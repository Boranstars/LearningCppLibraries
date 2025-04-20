#include "spdlog/spdlog.h"

// 注意；这里直接将spdlog集成到系统中了.
int main(int argc, const char** argv) {

    spdlog::info("hello!");
    spdlog::error("some error message with arg: {}", argv[0]);
    return 0;
}