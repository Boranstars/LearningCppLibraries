//
// Created by Boran on 2025/4/20.
//
#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include <filesystem>
using json = nlohmann::json;

int main ()
{
	json data;
	data["name"] = "John Doe";
	data["age"] = 30;
	data["is_student"] = false;
	data["courses"] = {"Math", "Science", "History"};
	data["address"]["street"] = "123 Main St";

	std::string compact_json = data.dump(); // 紧凑格式
	std::string pretty_json = data.dump(4); // 美化格式，缩进4个空格

	std::cout << "Compact JSON:\n" << compact_json << std::endl;
	std::cout << "Pretty JSON:\n" << pretty_json << std::endl;

	// 将 JSON 数据写入文件
	std::filesystem::create_directories("data");
	std::ofstream file("data/data.json", std::ios::out | std::ios::trunc);
	if (file.is_open()) {
		file << pretty_json;
		file.close();
		std::cout << "JSON data written to file." << std::endl;
	} else {
		std::cerr << "Error opening file for writing." << std::endl;
	}
}
