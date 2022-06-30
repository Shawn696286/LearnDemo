# CMakeList.txt: C++ 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

# 记录应用程序名称
set(EXE_NAME test_harddecoder)
#############################################################

# 添加工程文件
	# 枚举将同级目录及子目录中*.cpp\*.h文件
	file(GLOB_RECURSE PROJECT_HEADERS *.h)
	file(GLOB_RECURSE PROJECT_CPPS    *.cpp)

	set(SOURCES ${PROJECT_HEADERS} ${PROJECT_CPPS} )
	
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/${EXE_NAME})

# 添加包含目录
include_directories(
	.
	../../common/inc
	$ENV{FFMPEG_FULL}/include
	$ENV{DXSDK_DIR}/Include
	)
	
# 添加库目录
set(POSTFIX d)
link_directories(
	../../common/lib
	$ENV{FFMPEG_FULL}/lib
	$ENV{DXSDK_DIR}/Lib/${PLATFORM}
)

# 判断编译类型
if(CMAKE_BUILD_TYPE STREQUAL DEBUG)
set(POSTFIX d)
else()
set(POSTFIX )
endif()

message(STATUS "CMAKE_BUILD_TYPE:${CMAKE_BUILD_TYPE},POSTFIX:${POSTFIX}")

#链接库(需在add_executable前)
link_libraries(
	logy
	libutilY
	d3d9
	d3dx9
	dxva2
	)
if(UNIX)
link_libraries(
	)
else()
link_libraries(
	)
endif()

# 将源代码添加到此项目的可执行文件。
add_executable (${EXE_NAME} ${SOURCES})
