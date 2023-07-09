SHELL = /bin/sh
INC=./include
CC=g++ -I${INC} -std=c++11
AR=ar rcs

LibDir=./lib
Lib=liblog.a

BinDir=./bin

TestSrcDir=./test
TestSrc=${notdir ${wildcard ${TestSrcDir}/*.cpp}}
TestTarget=${addsuffix _test, ${basename ${TestSrc}}}

LibSrcDir=./src
LibSrc=${notdir ${wildcard ${LibSrcDir}/*.cpp}}

ObjDir=./obj
LibObjs=${patsubst %.cpp, %.o, ${LibSrc}}

Libs=-lpthread

vpath %_test ${BinDir}
vpath %.a ${LibDir}
vpath %.cpp ${LibSrcDir}:${TestSrcDir}
vpath %.o ${ObjDir}

$(shell mkdir -p ${BinDir})
$(shell mkdir -p ${LibDir})
$(shell mkdir -p ${ObjDir})

.PHONY: all
all: ${TestTarget}

%_test: %.o ${Lib}
	${CC} ${ObjDir}/${notdir $<} ${LibDir}/${Lib} -o ${BinDir}/$@ ${Libs}

${Lib}: ${LibObjs}
	${AR} ${LibDir}/${Lib} ${addprefix ${ObjDir}/, ${LibObjs}}

%.o: %.cpp
	${CC} -c $< -o ${ObjDir}/${notdir $@}

.PHONY: clean
clean:
	-rm -rf ${ObjDir} ${LibDir} ${BinDir}