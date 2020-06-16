/*
 * Distributed under the MIT License (See accompanying file /LICENSE )
 * Copyright (c) 2018 Kaze Organization
 * Authors: Michał Wiatr
 */
#ifndef KAZESL_IOSERVICE
#define KAZESL_IOSERVICE

#include <optional>
#include <thread>
#include <boost/asio/io_service.hpp>
#include <vector>

namespace kazesl
{

class IOService
{
  public:
    boost::asio::io_service &
    io_service()
    {
        return io_service_;
    }

  protected:
    IOService(std::size_t threads);
    virtual
    ~IOService();

  private:
    std::vector<std::thread> threads_;
    std::optional<boost::asio::io_service::work> work_;
    boost::asio::io_service io_service_;
};
}
#endif
