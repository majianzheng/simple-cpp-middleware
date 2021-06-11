#include "test.h"
#include <string.h>

bool check_str_eq(const char* a, const char* b) {
        if (NULL == a && NULL == b) {
        return true;
    }
    if (NULL == a || NULL == b) {
        REPORT_ERROR<<"字符串其中一个为空"<<endl;
        return false;
    }
    return (0 == strcmp(a, b));
}

void assert_eq(const char* a, const char* b, const char* msg) {
    bool c = check_str_eq(a, b);
    if (NULL != msg) {
        REPORT_ERROR<<msg;
    }
    ASSERT(c);
}

void assert_neq(const char* a, const char* b, const char* msg) {
    bool c = !check_str_eq(a, b);
    if (NULL != msg) {
        REPORT_ERROR<<msg;
    }
    ASSERT(c);
}

void assert_eq(int a, int b, const char* msg) {
    if (a == b) {
        return;
    }
    if (NULL != msg) {
        REPORT_ERROR<<msg;
    }
    ASSERT(false);
}
void assert_neq(int a, int b, const char* msg) {
    if (a != b) {
        return;
    }
    if (NULL != msg) {
        REPORT_ERROR<<msg;
    }
    ASSERT(false);
}