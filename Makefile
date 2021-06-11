#目标文件名
TARGET:=libscm.so
TARGET_TEST:=scm_test

CC:= g++

SRC=./src
SRC_TEST=./test

#头文件路径
EXPORT_DIR=./export
INCLUDE_DIR=${SRC}/include

#输出路径
BUILD_DIR=./build

#头文件路径包含
INC_DIR=-I${EXPORT_DIR} -I${INCLUDE_DIR} -I${SRC}
INC_DIR_TEST=${INC_DIR} -I${SRC_TEST} -I${SRC_TEST}

#编译的代码文件
SOURCES=${SRC}/locks/*.cpp ${SRC}/concurrent/*.cpp ${SRC}/utils/*.cpp ${SRC}/memory/*.c
SOURCES_TEST=${SRC_TEST}/*.cpp

#链接的库
LIB=-lpthread
LIB_TEST=-L${BUILD_DIR} -lscm

OPTIONS=-std=c++11 -Wall -g -fPIC

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${BUILD_DIR}

all:
	@echo "start build..."
	@if [	!	-d $(BUILD_DIR)	];	then mkdir ${BUILD_DIR}; fi;
	@${CC} ${OPTIONS} ${INC_DIR} -shared ${LIB} -o ${BUILD_DIR}/${TARGET} ${SOURCES}
	@echo "build success!"

.PHONY:test
test:
	@echo "start build the test source code..."
	@${CC} ${OPTIONS} ${INC_DIR_TEST} ${LIB_TEST} -o ${BUILD_DIR}/${TARGET_TEST} ${SOURCES_TEST}
	@echo "build test code success! start execute test..."
	@${BUILD_DIR}/${TARGET_TEST}
	@echo "test finished!"
.PHONY:clean
clean:
	@if [	-d $(BUILD_DIR)	];	then rm -r -f ${BUILD_DIR}; fi;
	@echo "cleaned up."


