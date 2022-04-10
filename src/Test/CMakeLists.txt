# CMakeList.txt: C++ 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

# 记录应用程序名称
set(EXE_NAME Test)
#############################################################

find_package(OpenSSL REQUIRED)

message(STATUS "openssl libs: ${OPENSSL_LIBRARIES}")

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

# 添加包含目录
include_directories(
	.
	./src
	./src/thread
	./src/smart_pointers
	../../common/inc
	)
	
# 添加库目录
link_directories(
	../../common/lib
	/usr/lib/x86_64-linux-gnu/
)

if(0)
#链接库(需在add_executable前)
if(UNIX)
link_libraries(
	libssl.so
	logy
	#utils
	)
else()
link_libraries(
	logy
	)
endif()
endif()

set(THIRD_LIBS
	logy
	utils
)

# 将源代码添加到此项目的可执行文件。
add_executable (${EXE_NAME} ${SOURCES})
target_link_libraries(${EXE_NAME} ${THIRD_LIBS})

