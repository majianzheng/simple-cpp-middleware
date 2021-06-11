

#ifndef __SCM_ATOMIC_H__
#define __SCM_ATOMIC_H__

#include "scm.h"

namespace SCM {

//Atomic Virtual
template<typename T>
struct Atomic {
    virtual void set(const T& t) = 0;

    virtual T get() = 0;
};

class AtomicByte: public Atomic<unsigned char> {
public:
    virtual void set(const unsigned char& t);

    virtual unsigned char get();
};

//INT16 Atomic
class AtomicShort: public Atomic<short> {
public:
    virtual void set(const short& t);

    virtual short get();

    short incAndGet();

    short getAndInc();
};

//INT32 Atomic
class AtomicInt: public Atomic<int> {

public:
    virtual void set(const int& t);

    virtual int get();

    int incAndGet();

    int getAndInc();
};

//INT64 Atomic
class AtomicInt64: public Atomic<SCM_INT64> {
public:
    virtual void set(const SCM_INT64& t);

    virtual SCM_INT64 get();

    SCM_INT64 incAndGet();

    SCM_INT64 getAndInc();
};

};


#endif //__SCM_ATOMIC_H__
