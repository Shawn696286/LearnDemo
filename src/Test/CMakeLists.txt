# CMakeList.txt: C++ 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

# 记录应用程序名称
set(EXE_NAME Test)
#############################################################

# 添加工程文件
if(0)
	# 枚举下列*.h文件
	set(H_FILES
		./src/test.h
		)

	# 枚举下列*.cpp文件
	set(CPP_FILES 
		./src/main.cpp 
		src/test.cpp
		)
	set(SOURCES ${H_FILES} ${CPP_FILES})
elseif(1)	
	# 枚举将同级目录及子目录中*.cpp\*.h文件
	file(GLOB_RECURSE PROJECT_HEADERS *.h)
	file(GLOB_RECURSE PROJECT_CPPS    *.cpp)

	set(SOURCES ${PROJECT_HEADERS} ${PROJECT_CPPS})
else()	
	# 枚举将src目录的所有文件(不包含子目录)
	aux_source_directory(src SOURCES)
endif()

# 将源代码添加到此项目的可执行文件。
add_executable (${EXE_NAME} ${SOURCES})

# 添加包含目录
include_directories(
	.
	./src
	./src/thread
	)
