//
// Created by Boran on 2025/4/20.
//
#include <nlohmann/json.hpp>
#include <iostream>
#include <fmt/core.h>
#include <fmt/ranges.h>

using json = nlohmann::json;

int main() {
	// 基本类型>json
	json j;
	j["integer"] = 42;
	j["float"] = 3.14;
	j["string"] = "Hello, World!";
	j["boolean"] = true;
	std::cout << j.dump(4) << std::endl;

	// json>基本类型
	json j2 = R"({"integer": 42, "float": 3.14, "string": "Hello, World!", "boolean": true})"_json;
	// _json 是一个用户定义的字面量，用于将字符串转换为 json 对象
	// 也可以使用 json::parse() 方法
	json j2_2 = json::parse(R"({"integer": 42, "float": 3.14, "string": "Hello, World!", "boolean": true})");

	// 可能会抛出异常
	try {
		int integer = j2["integer"]; // 直接转换
		float float_num = j2["float"].get<float>(); // 使用 get 方法转换(推荐)
		std::string str = j2["string"].get<std::string>(); // 使用 get 方法转换(推荐)
		bool boolean = j2.value("boolean", false); // 使用 value 方法转换,false 是默认值
		std::cout << j2.dump(4) << std::endl;
		fmt::print("Integer: {}, Float: {}, String: {}, Boolean: {}\n", integer, float_num, str, boolean);
	} catch (const json::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}


	// json作为一等公民
	json j3 = {
			{"name",       "John Doe"},
			{"age",        30},
			{"is_student", false},
			{"courses",    {"Math",                    "Science", "History"}},
			{"address",    {{"street", "123 Main St"}, {"city", "Anytown"}}}
	};
	std::cout << j3.dump(4) << std::endl;
	auto course = j3["courses"].at(0).get<std::string>(); // 使用 at 方法访问元素,不存在会抛出异常
	auto courses = j3["courses"].get<std::vector<std::string>>(); // 使用 get 方法转换为 vector
	fmt::print("First course: {},Courses: {}\n",
			   course,
			   fmt::join(courses, ", ")); // 使用 fmt::join 打印 vector
}