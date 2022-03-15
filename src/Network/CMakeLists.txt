# CMakeList.txt: C++ 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

# 记录应用程序名称
set(EXE_NAME network)
#############################################################

# 添加工程文件
	# 枚举将同级目录及子目录中*.cpp\*.h文件
	file(GLOB_RECURSE PROJECT_HEADERS *.h)
	file(GLOB_RECURSE PROJECT_CPPS    *.cpp)

	set(SOURCES ${PROJECT_HEADERS} ${PROJECT_CPPS})
	
#链接库(需在add_executable前)
link_libraries(
	logy
	)

# 将源代码添加到此项目的可执行文件。
add_executable (${EXE_NAME} ${SOURCES})

# 添加包含目录
include_directories(
	.
	./src
	./src/select
	)
