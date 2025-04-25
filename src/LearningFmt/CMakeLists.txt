# Fmt库学习模块配置
find_package(fmt REQUIRED)

# 获取当前模块名
get_filename_component(MODULE_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

# 自动编译所有.cpp文件
file(GLOB TEST_SOURCES src/*.cpp)
foreach(test_source ${TEST_SOURCES})
    get_filename_component(test_name ${test_source} NAME_WE)
    
    # 创建可执行文件
    add_executable(${test_name} ${test_source})
    # 自动为每个模块创建独立输出目录
    setup_module_outputs(${test_name})
    # 链接fmt库
    target_link_libraries(${test_name} PRIVATE 
        fmt::fmt
    )
    
    # 编译器检查
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(${test_name} PRIVATE -Wall -Wextra)
    endif()
    
    # IDE分组
    set_property(TARGET ${test_name} PROPERTY FOLDER ${MODULE_NAME})
endforeach()
