
/**
 * The heavy lock based raw pthread.
 */

#ifndef _SCM_MUTEXT_LOCK_H
#define _SCM_MUTEXT_LOCK_H

#include "Lock.h"
#include <pthread.h>
#include <unistd.h>
#include <list>

namespace SCM
{
class PthreadCondition : public Condition
{
private:
    pthread_cond_t _cond;
    pthread_mutex_t* _mutex;
public:
    virtual void await() override;

    virtual bool await(SCM_INT64 time) override;

    virtual void signal() override;

    virtual void signalAll() override;
    friend class MutexLock;
private:
    PthreadCondition(pthread_mutex_t* mutex_ptr);
    virtual ~PthreadCondition();
};

class MutexLock : public Lock
{
private:
    /* data */
    pthread_mutex_t _mutex[1];
    std::list<PthreadCondition*> _cond_list;
public:
    MutexLock(/* args */);
    virtual ~MutexLock();

    virtual void lock() override;

    virtual bool tryLock(const SCM_INT64 &time) override;

    virtual void unlock() override;

    virtual Condition *newCondition() override;
};
} // namespace SCM

#endif
