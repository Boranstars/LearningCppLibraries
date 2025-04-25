//
// Created by Boran on 2025/4/25.
//
#include <nlohmann/json.hpp>
#include <iostream>

using json = nlohmann::json;

int main() {
    // 原始JSON文档
    json doc = {
        {"name", "Alice"},
        {"age", 28},
        {"address", {
            {"street", "123 Main St"},
            {"city", "Boston"}
        }},
        {"scores", {95, 88, 92}}
    };

    // JSON Patch操作序列
    json patch = {
        // 1. 添加新字段
        {"op", "add"}, {"path", "/email"}, {"value", "alice@example.com"},
        
        // 2. 替换已有字段
        {"op", "replace"}, {"path", "/age"}, {"value", 29},
        
        // 3. 移动字段
        {"op", "move"}, {"from", "/address/city"}, {"path", "/city"},
        
        // 4. 复制数组元素
        {"op", "copy"}, {"from", "/scores/0"}, {"path", "/topScore"},
        
        // 5. 删除字段
        {"op", "remove"}, {"path", "/address/street"}
    };

    // 应用JSON Patch
    json patched_doc = doc.patch(patch);
    
    std::cout << "Original document:\n" << doc.dump(2) << "\n\n";
    std::cout << "Patch operations:\n" << patch.dump(2) << "\n\n";
    std::cout << "Patched document:\n" << patched_doc.dump(2) << "\n";

    return 0;
}
