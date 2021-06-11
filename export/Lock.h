/**
 * A lock is a tool for controlling access to a shared resource by multiple threads.
 * @author majianzheng
 */

#ifndef _SCM_LOCK_H
#define _SCM_LOCK_H

#include "scm.h"

namespace SCM {
struct Condition {
    virtual void await() = 0;

    virtual bool await(SCM_INT64 time) = 0;

    virtual void signal() = 0;

    virtual void signalAll() = 0;
};


struct Lock {
    virtual void lock() = 0;

    virtual bool tryLock(const SCM_INT64& time) = 0;

    virtual void unlock() = 0;

    virtual Condition* newCondition() = 0;
};

class ScopeLock {
    private:
    Lock* _lock;
    public:
    ScopeLock(Lock* lock) {
        _lock = lock;
        _lock->lock();
    }
    ~ScopeLock() {
        _lock->unlock();
    }
};
}
//区域锁
#define SCOPE_LOCK(lock_ptr) SCM::ScopeLock scope_lock(lock_ptr)

#endif
