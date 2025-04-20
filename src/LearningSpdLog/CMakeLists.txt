# 1. 声明当前模块的依赖
find_package(spdlog REQUIRED)

# 2. 获取当前模块名（自动识别目录名）
get_filename_component(MODULE_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
# 3. 自动为每个.cpp文件生成独立可执行程序+
file(GLOB TEST_SOURCES src/*.cpp)
foreach(test_source ${TEST_SOURCES})
    get_filename_component(test_name ${test_source} NAME_WE)  # 提取无后缀文件名

    # 创建可执行文件
    add_executable(${test_name} ${test_source})
    # 自动为每个模块创建独立输出目录
    setup_module_outputs(${test_name})  # 关键调用
    # 链接依赖库（PUBLIC表示传递依赖）
    target_link_libraries(${test_name} PRIVATE
            spdlog::spdlog
    )

    # 可选：添加编译定义（如开启SPDLOG特定功能）
    target_compile_definitions(${test_name} PRIVATE
            SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_DEBUG
    )

    # 可选：IDE分组（CLion/VSCode中显示清晰）
    set_property(TARGET ${test_name} PROPERTY FOLDER ${MODULE_NAME})
endforeach()

# 4. 可选：添加示例代码的编译选项检查
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(${test_name} PRIVATE -Wall -Wextra)
endif()