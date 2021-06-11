
#ifndef _SCM_H
#define _SCM_H

#include <string>
#include <functional>

#ifndef _int64
#define _int64 long long
#endif

#define SCM_INT64 long long

#ifndef NULL
#define NULL 0
#endif

#define S_OK  0

namespace SCM {
    struct LINK_NODE {
        LINK_NODE * preNode;
        LINK_NODE * nextNode;
        void * value;
    };

    struct FAST_LINK {
        LINK_NODE * head;
        LINK_NODE * tail;
    };

    enum TIME_UNIT {
        NANOSECONDS,
        MICROSECONDS,
        MILLISECONDS,
        SECONDS,
        MINUTES,
        HOURS,
        DAYS,
    };

    typedef std::function<void(void)>        Runnable; 

    //common api
    SCM_INT64 currentTimeMillis();

    SCM_INT64 nanoTime();

    int getThreadId();

} // namespace SCM


#endif /* _SCM_H */
