# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.8)

project ("LearnDemo")

# 记录根目录
set(PROJECT_ROOT_DIR ${PROJECT_SOURCE_DIR})

# 设置库和可执行程序输出目录
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/common/lib)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

set(CMAKE_CXX_FLAGS   "-std=c++11 -g -Wall -fPIC -pthread -std=c++14") 

# 设置编译版本
if(1)
	set(CMAKE_BUILD_TYPE DEBUG)
else()
	set(CMAKE_BUILD_TYPE RELEASE)
endif()

# 包含子项目。
add_subdirectory ("src/TemplateProject")
add_subdirectory ("src/DesignMode")
add_subdirectory ("src/Test")
add_subdirectory ("src/LogY")
if(_WIN32)

else()

add_subdirectory ("src/Network")
add_subdirectory ("src/S17Test")
endif()

