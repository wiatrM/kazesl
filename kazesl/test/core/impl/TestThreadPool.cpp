#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <memory>
#include <regex>
#include <thread>
#include <chrono>

#include <core/ThreadPool.hpp>
#include <spdlog/sinks/ostream_sink.h>

using ::testing::AtLeast;
using ::testing::InSequence;
using ::testing::Return;

namespace kazesl
{

class ThreadPoolTests
    : public ::testing::Test
{
  protected:
    std::unique_ptr<kazeCommon::Logger> logger;

    virtual void
    SetUp()
    {
        logger = std::make_unique<kazeCommon::Logger>(kazeCommon::LogSeverity::trace, false);
    }

    virtual void
    TearDown()
    {
    }
};

/***
 * Job Mock
*/
class JobMock
    : public JobInterface
{
  public:
    MOCK_METHOD0(setup, bool());
    MOCK_METHOD0(execute, void());
    MOCK_METHOD0(done, void());
};

// ------------------------------------------

TEST_F(ThreadPoolTests, TestThreadPoolInit)
{
    logger->initGeneralLogger();
    std::unique_ptr<ThreadPool> tp_ = std::make_unique<ThreadPool>(logger->journal("ThreadPoolTest"), 2); // Two threads for test

    ASSERT_TRUE(tp_ != nullptr);

    ASSERT_TRUE(tp_->workers_size() == 2);
}

TEST_F(ThreadPoolTests, TestThreadPoolLogs)
{
    std::ostringstream oss;
    logger->addSink(std::make_shared<spdlog::sinks::ostream_sink_mt>(oss));
    logger->initGeneralLogger();
    std::unique_ptr<ThreadPool> tp_ = std::make_unique<ThreadPool>(logger->journal("ThreadPoolTest"), 2); // Two threads for test

    std::regex re(".*ThreadPool initialisation.*2.*");
    std::cmatch m;

    ASSERT_TRUE(std::regex_search(oss.str().c_str(), m, re));
}

TEST_F(ThreadPoolTests, JobInit)
{
    JobMock job;
    logger->initGeneralLogger();
    std::unique_ptr<ThreadPool> tp_ = std::make_unique<ThreadPool>(logger->journal("ThreadPoolTest"), 2);

    // expect calls on interface methods...
    {
        InSequence jobSeq;
        EXPECT_CALL(job, setup())
            .Times(AtLeast(1))
            .WillOnce(Return(true));
        EXPECT_CALL(job, execute())
            .Times(AtLeast(1));
        EXPECT_CALL(job, done())
            .Times(AtLeast(1));
    }
    tp_->submit(&job);
    std::this_thread::sleep_for (std::chrono::microseconds(500)); // give some time for threads to process the Job
}

TEST_F(ThreadPoolTests, TestFloodJob)
{
    JobMock job;
    logger->initGeneralLogger();
    std::unique_ptr<ThreadPool> tp_ = std::make_unique<ThreadPool>(logger->journal("ThreadPoolTest"), 3); //  3 workers


    EXPECT_CALL(job, setup())
            .Times(AtLeast(8));
    EXPECT_CALL(job, execute())
            .Times(AtLeast(8));
    EXPECT_CALL(job, done())
            .Times(AtLeast(8));

    for (int i = 0; i < 10; i++ )
    {
        tp_->submit(&job);
    }

    std::this_thread::sleep_for (std::chrono::microseconds(1200)); // give some time for threads to process the Job
}

TEST_F(ThreadPoolTests, TestThreadJob)
{
    int universe = 0;   // creating value of int to pass as reference to job

    std::function<void()> test_42 = [&universe]() { universe = 42; };   // lambda to call in threadJob

    ThreadJob<std::function<void()>> _tt(std::move(test_42), jDefault);
    logger->initGeneralLogger();
    std::unique_ptr<ThreadPool> tp_ = std::make_unique<ThreadPool>(logger->journal("ThreadPoolTest"), 2); //  2 workers

    tp_->submit(&_tt);
    std::this_thread::sleep_for (std::chrono::microseconds(600));
    ASSERT_EQ(universe, 42);
}

TEST_F(ThreadPoolTests, TestLambdaJob)
{

    logger->initGeneralLogger();
    std::unique_ptr<ThreadPool> tp_ = std::make_unique<ThreadPool>(logger->journal("ThreadPoolTest"), 2); //  2 workers
    int universe = 0;
    ThreadPool::FutureJob<void> promise = tp_->submit_l([&universe](){
        universe = 42;
    });

    promise.get();  // this time we dont need to wait, .get will wait for job to finish
    ASSERT_EQ(universe, 42);
}
}
