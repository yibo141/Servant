/*
 * Author: Broglie 
 * E-mail: yibo141@outlook.com
 */

#include "Epoll.h"
#include "Event.h"

namespace servant   
{

void Epoll::epoll(std::vector<Event*> &activeEvents)
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
            exit(1);
        }
    }
    else if(numEvents == 0) 
    {
        // 什么都不做
    }
    else 
    {
        if(numEvents == retEvents.size())
            retEvents.resize(1.5 * numEvents);
        for(int i = 0; i < numEvents; ++i) 
        {
            Event *ev = new Event(ownerLoop, retEvents[i].data.fd);
            ev->setRetEvents(retEvents[i].events);
            activeEvents.push_back(ev);
        }
    }
}

void Epoll::updateEvent(Event *ev)
{
    // 确保在拥有此Event的线程更新Event
    assert(ev->ownerLoop == this->ownerLoop);
    epoll_event event;
    event.data.fd = ev->getFd();
    event.events = ev->getEvents();
    ::epoll_ctl(epollfd, EPOLL_CTL_MOD, ev->getFd(), &event);
}

} // namespace servant