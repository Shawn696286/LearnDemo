# CMakeList.txt: C++ 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

# 枚举将同级目录及子目录中*.cpp\*.h文件
file(GLOB_RECURSE PROJECT_HEADERS *.h)
file(GLOB_RECURSE PROJECT_CPPS    *.cpp)

set(SOURCES ${PROJECT_HEADERS} ${PROJECT_CPPS})

include_directories(
	../../common/inc
	)

link_libraries(
	libssl.so
	libcrypto.so
	)
	
set(EXECUTABLE_OUTPUT_PATH ../../common/lib)

# 将源代码添加到此项目的静态库。
add_library(utils STATIC ${SOURCES})
                                         