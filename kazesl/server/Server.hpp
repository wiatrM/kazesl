/*
 * Distributed under the MIT License (See accompanying file /LICENSE)
 * Copyright (c) 2018 Kaze Organization
 * Authors: Michał Wiatr
 */

#ifndef KAZESL_SERVER
#define KAZESL_SERVER

#include <boost/beast.hpp>

#include <core/Stoppable.hpp>
#include <common/Logger.hpp>
#include <server/ServerInterface.hpp>

namespace kazesl
{

using namespace boost::asio;

class Server
    : public ServerInterface,
      Stoppable
{
  public:
    Server(io_service &io_service_, kazeCommon::journal j_);

    virtual ~Server();

    Endpoints
    endpoints(std::vector<unsigned int> const &v) override;

    void
    close() override;

  private:
    void onStart() override;

  private:
    kazeCommon::journal log_;
    io_service &io_service_;
    std::optional<io_service::work> work_;
};

std::unique_ptr<Server>
create_Server(boost::asio::io_service &io_service, kazeCommon::journal journal);
}
#endif
