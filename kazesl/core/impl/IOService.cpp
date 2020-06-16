/*
 * Distributed under the MIT License (See accompanying file /LICENSE)
 * Copyright (c) 2018 Kaze Organization
 * Authors: Michał Wiatr
 */

#include <core/IOService.hpp>

namespace kazesl
{

IOService::IOService(std::size_t threads)
{
    // Emplace io_service_ for future work
    work_.emplace(io_service_);
    threads_.reserve(threads);

    // Start of threads that will handle io_service work
    while (threads--)
        threads_.emplace_back(
            [this, threads]() {
                this->io_service_.run();
            });
}

IOService::~IOService()
{
    work_ = std::nullopt;
    for (auto &_ : threads_)
        _.join();
}
}
