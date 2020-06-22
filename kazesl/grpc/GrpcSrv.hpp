/*
 * Distributed under the MIT License (See accompanying file /LICENSE )
 * Copyright (c) 2020 Kaze Organization
 * Authors: Michał Wiatr
 */
#ifndef KAZESL_GRPCSRV
#define KAZESL_GRPCSRV

#include <Genera

namespace kazesl
{

class Processor
{
public:
    virtual ~Processor() = default;

    Processor() = default;

    Processor(const Processor&) = delete;

    Processor& operator=(const Processor&) = delete;

    // process the request
    virtual void process() = 0;

    virtual std::shared_ptr<Processor> clone() = 0;

    // is processing finished? If yes object will be deleted
    virtual bool isFinished() = 0;
};

class GrpcSrv
{
    explicit GrpcSrv(GeneralApp & app) : impl_(app);
};
}

#endif
