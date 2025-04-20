#include <chrono>
#include <cstdio>
#include "spdlog/async.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/spdlog.h"
#include <thread>
int main(int argc, const char **argv) {

    try {
        auto async_file = spdlog::basic_logger_mt<spdlog::async_factory>(
            "async_file_log", "logs/async_log.log");
        for (size_t i = 1; i < 101; i++)
        {   
            async_file->info("async log message #{}", i);
            
            // std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }

        spdlog::drop_all();
    } catch (const spdlog::spdlog_ex &ex) {
        std::printf("Log initialization failed: %s\n", ex.what());
        return 1;
    }

    return 0;
}