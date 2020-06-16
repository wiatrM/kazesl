/*
 * Distributed under the MIT License (See accompanying file /LICENSE )
 * Copyright (c) 2018 Kaze Organization
 * Authors: Michał Wiatr
 */
#ifndef KAZESL_JOB
#define KAZESL_JOB

#include <utility>

namespace kazesl
{

enum JobType
{
    jDefault, // Default job type, normal priority

    // api related
    jHttp,    // HTTP based job
    jWallet,  // Wallet API based job
    jCommand, // Client/CLI command

    // Network/p2p related
    jPeerCommand, // Discovery,
    jGeneric      // Ping etc.

    // to be added...
};

class JobInterface
{
  public:
    JobInterface() = default;
    virtual ~JobInterface() = default;
    JobInterface(const JobInterface &rhs) = delete;
    JobInterface &operator=(const JobInterface &rhs) = delete;
    JobInterface(JobInterface &&other) = default;
    JobInterface &operator=(JobInterface &&other) = default;

    /**
     * @brief Set-up the job
     */
    virtual bool setup() = 0;

    /**
     * @brief Execute the job
     */
    virtual void execute() = 0;

    /**
     * @brief Called after execution
     */
    virtual void done() = 0;
};

class Job
    : public JobInterface
{
  public:
    Job(JobType jt);

    bool setup();
    void execute();
    void done();

    void type(JobType jt)
    {
        type_ = jt;
    }

    JobType type()
    {
        return type_;
    }
  protected:
    JobType type_;
};

/**
 * @brief Job that will execute function passed by constructor
 *
 * @tparam Func function type
 */
template <typename Func>
class ThreadJob
    : public Job
{
  public:
    ThreadJob(Func &&func, JobType job_)
        : func_{std::move(func)},
          Job(job_)
    {
    }

    ~ThreadJob(void) override = default;
    ThreadJob(const ThreadJob &rhs) = delete;
    ThreadJob(ThreadJob &&other) = default;
    ThreadJob &operator=(ThreadJob &&other) = default;
    ThreadJob &operator=(const ThreadJob &rhs) = delete;

    void execute() override
    {
        func_();
    }

  private:
    Func func_;
};

}

#endif
