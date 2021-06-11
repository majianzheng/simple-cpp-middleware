

#ifndef _SCM_MEM_POOL_TYPES_H
#define _SCM_MEM_POOL_TYPES_H

inline int rounded_size(int size) {
    return ((size + 7) & ~7);
}


#endif
