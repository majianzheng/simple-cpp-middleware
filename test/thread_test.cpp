

#ifndef _SCM_THREAD_TEST_H
#define _SCM_THREAD_TEST_H

#include "test.h"
#include "Thread.h"
#include "MutexLock.h"

using namespace SCM;

void thread_test() {
    int current_id = getThreadId();
    PRINT<<"Begin thread. current:"<<getThreadId()<<endl;
    MutexLock lock;
    SCM_INT64 time1 = 0;

    Thread thread([&](){
        //线程入口
        int id = SCM::getThreadId();
        PRINT<<"Thread created，id:"<<id<<std::endl;
        assert_neq(current_id, id);
        //测试互斥锁
        lock.lock();
        time1 = SCM::currentTimeMillis();
        PRINT<<"thread into lock scop, sleep some time.\n";
        ::sleep(3);
        PRINT<<"thread out lock scop.\n";
        lock.unlock();
    });

    //启动线程
    thread.start();

    PRINT<<"thread created.\n";
    ::sleep(1);

    PRINT<<"main thread begin lock.\n";
    lock.lock();
    SCM_INT64 get_lock_time = SCM::currentTimeMillis() - time1;
    PRINT<<"get_lock_time:"<<get_lock_time<<endl;
    ASSERT(get_lock_time > 2600);
    lock.unlock();

    thread.join();
};

#endif
