/*
 * Distributed under the MIT License (See accompanying file /LICENSE)
 * Copyright (c) 2018 Kaze Organization
 * Authors: Michał Wiatr
 */

#ifndef KAZESL_STOPPABLE
#define KAZESL_STOPPABLE

#include <atomic>
#include <chrono>
#include <future>

namespace kazesl
{

class Stoppable
{
  public:
    Stoppable(std::string name);

    virtual
    ~Stoppable();

    bool started() const
    {
        return started_;
    }

    bool
    isStopping() const;
    bool
    isStopped() const;

    void prepare();
    void start();
    void stop();
    void stopped();

  protected:
    // Stoppable name for log
    std::string name_;
  private:

    // Overrides..
    virtual void
    onPrepare();

    virtual void
    onStart();

    virtual void
    onStop();

    std::atomic<bool> prepared_{false};
    std::atomic<bool> started_{false};
    std::atomic<bool> stopped_{false};
    std::atomic<bool> calledStop_{false};

    std::mutex m_;
    std::condition_variable cv_;
};
}

#endif
