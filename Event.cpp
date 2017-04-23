/*
 * Author: Broglie 
 * E-mail: yibo141@outlook.com
 */

#include <sys/epoll.h>
#include "Event.h"
#include "EventLoop.h"

namespace servant
{

void Event::handleEvent()
{
    if(revents & (EPOLLIN | EPOLLPRI | EPOLLRDHUP))
        if(readCallback)
            readCallback();
    if(revents & EPOLLOUT)
        if(writeCallback)
            writeCallback();
    if(revents & EPOLLERR)
        if(errorCallback)
            errorCallback();
}

void Event::update()
{
    loop->updateEvent(this);
}

} // namespace servant