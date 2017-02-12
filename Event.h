/*
 * Author: Broglie 
 * E-mail: yibo141@outlook.com
 */

#ifndef EVENT_H
#define EVENT_H

#include <sys/epoll.h>

namespace servant
{

class EventLoop;

class Event
{
public:
    typedef void (*Callback)(int fd);
    Event(EventLoop *_loop, int _fd)
        : loop(_loop),
          fd(_fd),
          revents(0)
    { }

    void handleEvent();

    void setRetEvents(int retEvents)
    {
        revents = retEvents;
    }
    int getEvents()
    {
        return events;
    }
    int getFd()
    {
        return fd;
    }

    void setReadCallback(const Callback &cb)
    { readCallback = cb; }
    void setWriteCallback(const Callback &cb)
    { writeCallback = cb; }
    void setErrorCallback(const Callback &cb)
    { errorCallback = cb; }

    void enableRead()
    {
        events |= (EPOLLIN | EPOLLPRI);
        update();
    }
    void enableWrite()
    {
        events |= EPOLLOUT;
        update();
    }
    void disableWrite()
    {
        events &= ~EPOLLOUT;
        update();
    }
    EventLoop* ownerLoop()
    {
        return loop;
    }
    
private:
    void update();
    
    EventLoop *loop;
    int fd;
    int events;   // 注册感兴趣的事件，由用户设置
    int revents;  // epoll_wait()调用返回的事件，由内核填写

    Callback readCallback;
    Callback writeCallback;
    Callback errorCallback;
};

}
#endif // EVENT_H