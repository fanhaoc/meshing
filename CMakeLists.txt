# CMakeList.txt: meshing 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

set(VCPKG_ROOT "c:/dev/vcpkg")

set(CMAKE_PREFIX_PATH "${VCPKG_ROOT}/installed/x64-windows/bin")

project ("meshing" LANGUAGES C CXX)

# 将源代码添加到此项目的可执行文件。
add_executable (meshing "meshing.cpp" "meshing.h" "ReadModel.cpp" "Octree.h" "Octree.cpp" "Visualization/Scene.cpp")

# TODO: 如有需要，请添加测试并安装目标。
# CMakeList.txt: tunnelProject 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
if(MSVC)
	add_compile_definitions("/utf-8")
endif(MSVC)

include("${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")

# include("c:/dev/vcpkg/installed/x64-windows")

find_package(assimp CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

file(GLOB SOURCE "*.h" "*.cpp" "*.txt")
# 将源代码添加到此项目的可执行文件。

# TODO: 如有需要，请添加测试并安装目标。
target_link_libraries(meshing PRIVATE assimp::assimp glfw glad::glad)

target_compile_options(meshing PRIVATE "/bigobj")