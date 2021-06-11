#include "MutexLock.h"
#include <assert.h>

using namespace SCM;

PthreadCondition::PthreadCondition(pthread_mutex_t* mutex_ptr) {
    _cond = PTHREAD_COND_INITIALIZER;
    _mutex = mutex_ptr;
}

PthreadCondition::~PthreadCondition() {
    pthread_cond_destroy(&_cond);
}

void PthreadCondition::await() {
    pthread_cond_wait(&_cond, _mutex);
}

bool PthreadCondition::await(SCM_INT64 time) {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    ts.tv_nsec += time;
    return 0 == pthread_cond_timedwait(&_cond, _mutex, &ts);
}

void PthreadCondition::signal() {
    pthread_cond_signal(&_cond);
}

void PthreadCondition::signalAll() {
    pthread_cond_broadcast(&_cond);
}


//系统互斥锁实现

MutexLock::MutexLock() {
    int status = pthread_mutex_init(_mutex, NULL);
    assert(status == 0);
}

MutexLock::~MutexLock() {
    if (!_cond_list.empty()) {
        for (auto iter = _cond_list.begin(); _cond_list.end() != iter; ++iter) {
            PthreadCondition* ptr = *iter;
            delete ptr;
        }
    }
    pthread_mutex_destroy(_mutex);
}

void MutexLock::lock() {
    pthread_mutex_lock(_mutex);
}

Condition* MutexLock::newCondition() {
    PthreadCondition* cond = new PthreadCondition(_mutex);
    _cond_list.push_back(cond);
    return cond;
}

bool MutexLock::tryLock(const SCM_INT64& timeout) {
    if (timeout < 0) {
        return false;
    }
    
    int status = S_OK;
    if (0 == timeout) {
        status = pthread_mutex_trylock(_mutex);
    } else {
        struct timespec time;
        clock_gettime(CLOCK_REALTIME, &time);
        time.tv_nsec += timeout;
        status = pthread_mutex_timedlock(_mutex, &time);
    }
    
    return S_OK == status;
}

void MutexLock::unlock() {
    pthread_mutex_unlock(_mutex);
}