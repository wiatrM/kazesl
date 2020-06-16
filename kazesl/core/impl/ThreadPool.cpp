/*
 * Distributed under the MIT License (See accompanying file /LICENSE)
 * Copyright (c) 2018 Kaze Organization
 * Authors: Michał Wiatr
 */

#include <core/ThreadPool.hpp>
#include <cassert>

namespace kazesl
{

ThreadPool::ThreadPool(kazeCommon::journal j_)
    : ThreadPool(j_, std::max(std::thread::hardware_concurrency(), 2u) - 1u)
{
}

ThreadPool::ThreadPool(kazeCommon::journal j_, const std::uint32_t numThreads)
    : jobq_(work_queue_length),
      done_{false},
      workers_{},
      Stoppable("ThreadPool"),
      log(j_)
{
    log->debug("ThreadPool initialisation. Number of workers: {}.", numThreads);
    try
    {
        for (std::uint32_t i = 0u; i < numThreads; ++i)
        {
            workers_.emplace_back(std::make_unique<std::thread>(std::bind(&ThreadPool::worker, this)));
        }
    }
    catch (...)
    {
        log->critical("Worker creation critical error, exiting...");
        destroy();
        throw;
    }
    start();
}

ThreadPool::~ThreadPool()
{
    stop();
}

void ThreadPool::submit(JobInterface* job)
{
    log->debug("Pushing job");
    jobq_.push(job);
}

void ThreadPool::worker(void)
{
    log->debug("Worker started, thread id: {}.", std::this_thread::get_id());

    // Atomic done_ indicates if threadpool shall be disabled
    JobInterface* job;

    while(!done_)
    {
        bool isPop = this->jobq_.pop(job);
        if(isPop)
        {
            log->debug("Processing job by worker: {}", std::this_thread::get_id());
            job->setup();
            job->execute();
            job->done();
        }

    }
    log->debug("Worker {} closed.", std::this_thread::get_id());
}

void ThreadPool::destroy()
{
    done_ = true;
    for(auto& worker : workers_)
    {
        worker->join();
    }
}

void ThreadPool::onStop()
{
    destroy();
}

void ThreadPool::onStart()
{

}

}
