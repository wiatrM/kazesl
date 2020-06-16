#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <memory>

#include <server/Server.hpp>



namespace kazesl
{

class TestServer
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


// ------------------------------------------

TEST_F(TestServer, TestServerInstance)
{
    logger->initGeneralLogger();

}

}
