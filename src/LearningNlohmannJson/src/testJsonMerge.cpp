//
// Created by Boran on 2025/4/25.
//
#include <nlohmann/json.hpp>
#include <iostream>

using json = nlohmann::json;

int main() {
    // 原始文档
    json original = {
        {"title", "Goodbye!"},
        {"author", {
            {"givenName", "John"},
            {"familyName", "Doe"}
        }},
        {"tags", {"example", "sample"}},
        {"content", "This will be unchanged"}
    };

    // 1. 基本合并
    json patch = {
        {"title", "Hello!"},
        {"phoneNumber", "+01-123-456-7890"},
        {"author", {
            {"familyName", nullptr}  // 删除字段
        }}
    };

    json result = original.patch(patch);
    std::cout << "After basic merge:\n" << result.dump(2) << "\n\n";

    // 2. 数组替换
    patch = {
        {"tags", {"test"}}
    };
    result = original.patch(patch);
    std::cout << "After array replacement:\n" << result.dump(2) << "\n\n";

    // 3. 嵌套对象合并
    patch = {
        {"author", {
            {"additionalName", "Middle"}
        }}
    };
    result = original.patch(patch);
    std::cout << "After nested merge:\n" << result.dump(2) << "\n\n";

    // 4. 删除整个对象
    patch = {
        {"author", nullptr}
    };
    result = original.patch(patch);
    std::cout << "After object removal:\n" << result.dump(2) << "\n";

    return 0;
}
