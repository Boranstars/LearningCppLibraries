//
// Created by Boran on 2025/4/20.
//
#include <nlohmann/json.hpp>
#include <iostream>

using json = nlohmann::json;

class Person {
public:
	std::string name;
	int age{};

	// 序列化函数
	friend void to_json(json& j, const Person& p) {
		j = json{{"name", p.name}, {"age", p.age}};
	}

	// 反序列化函数
	friend void from_json(const json& j, Person& p) {
		j.at("name").get_to(p.name);
		j.at("age").get_to(p.age);
	}
};

// 也可以使用宏定义来简化序列化和反序列化函数的编写，侵入式宏定义
class Student {
public:
	std::string name;
	int age{};
	std::string major;

	// 宏定义,自动生成序列化和反序列化函数,实际上和上面的函数是一样的
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Student, name, age, major)
};

// 非侵入式,假设我们无法修改 Point 类的定义
class Point {
public:
	int x;
	int y;
public:
	Point() = default;
	Point(int x, int y) : x(x), y(y) {}


};

// 非侵入式,通常用于无法修改类定义的情况
namespace nlohmann {
	template<>
	struct adl_serializer<Point> {
		static void to_json(json& j, const Point& p) {
			j = json{{"x", p.x}, {"y", p.y}};
		}

		static void from_json(const json& j, Point& p) {
			j.at("x").get_to(p.x);
			j.at("y").get_to(p.y);
		}
	};
}
int main() {
	// 序列化和反序列化自定义类型,使用非侵入式友元函数(特殊情况使用)
	Person p1{"John Doe", 30};
	json j1 = p1; // 序列化,自动调用 to_json 函数
	std::cout << "Serialized JSON: " << j1.dump(4) << std::endl;
	Person p2;
	p2 = j1.get<Person>();
	std::cout << "Deserialized Person: " << p2.name << ", " << p2.age
			  << std::endl;

	// 序列化和反序列化自定义类型,使用宏定义（推荐）
	Student s1{"Jane Doe", 22, "Computer Science"};
	json j2 = s1; // 序列化,自动调用 to_json 函数
	std::cout << "Serialized JSON: " << j2.dump(4) << std::endl;
	Student s2;
	s2 = j2.get<Student>(); // 反序列化,自动调用 from_json 函数

	std::cout << "Deserialized Student: " << s2.name << ", " << s2.age
			  << ", " << s2.major << std::endl;

	// 序列化和反序列化自定义类型,使用非侵入式,需要在头文件中定义
	Point point1{1, 2};
	json j3 = point1; // 序列化,自动调用 to_json 函数
	std::cout << "Serialized JSON: " << j3.dump(4) << std::endl;
	Point point2{0, 0};
	point2 = j3.get<Point>(); // 反序列化,自动调用 from_json 函数,这里需要Point类的默认构造函数
	std::cout << "Deserialized Point: " << point2.x << ", " << point2.y
			  << std::endl;

	return 0;
}