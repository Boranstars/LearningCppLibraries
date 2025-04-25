#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/chrono.h>
#include <fmt/ranges.h>
#include <vector>
#include <chrono>

// 自定义类型格式化
struct Point {
    double x, y;
};

template <>
struct fmt::formatter<Point> {
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }
    
    template <typename Context>
    auto format(const Point& p, Context& ctx) const {
        return format_to(ctx.out(), "({:.1f}, {:.1f})", p.x, p.y);
    }
};

void test_advanced_features() {
    // 自定义类型格式化
    Point p{1.5, 2.5};
    fmt::print("Point: {}\n", p);
    
    // 编译时格式化
    char buffer[64] = {0};
    fmt::format_to(buffer, "Compile-time: {}", 42);
    fmt::print("{}\n", buffer);
    
    // 范围格式化
    std::vector<int> v = {1, 2, 3};
    fmt::print("Vector: {}\n", fmt::join(v, ", "));
    
    // 日期时间格式化
    using namespace std::chrono;
    auto now = system_clock::now();
    fmt::print("Current time: {:%Y-%m-%d %H:%M:%S}\n", now);
}

int main() {
    test_advanced_features();
    return 0;
}
