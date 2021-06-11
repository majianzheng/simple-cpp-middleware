

#ifndef __SCM_CAS_ASM_H__
#define __SCM_CAS_ASM_H__

//比较并交换值
bool compare_and_swap_int(volatile int * addr, int expect, int update);

#endif  //__SCM_CAS_ASM_H__
