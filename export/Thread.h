

#ifndef _SCM_THREAD_H
#define _SCM_THREAD_H

#include "scm.h"
#include <string>

namespace SCM {
    class Thread {
        enum State {
            NEW,
            RUNNABLE,
            BLOCKED,
            WAITING,
            TIMED_WAITING,
            TERMINATED,
        };
    private:
        /* data */
        Runnable _target;
        std::string _name;
        State _state;
        bool _daemon;
        void * _fd;
        SCM_INT64  _tid;
    protected:
        virtual void run();
    public:
        Thread(/* args */);

        Thread(const Runnable& runnable);

        Thread(const Runnable& runnable, const std::string& name, bool daemon = false);

        ~Thread();

        void setName(std::string& name) {
            this->_name = name;
        }

        const std::string& getName() const {
            return _name;
        }

        void start();

        void join();

        void join(SCM_INT64 millis);

        static Thread* currentThread();

        static void sleep(SCM_INT64 millis);

        SCM_INT64 getId() {return _tid;}

        int getState() {return _state;}

    };
    
} // namespace SCM 

#endif //_SCM_THREAD_H