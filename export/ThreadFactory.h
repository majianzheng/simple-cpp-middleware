

#ifndef _SCM_THREAD_FACTORY_H
#define _SCM_THREAD_FACTORY_H

#include "scm.h"
#include "Thread.h"

namespace SCM {
    struct ThreadFactory {
        virtual Thread* newThread(const Runnable& runnable) = 0;
    };
    
} // namespace SCM


#endif //_SCM_THREAD_FACTORY_H