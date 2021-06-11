
#include "Thread.h"
#include <unistd.h>
#include <pthread.h>
#include <iostream>

using namespace SCM;

Thread::Thread(): _state(NEW), _tid(-1), _daemon(false), _fd(NULL) {
}

Thread::Thread(const Runnable& runnable): _fd(NULL) {
    _target = runnable;
    _name = "";
    _daemon = false;
    _state = NEW;
    _tid = -1;
}

Thread::Thread(const Runnable& runnable, const std::string& name, bool daemon): _fd(NULL) {
    _target = runnable;
    _name = name;
    _daemon = daemon;
    _state = NEW;
    _tid = -1;
}

Thread::~Thread() {
    _tid = -1;
    if (NULL != _fd) {
        pthread_t * ptr = (pthread_t*)_fd;
        delete ptr;
        _fd = NULL;
    }
}

void Thread::start() {
    if (RUNNABLE == _state) {
        //已经在运行中了
        return;
    }
    _state = RUNNABLE;
    _fd = new pthread_t;
    int status = pthread_create((pthread_t*)(_fd), NULL,
    [](void* args)->void* {
        Thread* _this = (Thread*)args;
        _this->_tid = getThreadId();
        //执行run
        _this->run();

        _this->_state = TERMINATED;
        return NULL;
    }, this);
    if (S_OK != status) {
        std::cerr<<"create thread failed.\n";
    }
}

void Thread::run() {
    try {
        if (_target) {
            _target();
        }
    }
    catch(const std::exception& e) {
        //ignore
    } catch (...) {
        //ignore
    }
}

void Thread::join() {
    if (NULL == _fd) {
        std::cerr<<"join failed.\n";
        return;
    }
    pthread_t* ptr = (pthread_t*)_fd;
    pthread_join(*ptr, NULL);
}

void Thread::join(SCM_INT64 millis)
{
    if (NULL == _fd) {
        std::cerr<<"join failed.\n";
        return;
    }
    struct timespec ts;
    if (clock_gettime(CLOCK_REALTIME, &ts) == -1) {
        std::cerr<<"clock_gettime failed.\n";
        return;
    }
    ts.tv_nsec += millis;
    int s = pthread_timedjoin_np(*(pthread_t*)_fd, NULL, &ts);
    if (0 != s) {
        std::cerr<<"join timed failed.\n";
    }
}

void Thread::sleep(SCM_INT64 sec) {
    ::sleep(sec);
}