/*
 * Distributed under the MIT License (See accompanying file /LICENSE)
 * Copyright (c) 2018 Kaze Organization
 * Authors: Michał Wiatr
 */

#include <server/Server.hpp>

namespace kazesl
{

Server::Server(io_service &io_service, kazeCommon::journal j_)
    : Stoppable("Server"),
      io_service_(io_service),
      log_(j_),
      work_(io_service)
{
    start();
}

Server::~Server()
{
    stop();
    work_ = std::nullopt;
}

Endpoints
Server::endpoints(std::vector<unsigned int> const &v)
{
}

void Server::close()
{
}

std::unique_ptr<Server>
create_Server(boost::asio::io_service &io_service, kazeCommon::journal journal)
{
    return std::make_unique<Server>(
        io_service, journal);
}

// Stoppable

void Server::onStart()
{
    log_->info("HTTP/HTTPs/WebSocket Server is starting...");
}
}
