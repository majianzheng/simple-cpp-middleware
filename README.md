# simple c++ middleware

As it's name, it's a light simple middleware library for c++ developers without any third library, and only for <code>Linux</code> and <code>MacOS</code> based raw OS kernal clang API and asm.

* Memory pool
* Lock based <code>AQS</code>
* Blocking queue
* Thread pool
* High performance share memory management(todo).

## Backgroud
When we want to develop a small system, properly need depend on some third big library even if we only use a litle part of it.

## Building and test

Clean the old target. Use <code>make clean</code> command:
```
[root@localhost simple-cpp-middleware]# make clean
cleaned up.
```

How to build it. Execute Makefile <code>make</code> command to build the library as:
```
[root@localhost simple-cpp-middleware]# make
start build...
build success!
```

Test it use the <code>make test</code> command like:

```
[root@localhost simple-cpp-middleware]# make test
start build the test source code...
build test code success! start execute test...
test proccess is ready, start test>>>
...
...
test result output
...
...
test is over, press [Enter] to finish.

test finished!
```
And also you can use group command once like <code>make clean all test</code>.
```
[root@localhost simple-cpp-middleware]# make clean all test
cleaned up.
start build...
build success!
start build the test source code...
build test code success! start execute test...
test proccess is ready, start test>>>
...
...
test result output
...
...
test is over, press [Enter] to finish.

test finished!
```

## API document
### Memory pool include the memory_pool.h
```
file: demo.c

#include "memory_pool.h"

int main(int argc, char const *argv[]) {
    //At first alloc 10M space from system to init memory pool
    mem_init(1024 * 1024 * 10);

    //Malloc some memory from memory pool
    void * buffer = mem_malloc(1024);

    //Use the memory do something
    const char* data = "some data...";
    memcpy(buffer, data, strlen(data));

    //At last release the memory
    mem_free(buffer);

    return 0;
}
```
### Lock and thread usage
```
#include "ReentrantLock.h"
#include "Thread.h"

int main(int argc, char const *argv[]) {
    //At first init a Lock instance.
    ReentrantLock lock;

    //Ant start a thread

    return 0;
}
```
