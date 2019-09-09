#include "XLog.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"

void vagt::log::init(const std::string& path, int logFileSize, int logFileNum)
{
    auto logger = spdlog::rotating_logger_mt("xvagt", path, logFileSize, logFileNum);
    spdlog::set_default_logger(logger);
    spdlog::default_logger()->set_pattern("%^%L%$ [%Y-%m-%d %H:%M:%S.%e][%t][%@] %v");
    spdlog::default_logger()->flush_on(spdlog::level::info);
    spdlog::default_logger()->set_level(spdlog::level::info);
    /*
    spdlog::default_logger()->set_pattern("%^%L%$ [%Y-%m-%d %H:%M:%S.%e][%t][%@] %v");
    spdlog::flush_on(spdlog::level::info);
    spdlog::set_level(spdlog::level::info);
    */
}

void vagt::log::setLevel(vagt::log::XLogLevel level)
{
    spdlog::default_logger()->set_level(spdlog::level::level_enum(level));
    spdlog::default_logger()->flush_on(spdlog::level::level_enum(level));
}

