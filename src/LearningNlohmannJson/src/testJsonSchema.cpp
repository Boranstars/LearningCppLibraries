#include <iostream>
#include <nlohmann/json.hpp>
#include <nlohmann/json-schema.hpp>

using json = nlohmann::json;
using validator = nlohmann::json_schema::json_validator;

int main() {
    // 1. 定义JSON Schema
    json schema = R"({
        "$schema": "http://json-schema.org/draft-07/schema#",
        "type": "object",
        "properties": {
            "name": {
                "type": "string",
                "minLength": 1
            },
            "age": {
                "type": "integer",
                "minimum": 0
            },
            "email": {
                "type": "string",
                "format": "email"
            }
        },
        "required": ["name", "age"],
        "additionalProperties": false
    })"_json;

    // 2. 创建验证器
    validator val;
    try {
        val.set_root_schema(schema);
    } catch (const std::exception &e) {
        std::cerr << "Schema验证失败: " << e.what() << std::endl;
        return 1;
    }

    // 3. 测试有效JSON
    json valid_data = {
        {"name", "John Doe"},
        {"age", 30},
        {"email", "john@example.com"}
    };

    try {
        val.validate(valid_data);
        std::cout << "有效数据验证通过" << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "验证错误: " << e.what() << std::endl;
    }

    // 4. 测试无效JSON
    json invalid_data = {
        {"name", ""},  // 空字符串
        {"age", -5},   // 负数
        {"email", "invalid"}
    };

    try {
        val.validate(invalid_data);
    } catch (const std::exception &e) {
        std::cerr << "验证错误: " << e.what() << std::endl;
    }

    return 0;
}
