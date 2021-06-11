

#ifndef _SCM_TEST_H
#define _SCM_TEST_H

#include "scm.h"
#include <iostream>
#include <assert.h>

using namespace std;

#define PRINT cout
#define REPORT_ERROR cerr

#define ASSERT(condition) assert(condition)

void assert_eq(const char* a, const char* b, const char* msg = NULL);
void assert_neq(const char* a, const char* b, const char* msg = NULL);
void assert_eq(int a, int b, const char* msg = NULL);
void assert_neq(int a, int b, const char* msg = NULL);

typedef void (*TEST_RUN_FUNC)();

void test_round_size();

void thread_test();

static const TEST_RUN_FUNC test_func_unit_array[] = {
	test_round_size,
	thread_test,

    //结束标志，在此之前添加测试用例
    NULL
};

#endif //_SCM_TEST_H
