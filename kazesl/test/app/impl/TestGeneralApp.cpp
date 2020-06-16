#include <gtest/gtest.h>
#include <memory>

#include <common/Logger.hpp>
#include <app/GeneralApp.hpp>

class GenerallAppTests : public ::testing::Test
{
protected:

    std::unique_ptr<kazeCommon::Logger> logger;

    virtual
    void
    SetUp()
    {
        logger = std::make_unique<kazeCommon::Logger>(kazeCommon::LogSeverity::trace, false);
        logger->initGeneralLogger();
    }
};

TEST_F(GenerallAppTests, TestAppInit)
{
    auto app = kazesl::create_GeneralApp(std::move(logger));
    ASSERT_TRUE(app != nullptr);
}

TEST_F(GenerallAppTests, TestGeneralIOService)
{
    auto app = kazesl::create_GeneralApp(std::move(logger));
    ASSERT_TRUE(app != nullptr);

    int universe = 42;
    app->get_io_service().dispatch([&](){
        std::cout << "I'm consumed by: " << std::this_thread::get_id() <<  " universe = " << universe << std::endl;
        universe--;
    });

    ASSERT_EQ(universe, 42);    // shall not be changed by dispatch
}
