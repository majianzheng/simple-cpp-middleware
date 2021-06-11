
#ifndef _SCM_MEM_POOL_TEST_H
#define _SCM_MEM_POOL_TEST_H

#include "test.h"
#include "mem_pool_types.h"
#include "memory_pool.h"


void test_round_size() {
    int rounded = rounded_size(7);
    PRINT<<"rounded:"<<rounded<<endl;
    assert_eq(8, rounded, "rounded size error.");
}

#endif