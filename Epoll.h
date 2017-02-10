/*
 * Author: Broglie 
 * E-mail: yibo141@outlook.com
 */

#ifndef EPOLL_H
#define EPOLL_H

#include <sys/epoll.h>
#include <string.h>
#include <assert.h>
#include <iostream>
#include <vector>
#include "EventHandler.h"

namespace servant
{

class EventLoop;

class Epoll 
{
public:
    Epoll(EventLoop *loop)
        :ownerLoop(loop),
         epollfd(::epoll_create1(EPOLL_CLOEXEC)),
         retEvents(8) // 初始时为epoll_wait预留8个返回的epoll_event
    { 
        // FIXME: 调用日志库写入日志并终止程序
        if(epollfd < 0)
            std::cout << "Epoll::epoll_create1() error: " << ::strerror(errno) << std::endl;
        assert(epollfd > 0);
    }

    ~Epoll()
    { ::close(epollfd); }

    // 调用epoll_wait，并将其交给Event类的handleEvent函数处理
    void epoll();

    // 修改epoll监听的事件
    void updateHandler(EventHandler &eh);
    void removeHandler(const EventHandler &eh);

    void assertInLoopThread() const 
    {
        ownerLoop->assertInLoopThread();
    }

private:
    void update();
    void callHandler();
    
    EventLoop *ownerLoop;
    int epollfd;
    std::vector<struct epoll_event> retEvents;
    std::vector<EventHandler> handlers;
};

}

#endif // EPOLL_H