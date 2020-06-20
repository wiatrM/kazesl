/*
 * Distributed under the MIT License (See accompanying file /LICENSE )
 * Copyright (c) 2018 Kaze Organization
 * Authors: Michał Wiatr
 */

#include <common/Logger.hpp>

namespace kazeCommon
{

Logger::Logger(LogSeverity level, bool console)
    :thresh_(level)
{
    // Do we need console output?
    if(console)
    {
#ifdef _WIN32
        auto color_sink = std::make_shared<spdlog::sinks::wincolor_stdout_sink_mt>();
#else
        auto color_sink = std::make_shared<spdlog::sinks::ansicolor_stdout_sink_mt>();
#endif
        sinks_.push_back(color_sink);
    }

    // Push some more custom Sinks
    initAdditionalSinks();

    // Set global logging pattern
    spdlog::set_pattern("* [%H:%M:%S][%l][t:%t][%n] %v");
    spdlog::set_level(static_cast<spdlog::level::level_enum>(level));
}

Logger::~Logger()
{
    spdlog::drop_all();
}

std::shared_ptr<spdlog::logger>
Logger::journal(std::string name)
{
    std::lock_guard<std::mutex> lock(mutex_);
    std::shared_ptr<spdlog::logger> journal = spdlog::get(name);
    if (journal == nullptr)
    {
        journal = std::make_shared<spdlog::logger>(name, begin(sinks_), end(sinks_));
        //spdlog::create(name, sinks_);
    }

    return journal;
}

void
Logger::initAdditionalSinks()
{
    if(!silent_)
    {
        // Init file sink
        // @TODO: this shall be configured when config class will be intruduced in another FR.
        sinks_.push_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/multisink.txt", true));
    }
#if defined(_DEBUG) && defined(_MSC_VER)
    auto debug_sink = std::make_shared<spdlog::sinks::msvc_sink_mt>();
    sinks_.push_back(debug_sink);
#endif
}

std::shared_ptr<spdlog::logger>
Logger::initGeneralLogger()
{
    std::lock_guard<std::mutex> lock(mutex_);
    // Init the 'general' logger with avaliable sinks_*
    logger_ = spdlog::get("general");

    if (logger_ == nullptr)
    {
        logger_ = std::make_shared<spdlog::logger>("general", begin(sinks_), end(sinks_));
    }

    return logger_;
}

};
