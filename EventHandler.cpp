/*
 * Author: Broglie 
 * E-mail: yibo141@outlook.com
 */

#include <sys/epoll.h>
#include "EventHandler.h"

namespace servant
{

void EventHandler::handleEvent()
{
    if(revents & (POLLIN | POLLPRI | POLLRDHUP))
        if(readCallback)
            readCallback();
    if(revents & POLLOUT)
        if(writeCallback)
            writeCallback();
    if(revent & (POLLERR | POLLNVAL))
        if(errorCallback)
            errorCallback();
}

void EventHandler::update()
{
    // TODO
}

} // namespace servant