#include <memory>
#include "spdlog/async.h"
#include "spdlog/async_logger.h"
#include "spdlog/common.h"
#include "spdlog/logger.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

int main(int argc, const char **argv) {

    try {
        

        // 创建控制台Sink
        auto console_log_sink =
            std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
            
        console_log_sink->set_level(spdlog::level::warn);
        console_log_sink->set_pattern("[%Y-%m-%d %H:%M:%S] [%^%l%$] %v");

        // 创建文件Sink
        auto file_sink = std::make_shared<
            spdlog::sinks::basic_file_sink_mt>(
            "logs/async_log.log");

        file_sink->set_level(spdlog::level::info);
        file_sink->set_pattern("[%Y-%m-%d %H:%M:%S] [%^%l%$] %v");


        
        spdlog::sinks_init_list sinks = {console_log_sink, file_sink};

        spdlog::logger  my_logger("my_multi_log", sinks.begin(), sinks.end());

        my_logger.set_level(spdlog::level::debug);
        my_logger.info("this only goes to the file");
        my_logger.warn("this goes to both console and file");
       
    } catch (const spdlog::spdlog_ex &ex) {
        std::printf("Log initialization failed: %s\n", ex.what());
        return 1;
    }

    return 0;
}