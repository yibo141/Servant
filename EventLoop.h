/*
 * Author: Broglie 
 * E-mail: yibo141@outlook.com
 */

#ifndef EVENTLOOP_H
#define EVENTLOOP_H

#include <sys/syscall.h>
#include <sys/types.h>
#include <assert.h>
#include <vector>

#include "CurrentThread.h"

namespace servant
{

class Epoll;
class Event;

class EventLoop 
{
public:
    EventLoop();
    ~EventLoop();
    void loop();
    void quit();
    void assertInLoopThread()
    {
        assert(isInLoopThread());
    }
    bool isInLoopThread() const 
    {
        return threadId == CurrentThread::gettid(); // ::syscall(SYS_gettid);
    }
    void updateEvent(Event *ev);

private:
    bool isLooping;
    const pid_t threadId;
    bool isQuit;
    Epoll *e;
    std::vector<Event*> activeEvents;
};

}
#endif // EVENTLOOP_H