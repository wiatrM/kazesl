/*
 * Distributed under the MIT License (See accompanying file /LICENSE )
 * Copyright (c) 2018 Kaze Organization
 * Authors: Michał Wiatr
 */

#ifndef KAZESL_LCOMMON_LOGGER
#define KAZESL_LCOMMON_LOGGER

//#include <spdlog/fmt/ostr.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>

#include <string>
#include <mutex>

namespace kazeCommon {

enum class LogSeverity
{
    trace = spdlog::level::level_enum::trace,
    debug = spdlog::level::level_enum::debug,
    info = spdlog::level::level_enum::info,
    error = spdlog::level::level_enum::err,
    fatal = spdlog::level::level_enum::critical
};

class Logger
{
public:
    using sink = spdlog::sink_ptr;

private:
    std::mutex mutable mutex_;
    std::shared_ptr<spdlog::logger> logger_{nullptr};
    std::vector<sink> sinks_;

    // Silent mode
    bool silent_ = false;

    // Logging severity threshold
    LogSeverity thresh_;

public:
    Logger(LogSeverity level, bool console);

    Logger(Logger const&) = delete;
    Logger& operator= (Logger const&) = delete;

    virtual
    ~Logger();

    std::shared_ptr<spdlog::logger>
    initGeneralLogger();

    /**
     * Set/get custom logger name with all sinks_ as new journal
     */
    std::shared_ptr<spdlog::logger>
    journal(std::string name);

    template <typename Arg1, typename... Args>
    void
    log(const LogSeverity level, const Arg1 &arg1, const Args &... args)
    {
        logger_->log(static_cast<spdlog::level::level_enum>(level),
                          arg1, args...);
    }

    /**
     * Log info
     */
    template <typename Arg1, typename... Args>
    void
    info(const Arg1 &arg1, const Args &... args)
    {
        log(LogSeverity::info, arg1, args...);
    }

    template <typename Arg1>
    void
    info(const Arg1 &arg1)
    {
        info("{}", arg1);
    }

    /**
     * Log trace
     */
    template <typename Arg1, typename... Args>
    void
    trace(const Arg1 &arg1, const Args &... args)
    {
        log(LogSeverity::trace, arg1, args...);
    }

    template <typename Arg1>
    void
    trace(const Arg1 &arg1)
    {
        trace("{}", arg1);
    }

    /**
     * Log debug
     */
    template <typename Arg1, typename... Args>
    void
    debug(const Arg1 &arg1, const Args &... args)
    {
        log(LogSeverity::debug, arg1, args...);
    }

    template <typename Arg1>
    void
    debug(const Arg1 &arg1)
    {
        debug("{}", arg1);
    }

    /**
     * Log error
     */
    template <typename Arg1, typename... Args>
    void
    error(const Arg1 &arg1, const Args &... args)
    {
        log(LogSeverity::error, arg1, args...);
    }

    template <typename Arg1>
    void
    error(const Arg1 &arg1)
    {
        error("{}", arg1);
    }

    /**
     * Log fatal
     */
    template <typename Arg1, typename... Args>
    void
    fatal(const Arg1 &arg1, const Args &... args)
    {
        log(LogSeverity::fatal, arg1, args...);
    }

    template <typename Arg1>
    void
    fatal(const Arg1 &arg1)
    {
        fatal("{}", arg1);
    }

    void
    addSink(auto _sink)
    {
        sinks_.push_back(_sink);
    }

    std::vector<sink>
    getSinks()
    {
        return sinks_;
    }

private:
    void
    initAdditionalSinks();
};

using journal = std::shared_ptr<spdlog::logger>;

};
#endif
