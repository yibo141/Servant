/*
 * Author: Broglie 
 * E-mail: yibo141@outlook.com
 */

#ifndef EPOLL_H
#define EPOLL_H

#include <sys/epoll.h>
#include <vector>
#include "Event.h"

namespace servant
{

class EventLoop;

class Epoll 
{
public:
    Epoll(EventLoop *loop)
        :ownerLoop(loop)
    { }

    // 调用epoll_wait， 返回的是待处理的events
    std::vector<Event> epoll();

    // 修改epoll监听的事件
    void updateEvent(Event &ev);
    void removeEvent(const Event &ev);

    void assertInLoopThread() const 
    {
        ownerLoop->assertInLoopThread();
    }

private:
    void update();
    std::vector<Event> events;
    std::vector<Event> retEvents;
};

}

#endif // EPOLL_H