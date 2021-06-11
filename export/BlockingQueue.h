

#ifndef _SCM_BLOCKING_QUEUE_H
#define _SCM_BLOCKING_QUEUE_H

#include "scm.h"

namespace SCM {
template<typename T>
struct BlockingQueue {
    virtual bool add(const T& e) = 0;

    virtual bool offer(const T& e) = 0;

    virtual void put(const T& e) = 0;

    virtual bool offer(const T& e, const SCM_INT64& timeout) = 0;

    virtual T take() = 0; 

    virtual bool poll(T& d, const SCM_INT64& timeout) = 0;
};
}

#endif
