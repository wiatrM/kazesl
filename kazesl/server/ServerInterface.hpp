/*
 * Distributed under the MIT License (See accompanying file /LICENSE)
 * Copyright (c) 2018 Kaze Organization
 * Authors: Michał Wiatr
 */

#ifndef KAZESL_SERVER_INTERFACE
#define KAZESL_SERVER_INTERFACE

#include <vector>
#include <boost/asio.hpp>

namespace kazesl {

using Endpoints = std::vector<boost::asio::ip::tcp::endpoint>;

class ServerInterface
{
  public:
    ServerInterface() = default;

    virtual ~ServerInterface() = default;

    /**
     * @brief set-up server endpoints
     * @param v List of endpoints (ports) to start the server and bind
     * @return Endpoints
     */
    virtual Endpoints
    endpoints(std::vector<unsigned int> const &v) = 0;

    /**
     * @brief Closing the server
     */
    virtual void
    close() = 0;
};

}
#endif
