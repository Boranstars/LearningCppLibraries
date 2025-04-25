//
// Created by Boran on 2025/4/25.
//
#include <nlohmann/json.hpp>
#include <iostream>

using json = nlohmann::json;

int main() {
    // 创建复杂JSON文档
    json doc = {
        {"name", "Charlie"},
        {"age", 35},
        {"address", {
            {"street", "456 Oak Ave"},
            {"city", "Chicago"},
            {"zip", 60601}
        }},
        {"scores", {88, 92, 78, 95}},
        {"contacts", {
            {"email", "charlie@example.com"},
            {"phone", "555-1234"}
        }}
    };

    // 使用JSON Pointer访问数据
    
    // 1. 访问顶层字段
    nlohmann::json::json_pointer ptr("/name");
    std::cout << "Name: " << doc[ptr] << "\n";
    
    // 2. 访问嵌套对象
    ptr = nlohmann::json::json_pointer("/address/city");
    std::cout << "City: " << doc[ptr] << "\n";
    
    // 3. 访问数组元素
    ptr = nlohmann::json::json_pointer("/scores/1");
    std::cout << "Second score: " << doc[ptr] << "\n";
    
    // 4. 检查路径是否存在
    ptr = nlohmann::json::json_pointer("/contacts/email");
    if (doc.contains(ptr)) {
        std::cout << "Email exists: " << doc[ptr] << "\n";
    }
    
    // 5. 修改值
    ptr = nlohmann::json::json_pointer("/age");
    doc[ptr] = 36;
    std::cout << "Updated age: " << doc[ptr] << "\n";
    
    // 6. 添加新字段
    ptr = nlohmann::json::json_pointer("/address/state");
    doc[ptr] = "IL";
    
    // 7. 删除字段
    ptr = nlohmann::json::json_pointer("/contacts/phone");
    doc.erase(ptr);
    
    std::cout << "\nFinal document:\n" << doc.dump(2) << "\n";

    return 0;
}
