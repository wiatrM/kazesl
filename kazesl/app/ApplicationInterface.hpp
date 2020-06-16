/*
 * Distributed under the MIT License (See accompanying file /LICENSE)
 * Copyright (c) 2018 Kaze Organization
 * Authors: Michał Wiatr
 */

#ifndef KAZESL_APPLICATION_INTERFACE
#define KAZESL_APPLICATION_INTERFACE

#include <boost/asio/io_service.hpp>
#include <common/Logger.hpp>

class ApplicationInterface
{
  public:
    ApplicationInterface() = default;

    virtual
    ~ApplicationInterface() = default;

    // Setup all application env
    virtual
    bool
    setup() = 0;

    /**
     * @brief This method will run before start of the application- can set-up dependencies and start needed objects
     */
    virtual
    void
    beforeStart() = 0;

    /**
     * @brief This method will run the application
     */
    virtual
    void
    run() = 0;

    /**
     * @brief signal stop handling
     */
    virtual
    void
    signalStop() = 0;

    /**
     * @brief get io_service
     */
    virtual
    boost::asio::io_service &
    get_io_service() = 0;

    //
    virtual
    kazeCommon::Logger &logger() = 0;
};

#endif
