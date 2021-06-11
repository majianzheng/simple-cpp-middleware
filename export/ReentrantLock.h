/**
 * A lock is a tool for controlling access to a shared resource by multiple threads.
 * @author majianzheng
 */

#ifndef _SCM_REENTRANT_LOCK_H
#define _SCM_REENTRANT_LOCK_H

#include "Lock.h"

namespace SCM
{
class ReentrantLock : public Lock {

public:
    virtual void lock() override;

    virtual bool tryLock(const SCM_INT64 &time) override;

    virtual void unlock() override;

    virtual Condition *newCondition() override;
};
} // namespace SCM



#endif