
#include "scm.h"
#include "sys/time.h"
#include <unistd.h>
#include <sys/types.h>
#include <sstream>
#include <iostream>

#if __GLIBC__ == 2 && __GLIBC_MINOR__ < 30
#include <sys/syscall.h>
#define gettid() syscall(SYS_gettid)
#endif

namespace SCM {

    SCM_INT64 currentTimeMillis() {
        struct timeval tv;
        gettimeofday(&tv, NULL);
        return tv.tv_sec*1000 + tv.tv_usec/1000;
    }

    SCM_INT64 nanoTime() {
        struct timeval tv;
        gettimeofday(&tv, NULL);
        return tv.tv_sec*1000000 + tv.tv_usec;
    }

    int getThreadId() {
        return (int)gettid();
    }
    
} // namespace SCM
