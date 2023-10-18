# CMakeList.txt: meshing 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

set(VCPKG_ROOT "c:/dev/vcpkg")

set(CMAKE_PREFIX_PATH "${VCPKG_ROOT}/installed/x64-windows/bin")

project ("meshing" LANGUAGES C CXX)

# 将源代码添加到此项目的可执行文件。
add_executable (meshing "meshing.cpp"  "ReadModel.cpp"  "Octree.cpp" "Visualization/Scene.cpp" "Visualization/Mesh.cpp" "Types.h" "Visualization/Shader.h" "Visualization/Shader.cpp" "Visualization/Camera.h" "Visualization/Camera.cpp" "Visualization/controller.cpp" "Visualization/controller.h" "Visualization/Mesh.h" "Visualization/Material.cpp" "Visualization/Material.h" "Visualization/Lights/Light.h" "Visualization/Lights/Light.cpp" "Visualization/Lights/LightSpot.h" "Visualization/Lights/LightSpot.cpp" "Visualization/Model.cpp" "Visualization/Model.h")

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
find_package(glm CONFIG REQUIRED)

file(GLOB SOURCE "*.h" "*.cpp" "*.txt")
# 将源代码添加到此项目的可执行文件。

# TODO: 如有需要，请添加测试并安装目标。
target_link_libraries(meshing PRIVATE assimp::assimp glfw glad::glad glm::glm)

target_compile_options(meshing PRIVATE "/bigobj")
