
#include "LinkedBlockingQueue.h"
#include "MutexLock.h"

using namespace SCM;

template<typename T>
LinkedBlockingQueue<T>::LinkedBlockingQueue(int capacity): _capacity(capacity) {
    _lock = new MutexLock();
    _not_empty_cond = _lock->newCondition();
    _not_full_cond = _lock->newCondition();
    _not_empty_wait = false;
    _not_full_wait = false;
}

template<typename T>
LinkedBlockingQueue<T>::~LinkedBlockingQueue() {
    if (NULL != _lock) {
        delete (MutexLock*)_lock;
        _lock = NULL;
    }
}

template<typename T>
bool LinkedBlockingQueue<T>::add(const T& e) {
    SCOPE_LOCK(_lock);
    if (this->is_full()) {
        return false;
    }
    _queue.push_back(e);
    //todo检查是否有在等待
    if (_not_empty_wait) {
        _not_empty_cond->signal();
    }
    return true;
}

template<typename T>
bool LinkedBlockingQueue<T>::offer(const T& e) {
    return add(e);
}

template<typename T>
void LinkedBlockingQueue<T>::put(const T& e) {
    SCOPE_LOCK(_lock);
    //阻塞式
    if (this->is_full()) {
        _not_full_wait = true;
        _not_full_cond->await();
        _not_full_wait = false;
    }
    _queue.push_back(e);
    //todo检查是否有在等待
    if (_not_empty_wait) {
        _not_empty_cond->signal();
    }
}

template<typename T>
bool LinkedBlockingQueue<T>::offer(const T& e, const SCM_INT64& timeout) {
    SCOPE_LOCK(_lock);
    //阻塞式
    bool isOk = true;
    if (this->is_full()) {
        _not_full_wait = true;
        isOk = _not_full_cond->await(timeout);
        _not_full_wait = false;
    }
    if (isOk)
    {
        _queue.push_back(e);
        if (_not_empty_wait) {
            _not_empty_cond->signal();
        }
    }
    return isOk;
}

template<typename T>
T LinkedBlockingQueue<T>::take() {
    SCOPE_LOCK(_lock);
    if (is_empty()) {
        _not_empty_wait = true;
        _not_empty_cond->await();
        _not_empty_wait = false;
    }
    T d = _queue.front();
    _queue.pop_front();
    if (_not_full_wait) {
        _not_full_cond->signal();
    }
    return d;
}

template<typename T>
bool LinkedBlockingQueue<T>::poll(T& d, const SCM_INT64& timeout) {
    SCOPE_LOCK(_lock);
    bool isOk = true;
    if (is_empty()) {
        _not_empty_wait = true;
        isOk = _not_empty_cond->await(timeout);
        _not_empty_wait = false;
    }
    if (isOk) {
        T d = _queue.front();
        _queue.pop_front();
        if (_not_full_wait) {
            _not_full_cond->signal();
        }
    }
    return isOk;  
}

