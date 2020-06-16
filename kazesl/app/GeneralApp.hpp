/*
 * Distributed under the MIT License (See accompanying file /LICENSE )
 * Copyright (c) 2018 Kaze Organization
 * Authors: Michał Wiatr
 */

#ifndef KAZESL_GENERAL_APP
#define KAZESL_GENERAL_APP

#include <boost/asio/signal_set.hpp>

#include <common/Logger.hpp>

#include <app/ApplicationInterface.hpp>

#include <core/Stoppable.hpp>
#include <core/IOService.hpp>
#include <core/ThreadPool.hpp>

#include <server/Server.hpp>

#include <memory>

namespace kazesl
{
using _l = kazeCommon::Logger;

class GeneralApp
    : public ApplicationInterface,
      public Stoppable,
      public IOService
{
private:

    boost::asio::signal_set signals_;
    std::atomic<bool> checkSigs_;

public:
    // application fields shall be accessable
    std::unique_ptr<_l> logger_;

    std::unique_ptr<ThreadPool> thread_pool_;
    std::unique_ptr<Server> server_;

    GeneralApp( // @TODO. config shall be passed here
        std::unique_ptr<_l> loggger);

    // ----------------------------
    // From Application Interface
    bool
    setup() override;

    void
    beforeStart() override;

    void
    run() override;

    void
    signalStop() override;

    kazeCommon::Logger &
    logger() override;

    boost::asio::io_service &
    get_io_service() override;
    // ----------------------------
    // Stoppable
    void
    onStart() override;

    void
    onStop() override;

    // Public method for intercept signals
    void
    signalled(const boost::system::error_code& ec, int signal_number);

    // ----------------------------
    ThreadPool&
    getThreadPool()
    {
        return *thread_pool_;
    }

};

std::unique_ptr<ApplicationInterface>
create_GeneralApp( // @TODO. config shall be passed here
    std::unique_ptr<_l> logger);
}

#endif
