#ifndef _SCM_MEMORY_POOL_H
#define _SCM_MEMORY_POOL_H

#include "scm.h"

/**
 * 内存池初始化
 * @param capacity 分配的大小
 */
int mem_init(int capacity);

/**
 * 从内存池中申请内存
 * @param size 申请的大小
 */
void* mem_molloc(int size);

/**
 * 释放申请的内存，归还内存池
 * @param ptr 指针
 */
void mem_free(void* ptr);


#endif  //_SCM_MEMORY_POOL_H