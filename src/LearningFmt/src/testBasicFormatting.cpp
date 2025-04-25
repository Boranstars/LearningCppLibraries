#include <fmt/core.h>
#include <fmt/format.h>
#include <iostream>
#include <string>

// 基础格式化测试
void test_basic_formatting() {
    // 位置参数
    fmt::print("Hello, {}!\n", "world");
    fmt::print("{1}, {0}!\n", "world", "Hello");
    
    // 命名参数
    fmt::print("Hello, {name}!\n", fmt::arg("name", "fmt"));
    
    // 格式规范
    fmt::print("{:.2f}\n", 3.1415926);  // 保留两位小数
    fmt::print("{:>10}\n", "right");    // 右对齐
    fmt::print("{:*^10}\n", "center");  // 居中并用*填充
    
    // 类型安全输出
    fmt::print("int: {}, double: {}, string: {}\n", 42, 3.14, "text");
}

int main() {
    test_basic_formatting();
    return 0;
}
