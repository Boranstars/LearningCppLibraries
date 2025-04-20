#include <cmath>
#include <csignal>
#include <cstdlib>
#include <iostream>
#include <memory>
#include "spdlog/async.h"
#include "spdlog/common.h"
#include "spdlog/logger.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"
#include <sstream>
#include <string>
#include <thread>
#include <type_traits>

class Calculator {
  public:
    Calculator(const std::string &logger_name) {

        try {
            this->_logger = spdlog::get(logger_name);

            std::ostringstream thread_id_str;
            thread_id_str << std::this_thread::get_id(); // 转换线程ID为字符串

            this->_logger->info("Start at thread {}", thread_id_str.str());
        } catch (const spdlog::spdlog_ex &ex) {
            std::cerr << "Error occured when create calculator:" << ex.what()
                      << std::endl;
        }
    }
    Calculator(Calculator &&) = default;
    Calculator(const Calculator &) = default;
    Calculator &operator=(Calculator &&) = default;
    Calculator &operator=(const Calculator &) = default;
    ~Calculator() {
        this->_logger->flush();
    }

    template <typename T1, typename T2>
    auto getPraseValue(const T1 a, const T2 b, const char op) const;

    void PraseInput(std::string &input) const;

  private:
    // std::shared_ptr<spdlog::logger> calculator_logger;
    // std::shared_ptr<spdlog::logger> result_logger;
    // std::shared_ptr<spdlog::logger> error_logger;
    std::shared_ptr<spdlog::logger> _logger;
    // std::string name = "Calculator";
};

template <typename T1, typename T2>
auto Calculator::getPraseValue(const T1 a, const T2 b, const char op) const {
    using return_type = typename std::common_type<T1, T2>::type;
    return_type result;
    switch (op) {
    case '+':
        result = static_cast<return_type>(a) + static_cast<return_type>(b);

        break;
    case '-':
        result = static_cast<return_type>(a) - static_cast<return_type>(b);

        break;
    case '*':
        result = static_cast<return_type>(a) * static_cast<return_type>(b);
        break;
    case '/':
        if (b == 0) {
            this->_logger->warn("devide by zero");
            return std::numeric_limits<return_type>::infinity();
        }
        result =
            static_cast<return_type>(a) / (static_cast<return_type>(b) * 1.0l);
        break;
    default:
        this->_logger->error("Unkonw opreation {}", op);
        return std::numeric_limits<return_type>::quiet_NaN(); // 返回 NaN
        break;
    }
    this->_logger->info("result : {0} ({1})", result, typeid(result).name());
    return result;
}

void Calculator::PraseInput(std::string &input) const {
    // 清理输入，去除无效字符
    input.erase(std::remove_if(input.begin(), input.end(),
                               [](unsigned char c) {
                                   return !std::isprint(c); // 去掉不可打印字符
                               }),
                input.end());

    this->_logger->info("Get input: {}", input);

    // 使用 std::istringstream 来解析输入
    std::istringstream stream(input);
    double a, b;
    char op;

    // 从输入流中读取操作数和操作符
    if (!(stream >> a >> op >> b)) {
        std::cout << "Invalid input format!" << std::endl;
        this->_logger->error("Invalid input format: {}", input);
        return;
    }

    // 调用 getPraseValue 进行计算
    auto result = getPraseValue(a, b, op);

    // 检查结果是否为无穷大或 NaN
    if (std::isinf(result) || std::isnan(result)) {
        this->_logger->error("Fail to get the result of operation: {}", input);
        return;
    }

    // 打印结果
    this->_logger->info("Result of {} : {} ({})", input, result,
                        typeid(result).name());
    std::cout << "Result: " << result << std::endl;
}

// 定义信号处理函数
void signalHandler(int signal) {
    std::cerr << "Signal " << signal << " detected. Shutting down...\n";

    // 刷新所有日志器
    spdlog::shutdown();

    exit(signal);
}



void cleanup() {
    std::cerr << "Cleaning up resources...\n";
    spdlog::shutdown();
}
int main(int argc, const char **argv) {
    // 注册清理函数
    std::atexit(cleanup);
    // 捕获常见信号
    std::signal(SIGINT, signalHandler);
    std::signal(SIGSEGV, signalHandler);
    std::signal(SIGABRT, signalHandler);

    std::string logPath = "logs/calculator.log";
    std::string logName = "Calculator";

    try {
        auto calculator_logger_sink =
            std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
                logPath, 1024 * 1024 * 5, 3);
        calculator_logger_sink->set_level(spdlog::level::info);
        calculator_logger_sink->set_pattern("[%Y-%m-%d %H:%M:%S] [%^%l%$] %v");

        auto calculator_logger =
            std::make_shared<spdlog::logger>(logName, calculator_logger_sink);

        calculator_logger->flush_on(spdlog::level::err);
        spdlog::register_logger(calculator_logger);

    } catch (const spdlog::spdlog_ex &ex) {
        std::cerr << "Log initialization failed: " << ex.what() << std::endl;
        return 1;
    }

    Calculator calc(logName);
    std::string input;
    std::cout << "Enter the operation" << std::endl;

    try {
        int counter = 0;
        while (std::getline(std::cin, input) && input != "quit") {
            ++counter;
            // if (counter == 2) {
            //     exit(1);
            // }
            calc.PraseInput(input);
        }
    } catch (const std::exception &ex) {
        spdlog::error("Runtime error: {}", ex.what());
        spdlog::shutdown();
        return 1;
    }

    return 0;
}