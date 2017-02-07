/*
 * Author: Broglie 
 * E-mail: yibo141@outlook.com
 */

#ifndef THREAD_H
#define THREAD_H

#include <pthread.h>

namespace servant
{

class Thread 
{
public:
    typedef void* (*ThreadFunc)(void*);
    explicit Thread(ThreadFunc func)
        :started(false),
         joined(false),
         tid(0),
         threadFunc(func)
    { }

    ~Thread()
    {
        if (started && !joined)
            pthread_detach(pthreadId);
    }

    void start();
    int join();
    bool isStarted() { return started; }
    pid_t gettid() { return tid; }

private:
    bool started;
    bool joined;
    pthread_t pthreadId;
    pid_t tid;
    ThreadFunc threadFunc;
};

}

#endif // THREAD_H