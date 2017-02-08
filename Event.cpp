/*
 * Author: Broglie 
 * E-mail: yibo141@outlook.com
 */

#include "Event.h"

namespace servant
{

void Event::handleEvent()
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

}