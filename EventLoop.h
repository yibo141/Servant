/*
 * Author: Broglie 
 * E-mail: yibo141@outlook.com
 */

#ifndef EVENTLOOP_H
#define EVENTLOOP_H

#include <syscall.h>
#include <sys/types.h>
#include <assert.h>

#include "CurrentThread.h"

namespace servant
{

class EventLoop 
{
public:
    EventLoop();
    ~EventLoop();
    void loop();
    void assertInLoopThread()
    {
        assert(isInLoopThread());
    }
    bool isInLoopThread() const 
    {
        return threadId == CurrentThread::gettid(); // ::syscall(SYS_gettid);
    }

private:
    bool isLooping;
    const pid_t threadId;
};

}
#endif // EVENTLOOP_H