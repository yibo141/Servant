/*
 * Author: Broglie 
 * E-mail: yibo141@outlook.com
 */

#include "Epoll.h"
#include "EventHandler.h"

namespace servant   
{

void Epoll::epoll()
{
    int numEvents = ::epoll_wait(epollfd,
                                 retEvents.data(),
                                 static_cast<int>(retEvents.size()),
                                 -1);
    if(numEvents < 0) 
    {
        if(errno != EINTR)
        {   // FIXME: 调用日志库写入日志并终止程序
            std::cout << "Epoll::epoll() error: " << ::strerror(errno) << std::endl;
            assert(numEvents >= 0);
        }
    }
    else if(numEvents == 0) 
    {
        // 什么都不做
    }
    else 
    {
        if(numEvents == events.size())
            retEvents.resize(1.5 * numEvents);
        for(int i = 0; i < numEvents; ++i) 
        {
            EventHandler eh(ownerLoop, retEvents[i].data.fd, retEvents[i].events);
            handlers.push_back(eh);
            callHandler();
        }
    }
}

void Epoll::updateHandler(EventHandler &eh)
{
    // TODO
}

void Epoll::removeHandler(const EventHandler &eh)
{
    // TODO
}

void Epoll::update()
{
    // TODO
}

void Epoll::callHandler()
{
    for(const EventHandler &handler : handlers)
    {
        handler.handleEvent();
    }
}

} // namespace servant