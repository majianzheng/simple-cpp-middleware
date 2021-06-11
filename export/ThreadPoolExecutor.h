
#ifndef _SCM_THREAD_POLL_EXECUTOR_H
#define _SCM_THREAD_POLL_EXECUTOR_H

#include "ThreadFactory.h"
#include "BlockingQueue.h"
#include "Atomic.h"
#include <set>
#include <functional>

namespace SCM {

class Thread;
class ReentrantLock;
typedef std::function<Thread*(void)>        RejectedExecutionHandler; 

class ThreadPoolExecutor {
private:
    //私有内部类定义
    class Worker;
    //属性参数
    BlockingQueue<Runnable>* _work_queue;
    RejectedExecutionHandler _reject_handler;
    volatile SCM_INT64 _keep_alive_time;
    volatile int _core_size;
    volatile int _max_size;
    ThreadFactory* _thread_factory;
public:
    ThreadPoolExecutor(int core_size, int max_size, SCM_INT64 keep_alive_time, TIME_UNIT time_unit, int queue_size);

    ThreadPoolExecutor(int core_size, int max_size, SCM_INT64 keep_alive_time, TIME_UNIT time_unit, int queue_size, const RejectedExecutionHandler &reject_handler);
    
    ThreadPoolExecutor(int core_size, int max_size, SCM_INT64 keep_alive_time, TIME_UNIT time_unit, int queue_size, ThreadFactory *thread_factory);

    ThreadPoolExecutor(int core_size, int max_size, SCM_INT64 keep_alive_time, TIME_UNIT time_unit, int queue_size, ThreadFactory *thread_factory, const RejectedExecutionHandler &reject_handler);

    ~ThreadPoolExecutor();

    void execute(const Runnable& runnable);

    void setCoreSize(int core_size);

    int getCoreSize();

    void setMaxSize(int max_size);
    
    int getMaxSize();
protected:
    void beforeExecute(Thread* t, const Runnable& r) { }
    void afterExecute(Runnable& r) { }
private:
    void init(int core_size, int max_size, SCM_INT64 keep_alive_time, TIME_UNIT time_unit, int queue_size, ThreadFactory *thread_factory = NULL);
    void runWorker(Worker* w);
private:
    ReentrantLock* _main_lock;
    std::set<Worker*> _workers;
    friend class Worker;
};
}

#endif //_SCM_THREAD_POLL_EXECUTOR_H
