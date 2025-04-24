# 1. 声明依赖（替换示例）
find_package(nlohmann_json REQUIRED)  # 例如 nlohmann_json 3.11.2

# 2. 获取当前模块名（自动识别目录名）
get_filename_component(MODULE_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

# 3. 自动编译所有.cpp文件
file(GLOB TEST_SOURCES src/*.cpp)
foreach(test_source ${TEST_SOURCES})
    get_filename_component(test_name ${test_source} NAME_WE)

    # 创建可执行文件
    add_executable(${test_name} ${test_source})
    # 自动为每个模块创建独立输出目录
    setup_module_outputs(${test_name})  # 关键调用
    # 4. 链接库（替换为库的目标名称）
    target_link_libraries(${test_name} PRIVATE
            nlohmann_json::nlohmann_json
            fmt::fmt
    )

    # 5. 库特定编译定义（可选）
    target_compile_definitions(${test_name} PRIVATE
        # 例如 JSON_USE_IMPLICIT_CONVERSIONS=1
    )

    # 6. IDE分组（自动使用模块名,可选）
    set_property(TARGET ${test_name} PROPERTY FOLDER ${MODULE_NAME})
endforeach()

# 7. 编译器检查（可选）
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(${test_name} PRIVATE -Wall -Wextra)
endif()