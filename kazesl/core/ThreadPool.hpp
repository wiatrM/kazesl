/*
 * Distributed under the MIT License (See accompanying file /LICENSE)
 * Copyright (c) 2018 Kaze Organization
 * Authors: Michał Wiatr
 */

#ifndef KAZESL_THREADPOOL
#define KAZESL_THREADPOOL

#include <algorithm>
#include <atomic>
#include <memory>
#include <thread>
#include <utility>
#include <vector>
#include <future>
#include <boost/lockfree/queue.hpp>

#include <core/Stoppable.hpp>
#include <common/Logger.hpp>
#include <core/Job.hpp>

namespace kazesl
{

const unsigned int work_queue_length = 100; // @TODO, another config value

class ThreadPool
    : public Stoppable
{
  public:

    template <typename T>
    class FutureJob
    {
      public:
        FutureJob(std::future<T> &&future)
            : future_{std::move(future)}
        {
        }

        FutureJob(const FutureJob &rhs) = delete;
        FutureJob &operator=(const FutureJob &rhs) = delete;
        FutureJob(FutureJob &&other) = default;
        FutureJob &operator=(FutureJob &&other) = default;
        ~FutureJob(void)
        {
            if (future_.valid())
            {
                future_.get();
            }
        }

        auto get(void)
        {
            return future_.get();
        }

      private:
        std::future<T> future_;
    };

    using lfq = boost::lockfree::queue<JobInterface *>;
    using thread_ptr = std::unique_ptr<std::thread>;

    /**
     * @brief Default constructor with hardware_concurrency-1 threads as a workers
     */
    ThreadPool(kazeCommon::journal j_);

    /**
     * @brief Explicit constructor with numThreads as workers
     * @param numThreads Number of threads to run as workers
     */
    explicit ThreadPool(kazeCommon::journal j_, const std::uint32_t numThreads);

    ThreadPool(const ThreadPool &rhs) = delete;
    ThreadPool &operator=(const ThreadPool &rhs) = delete;

    virtual ~ThreadPool();

    /**
     * @brief Get workers count
     * @return std::size_t workers size
     */
    std::size_t
    workers_size()
    {
        return this->workers_.size();
    }

    /**
     * @brief Direct submit of job object
     * @param job job to submit
     */
    void submit(JobInterface *job);

    /**
     * @brief Submit job with lambda
     */
    template <typename Func, typename... Args>
    auto submit_l(Func &&func, JobType jt = jDefault, Args &&... args)
    {
        auto boundTask = std::bind(std::forward<Func>(func), std::forward<Args>(args)...);
        using ResultType = std::result_of_t<decltype(boundTask)()>;
        using PackagedTask = std::packaged_task<ResultType()>;
        using TaskType = ThreadJob<PackagedTask>;

        PackagedTask task{std::move(boundTask)};
        FutureJob<ResultType> result{task.get_future()};

        jobq_.push(new TaskType(std::move(task), jDefault));
        return result;
    }

  private:
    /**
     * Stoppable implementation
     */
    void
    onStop() override;
    void
    onStart() override;

    /**
     * @brief Destroy queue and join all running threads
     */
    void
    destroy();

  private:
    /**
     * @brief Thread worker method for pooling jobs and processing them
     */
    void worker(void);

    mutable lfq jobq_;
    std::atomic_bool done_;
    std::vector<thread_ptr> workers_;

    std::mutex mutex_;
    std::condition_variable cv_;
    kazeCommon::journal log;
};
}

#endif
