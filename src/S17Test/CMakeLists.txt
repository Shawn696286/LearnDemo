# CMakeList.txt: C++ 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

# 记录应用程序名称
set(EXE_NAME S17Test)
#############################################################

set(CMAKE_C_COMPILER "/usr/local/bin/gcc")
set(CMAKE_CXX_COMPILER "/usr/local/bin/g++")
set(CMAKE_CXX_FLAGS "-std=c++14 -fPIC -g -Wall -Wno-deprecated-declarations -ldl -pthread") 

set(S17_SDK_PATH $ENV{S17_SDK_PATH})
message(S17_SDK_PATH: ${S17_SDK_PATH})

include_directories(${S17_SDK_PATH}/inc)
include_directories(${S17_SDK_PATH}/third-party/inc)
include_directories(${S17_SDK_PATH}/third-party/inc/boost)

include_directories(./utils)
include_directories(./utils/config)
include_directories(./platform/up.s17/signal)
include_directories(./plugin/down.lenz)
include_directories(./plugin/down.lenz/parser)


link_directories(${S17_SDK_PATH}/lib64)
link_directories(${S17_SDK_PATH}/third-party/lib64)


# 添加工程文件	
	# 枚举将同级目录及子目录中*.cpp\*.h文件
	file(GLOB_RECURSE PROJECT_HEADERS *.h)
	file(GLOB_RECURSE PROJECT_CPPS    *.cpp)

	set(SOURCES ${PROJECT_HEADERS} ${PROJECT_CPPS} )

# 添加包含目录
include_directories(
	.
	./aes
	)
	

# 将源代码添加到此项目的可执行文件。
add_executable (${EXE_NAME} ${SOURCES})

set(THIRD_LIBS
	libyaml-cpp.a
	libjsoncpp.a
	libeXosip2.so
	libosip2.so
	libpugixml.a
	libosipparser2.so
	libbasic_cpp.so
	libavcore.so
	libs17_sdk_client.so
)
target_link_libraries(${EXE_NAME} ${THIRD_LIBS})