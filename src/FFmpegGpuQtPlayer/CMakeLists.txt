# CMakeList.txt: C++ 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

# 记录应用程序名称
set(EXE_NAME player_ffmpeg_qt_gpu)

# 设置库和可执行程序输出目录
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/${PLATFORM}/${EXE_NAME})
#############################################################

#修改环境变量，添加qt路径
set(QT_PATH  "C:/Qt/Qt5.12.12/5.12.12/msvc2017_64/bin")
set(ENV{PATH} "${QT_PATH};$ENV{PATH}")

# 查找QT库路径
find_package(Qt5 COMPONENTS Widgets REQUIRED)

# 添加工程文件	
# 枚举将同级目录及子目录中*.cpp\*.h文件
file(GLOB_RECURSE PROJECT_HEADERS *.h)
file(GLOB_RECURSE PROJECT_CPPS    *.cpp)
qt5_wrap_ui(GLOB_RECURSE QT_UIS *.ui)
set(SOURCES ${PROJECT_HEADERS} ${PROJECT_CPPS} )

# 添加包含目录
include_directories(
	.
	../../common/inc
	$ENV{FFMPEG_FULL}/include
	)
	

# 添加库目录
link_directories(
	../../common/lib/${PLATFORM}
	$ENV{FFMPEG_FULL}/lib
)

#链接库(需在add_executable前)
if(UNIX)
link_libraries(
	logy
	libutilY
	)
else()
link_libraries(
	logy
	libutilY
	Qt5::Widgets
	)
endif()

# 将源代码添加到此项目的可执行文件。
add_executable (${EXE_NAME} ${SOURCES})
