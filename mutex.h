#ifndef _MUTEX_H
#define _MUTEX_H

#include <pthread.h>

class mutex
{
    public:
        mutex();
        ~mutex();
        void lock();
        void unlock();
    private:
        pthread_mutex_t mutex_;
};

mutex::mutex()
{
    pthread_mutex_init(&mutex_, NULL);
}

void mutex::lock()
{
    pthread_mutex_lock(&mutex_);
}

void mutex::unlock()
{
    pthread_mutex_unlock(&mutex_);
}

~mutex::mutex()
{
    pthread_mutex_destroy(&mutex_);
}

#endif
