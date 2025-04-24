cmake_minimum_required(VERSION 3.20)
project(LearingCppLibraries)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
find_package(fmt REQUIRED) #全局需要fmt库
# 设置二进制输出基础目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# 自动为每个模块创建独立输出目录
function(setup_module_outputs MODULE_NAME)
    set_target_properties(${MODULE_NAME} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${MODULE_NAME}"
            LIBRARY_OUTPUT_DIRECTORY "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/${MODULE_NAME}"
            ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/${MODULE_NAME}"
    )
endfunction()


# 1. Vcpkg 自动集成（优先使用环境变量中的路径）
if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
    message(STATUS "Using Vcpkg from: $ENV{VCPKG_ROOT}")
elseif(EXISTS "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")
    set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")
endif()

# 2. 自动包含所有 Learning* 子模块
file(GLOB LIB_DIRS LIST_DIRECTORIES true "src/Learning*")
foreach(subdir ${LIB_DIRS})
    if(EXISTS "${subdir}/CMakeLists.txt")
        message(STATUS "Adding module: ${subdir}")
        add_subdirectory(${subdir})
    endif()
endforeach()

