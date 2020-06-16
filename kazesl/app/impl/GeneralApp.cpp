/*
 * Distributed under the MIT License (See accompanying file /LICENSE )
 * Copyright (c) 2018 Kaze Organization
 * Authors: Michał Wiatr
 */

#include <app/GeneralApp.hpp>
#include <app/gitversion.hpp>

namespace kazesl
{

// @TODO: Thiss shall be get from config
const std::size_t threadsNo = 2;

GeneralApp::GeneralApp( // @TODO. config shall be passed here
    std::unique_ptr<_l> logger)
    : IOService(threadsNo),
      logger_(std::move(logger)),
      Stoppable("GeneralApp"),
      signals_(io_service()),
      checkSigs_(true),
      thread_pool_(std::make_unique<ThreadPool>(
          logger_->journal("ThreadPool")
      )),
      server_(
        create_Server(
            io_service(),
            logger_->journal("Server")
        )
      )
{
}

bool
GeneralApp::setup()
{
    // Intercept CTRL-C to close application
    signals_.add(SIGINT);
    signals_.async_wait(std::bind(&GeneralApp::signalled, this,
                                  std::placeholders::_1, std::placeholders::_2));

    return true;
}

void
GeneralApp::beforeStart()
{
    logger_->info("KazeSL is starting, version: {}, on branch: {}", GIT_VERSION, GIT_BRANCH);
    start();
}

void
GeneralApp::run()
{
    logger_->info("Entering IOService main loop.");
    io_service()
        .run();
}

void
GeneralApp::signalStop()
{
    io_service().stop();
}

void
GeneralApp::signalled(const boost::system::error_code& ec, int signal_number)
{
    if (ec == boost::asio::error::operation_aborted)
    {
        // Signal aborted, its ok.
    }
    else if (ec)
    {
        logger_->info("Got signal.. {} with error {}", signal_number, ec.message());
    }
    else
    {
        logger_->info("Got signal.. {}", signal_number);
        signalStop();
    }
}

kazeCommon::Logger &
GeneralApp::logger()
{
    return *logger_;
}


boost::asio::io_service &
GeneralApp::get_io_service()
{
    return io_service();
}

/**
 * Stoppable overrides
 */

void
GeneralApp::onStart()
{
    logger_->debug("{} onStart", name_);
}

void
GeneralApp::onStop()
{
    logger_->debug("{} onStop", name_);
    thread_pool_->stop();
}

std::unique_ptr<ApplicationInterface>
create_GeneralApp(std::unique_ptr<kazeCommon::Logger> logger)
{
    return std::make_unique<GeneralApp>(
        std::move(logger));
}
}
