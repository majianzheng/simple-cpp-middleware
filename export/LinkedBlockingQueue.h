

#ifndef _SCM_LINKED_BLOCKING_QUEUE_H
#define _SCM_LINKED_BLOCKING_QUEUE_H

#include "BlockingQueue.h"
#include <list>

namespace SCM {

class Lock;
class Condition;

template<typename T>
class LinkedBlockingQueue : public BlockingQueue<T> {
private:
    int _capacity;
    Lock * _lock;
    std::list<T> _queue;
    Condition* _not_empty_cond;
    Condition* _not_full_cond;
    bool _not_empty_wait;
    bool _not_full_wait;
private:
    bool is_full() const {return _queue.size() >= _capacity;}
    bool is_empty() const {return _queue.empty();}
public:
    LinkedBlockingQueue(int capacity);
    virtual ~LinkedBlockingQueue();

    virtual bool add(const T& e) override;

    virtual bool offer(const T& e) override;

    virtual void put(const T& e) override;

    virtual bool offer(const T& e, const SCM_INT64& timeout) override;

    virtual T take() override; 

    virtual bool poll(T& d, const SCM_INT64& timeout) override;
};
}

#endif
