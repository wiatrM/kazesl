#include <gtest/gtest.h>
#include <regex>


#include <common/Logger.hpp>
#include <spdlog/sinks/ostream_sink.h>

class LoggerTests : public ::testing::Test
{
protected:
    std::unique_ptr<kazeCommon::Logger> log;

    virtual
    void
    SetUp()
    {
        log = std::make_unique<kazeCommon::Logger>(kazeCommon::LogSeverity::trace, false); // Without console output
    }

    virtual
    void
    TearDown()
    {

    }
};

TEST_F(LoggerTests, init_logger)
{
    ASSERT_TRUE(log != nullptr);
}

TEST_F(LoggerTests, init_logger_with_sinks)
{
    EXPECT_TRUE(log != nullptr);
    std::shared_ptr<spdlog::logger> general_ = log->initGeneralLogger();
    ASSERT_TRUE(general_ != nullptr);
    ASSERT_TRUE(log->getSinks().size() == 1);
}

TEST_F(LoggerTests, test_log_with_osssink)
{
    std::ostringstream oss;
    log->addSink(std::make_shared<spdlog::sinks::ostream_sink_mt>(oss));

    std::shared_ptr<spdlog::logger> general_ = log->initGeneralLogger();
    ASSERT_TRUE(general_ != nullptr);
    ASSERT_TRUE(log->getSinks().size() == 2);

    // Regex match pattern
    std::regex re(".*\\[info\\].*\\[general\\].TEST1");
    std::cmatch m;
    log->log(kazeCommon::LogSeverity::info, "TEST{}", 1);
    ASSERT_TRUE(std::regex_search(oss.str().c_str(), m, re));
}

TEST_F(LoggerTests, test_log_info)
{
    std::ostringstream oss;
    log->addSink(std::make_shared<spdlog::sinks::ostream_sink_mt>(oss));
    std::shared_ptr<spdlog::logger> general_ = log->initGeneralLogger();

    std::regex re(".*\\[info\\].*\\[general\\].TEST1");
    std::cmatch m;
    log->info("TEST{}", 1);
    ASSERT_TRUE(std::regex_search(oss.str().c_str(), m, re));
}

TEST_F(LoggerTests, test_log_debug)
{
    std::ostringstream oss;
    log->addSink(std::make_shared<spdlog::sinks::ostream_sink_mt>(oss));
    std::shared_ptr<spdlog::logger> general_ = log->initGeneralLogger();

    std::regex re(".*\\[debug\\].*\\[general\\].TEST1");
    std::cmatch m;
    log->debug("TEST{}", 1);
    ASSERT_TRUE(std::regex_search(oss.str().c_str(), m, re));
}

TEST_F(LoggerTests, test_log_trace)
{
    std::ostringstream oss;
    log->addSink(std::make_shared<spdlog::sinks::ostream_sink_mt>(oss));
    std::shared_ptr<spdlog::logger> general_ = log->initGeneralLogger();

    std::regex re(".*\\[trace\\].*\\[general\\].TEST1");
    std::cmatch m;
    log->trace("TEST{}", 1);
    ASSERT_TRUE(std::regex_search(oss.str().c_str(), m, re));
}

TEST_F(LoggerTests, test_log_error)
{
    std::ostringstream oss;
    log->addSink(std::make_shared<spdlog::sinks::ostream_sink_mt>(oss));
    std::shared_ptr<spdlog::logger> general_ = log->initGeneralLogger();

    std::regex re(".*\\[error\\].*\\[general\\].TEST1");
    std::cmatch m;
    log->error("TEST{}", 1);
    ASSERT_TRUE(std::regex_search(oss.str().c_str(), m, re));
}

TEST_F(LoggerTests, test_log_fatal)
{
    std::ostringstream oss;
    log->addSink(std::make_shared<spdlog::sinks::ostream_sink_mt>(oss));
    std::shared_ptr<spdlog::logger> general_ = log->initGeneralLogger();

    std::regex re(".*\\[critical\\].*\\[general\\].TEST1");
    std::cmatch m;
    log->fatal("TEST{}", 1);
    ASSERT_TRUE(std::regex_search(oss.str().c_str(), m, re));
}

TEST_F(LoggerTests, test_new_journal)
{
    std::ostringstream oss;
    log->addSink(std::make_shared<spdlog::sinks::ostream_sink_mt>(oss));
    std::shared_ptr<spdlog::logger> general_ = log->initGeneralLogger();

    std::regex re(".*\\[critical\\].*\\[general\\].TEST1");
    std::cmatch m;
    log->fatal("TEST{}", 1);
    std::shared_ptr<spdlog::logger> new_journal = log->journal("networking");
    new_journal->info("New journal created!");
    ASSERT_TRUE(std::regex_search(oss.str().c_str(), m, re));
}
