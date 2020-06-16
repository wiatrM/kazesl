/*
 * Distributed under the MIT License (See accompanying file /LICENSE)
 * Copyright (c) 2018 Kaze Organization
 * Authors: Michał Wiatr
 */

#include <core/Stoppable.hpp>
#include <cassert>

namespace kazesl
{

Stoppable::Stoppable(std::string name)
    : name_(name)
{
}

Stoppable::~Stoppable()
{
    stopped();
}

bool
Stoppable::isStopping() const
{
    return calledStop_;
}

bool
Stoppable::isStopped() const
{
    return stopped_;
}

void
Stoppable::prepare()
{
    onPrepare();
}

void
Stoppable::start()
{
    started_ = true;
    onStart();
}

void
Stoppable::stop()
{
    // We shall be started
    assert (started_);

    onStop();
    stopped();
}

void
Stoppable::stopped()
{
    stopped_ = true;
}

void
Stoppable::onPrepare()
{
}

void
Stoppable::onStart()
{
}

void
Stoppable::onStop()
{

}
}
