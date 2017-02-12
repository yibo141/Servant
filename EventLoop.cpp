/*
 * Author: Broglie 
 * E-mail: yibo141@outlook.com
 */

#include <assert.h>
#include <poll.h>
#include <signal.h>
#include <assert.h>
#include "CurrentThread.h"
#include "EventLoop.h"
#include "Event.h"
#include "Epoll.h"

namespace 
{
    class IgnoreSigPipe
    {
    public:
        IgnoreSigPipe()
        {
            ::signal(SIGPIPE, SIG_IGN);
        }
    };

    // 忽略SIGPIPE信号
    IgnoreSigPipe initObj;
}

namespace servant
{

EventLoop::EventLoop()
    :isLooping(false),
     threadId(CurrentThread::gettid()),
     isQuit(false),
     e(new Epoll(this))
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
    isQuit = false;

    while(!isQuit)
    {
        activeEvents.clear();
        e->epoll(activeEvents);
        for(std::vector<Event*>:: iterator iter = activeEvents.begin();
            iter != activeEvents.end(); ++iter)
        {
            (*iter)->handleEvent();
        }
    }
    isLooping = false;
}

void EventLoop::quit()
{
    isQuit = true;
}

void EventLoop::updateEvent(Event *ev)
{
    assert(ev->ownerLoop() == this);
    assertInLoopThread();
    e->updateEvent(ev);
}

} // namespace servant