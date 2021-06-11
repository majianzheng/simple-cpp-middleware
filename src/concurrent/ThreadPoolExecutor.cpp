
#include "ThreadPoolExecutor.h"
#include "LinkedBlockingQueue.h"
#include "Thread.h"
#include "ReentrantLock.h"
#include <sstream>

using namespace SCM;

//私有内部类Worker
//实现线程池的实际执行体
class ThreadPoolExecutor::Worker {
private:
    ThreadPoolExecutor* _thread_pool;
    Runnable _firstTask;
    Thread* _thread;
    volatile _int64 _completed_tasks;
public:
    Worker(ThreadPoolExecutor* thread_pool, const Runnable& first_task){
        this->_thread_pool = thread_pool;
        this->_firstTask = first_task;
        this->_completed_tasks = 0;
        this->_thread = thread_pool->_thread_factory->newThread([this](){
            run();
        });
    }
    ~Worker(){

    }
    void run() {
        this->_thread_pool->runWorker(this);
    }
    friend class ThreadPoolExecutor;
};

class DefaultThreadFactory : public ThreadFactory {
private:
    AtomicInt _thr_count;
public:
    virtual Thread* newThread(const Runnable& runnable) {
        std::stringstream ss;
        ss<<"scm-thr-pool-"<<_thr_count.getAndInc();
        Thread* thr = new Thread(runnable, ss.str());
        return thr;
    }
};

void ThreadPoolExecutor::init(int core_size, int max_size, SCM_INT64 keep_alive_time, TIME_UNIT time_unit, int queue_size, ThreadFactory *thread_factory) {
    this->_core_size = core_size;
    this->_keep_alive_time = keep_alive_time;
    this->_max_size = max_size;
    _work_queue = new LinkedBlockingQueue<Runnable>(queue_size);
    if (NULL == thread_factory) {
        _thread_factory = new DefaultThreadFactory();
    } else {
        _thread_factory = thread_factory;
    }
}

ThreadPoolExecutor::ThreadPoolExecutor(int core_size, int max_size, SCM_INT64 keep_alive_time, TIME_UNIT time_unit, int queue_size) {
    this->init(core_size, max_size, keep_alive_time, time_unit, queue_size);
}

ThreadPoolExecutor::ThreadPoolExecutor(int core_size, int max_size, SCM_INT64 keep_alive_time, TIME_UNIT time_unit, int queue_size, 
    const RejectedExecutionHandler &reject_handler) {
    this->init(core_size, max_size, keep_alive_time, time_unit, queue_size);
    this->_reject_handler = reject_handler;
}

ThreadPoolExecutor::ThreadPoolExecutor(int core_size, int max_size, SCM_INT64 keep_alive_time, TIME_UNIT time_unit, int queue_size, ThreadFactory *thread_factory) {
    this->init(core_size, max_size, keep_alive_time, time_unit, queue_size, thread_factory);
}

ThreadPoolExecutor::ThreadPoolExecutor(int core_size, int max_size, SCM_INT64 keep_alive_time, TIME_UNIT time_unit, int queue_size, ThreadFactory *thread_factory, const RejectedExecutionHandler &reject_handler) {
    this->init(core_size, max_size, keep_alive_time, time_unit, queue_size, thread_factory);
    this->_reject_handler = reject_handler;
}

ThreadPoolExecutor::~ThreadPoolExecutor() {

}

void ThreadPoolExecutor::execute(const Runnable &runnable) {

}

void ThreadPoolExecutor::setCoreSize(int core_size) {
    this->_core_size = core_size;
}

int ThreadPoolExecutor::getCoreSize() {
    return this->_core_size;
}

void ThreadPoolExecutor::setMaxSize(int max_size) {
    this->_max_size = max_size;
}

int ThreadPoolExecutor::getMaxSize() {
    return this->_max_size;
}

void ThreadPoolExecutor::runWorker(Worker* w) {
    Thread* wt = Thread::currentThread();
    const Runnable& task = w->_firstTask;
    //w->_firstTask = null;
    //w.unlock(); // allow interrupts
    bool completedAbruptly = true;
    try {
        while (task != null || (task = getTask()) != null) {
            //w.lock();
            if ((runStateAtLeast(ctl.get(), STOP) ||
                 (Thread.interrupted() &&
                  runStateAtLeast(ctl.get(), STOP))) &&
                !wt.isInterrupted())
                wt.interrupt();
            beforeExecute(wt, task);
            try {
                task.run();
                afterExecute(task);
            } catch (...) {
                afterExecute(task);
            }
            w->_completed_tasks++;
        }
        completedAbruptly = false;
    } catch (...) {
        
    }
    //processWorkerExit(w, completedAbruptly);
}
