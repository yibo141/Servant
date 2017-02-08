/*
 * Author: Broglie 
 * E-mail: yibo141@outlook.com
 */

#include <assert.h>
#include <poll.h>
#include "CurrentThread.h"
#include "EventLoop.h"

namespace servant
{

EventLoop::EventLoop()
    :isLooping(false),
     threadId(CurrentThread::gettid())
{ }

EventLoop::~EventLoop()
{
    assert(!isLooping);
}

void EventLoop::loop()
{
    assert(!isLooping);
    assertInLoopThread();
    isLooping = true;

    ::poll(NULL, 0, 5*1000);
    isLooping = false;
}

} // namespace servant