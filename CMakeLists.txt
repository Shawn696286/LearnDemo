# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.8)

project ("LearnDemo")

# 记录根目录
set(PROJECT_ROOT_DIR ${PROJECT_SOURCE_DIR})

# 检测项目32位还是64位
if(CMAKE_CL_64)
	set(PLATFORM "x64") 
else()
	set(PLATFORM "x86") 
endif()

# 设置库和可执行程序输出目录
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/common/lib/${PLATFORM})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/${PLATFORM})

if(UNIX)
set(CMAKE_CXX_FLAGS   "-std=c++11 -g -Wall -fPIC -pthread -std=c++14") 
endif()

# 设置编译版本
if(1)
	set(CMAKE_BUILD_TYPE DEBUG)
else()
	set(CMAKE_BUILD_TYPE RELEASE)
endif()


# 包含子项目。
if(0)
add_subdirectory ("src/TemplateProject")
add_subdirectory ("src/DesignMode")
endif()
#add_subdirectory ("src/Test")
add_subdirectory ("src/LogY")
#add_subdirectory ("src/UtilY")
#add_subdirectory ("src/TestAvapi64")
#add_subdirectory ("src/TestAvapi32")
if(WIN32)

#add_subdirectory ("src/GpuCmd")
#add_subdirectory ("src/FFmpegGpu")
add_subdirectory ("src/FFmpegGpuQtPlayer")
#add_subdirectory ("src/TestHardDecoder")
else()

add_subdirectory ("src/Network")
add_subdirectory ("src/S17Test")
endif()

