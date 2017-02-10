/*
 * Author: Broglie 
 * E-mail: yibo141@outlook.com
 */

#ifndef EVENT_H
#define EVENT_H

namespace servant
{

class EventLoop;

class EventHandler
{
public:
    typedef void (*Callback)();
    EventHandler(EventLoop *loop, const int fd, int event)
        :this->loop(loop),
         this->fd(fd),
         revents(event)
    { }

    void handleEvent();

    void setReadCallback(const Callback &cb)
    { readCallback = cb; }
    void setWriteCallback(const Callback &cb)
    { writeCallback = cb; }
    void setErrorCallback(const Callback &cb)
    { errorCallback = cb; }

    void enableRead()
    {
        revents |= (POLLIN | POLLPRI);
        update();
    }
    void enableWrite()
    {
        revents |= POLLOUT;
        update();
    }
    void disableWrite()
    {
        revents &= ~POLLOUT;
        update();
    }
    
    int fd() const 
    { return fd; }
    
private:
    void update();
    
    EventLoop *loop;
    const int fd;
    int revents;

    Callback readCallback;
    Callback writeCallback;
    Callback errorCallback;
};

}
#endif // EVENT_H