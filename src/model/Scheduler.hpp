#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

#include <iostream>
#include <vector>
#include <random>
#include "SchedulingQueue.hpp"
#include "Process.hpp"

#define PROCESSES_NUMBER 100

/**
 * @class Scheduler
 * @brief Represents a CPU scheduler.
 *
 * The Scheduler class is responsible for managing scheduling queues and executing processes.
 */
class Scheduler
{
private:
    std::vector<SchedulingQueue> schedulingQueues; /**< A vector of scheduling queues. */
    std::vector<Process *> processVector;          /**< A vector of pointers to the processes. */

    /**
     * @brief Upgrades a process to a higher priority queue.
     *
     * @param currProcess A pointer to the process to be upgraded.
     * @param currQueueIndex The index of the current queue of the process.
     */
    void upgradeProcess(Process *currProcess, int currQueueIndex);

public:
    /**
     * @brief Constructs a Scheduler object.
     */
    Scheduler();

    /**
     * @brief Destructs a Scheduler object.
     */
    ~Scheduler();

    /**
     * @brief Adds a new scheduling queue to the scheduler.
     *
     * @param size The maximum size of the scheduling queue.
     * @param quantum The time quantum for the Round Robin scheduling algorithm.
     * @param serveTime The time required to serve a process.
     */
    void addQueue(size_t size, int quantum, int serveTime);

    /**
     * @brief Adds a new process to the scheduler.
     *
     * @param currProcess A pointer to the process to be added.
     */
    void addProcess(Process *currProcess);

    /**
     * @brief Starts the execution of the processes.
     */
    void startExecution();

    /**
     * @brief Returns the scheduling queues.
     *
     * @return The scheduling queues.
     */
    std::vector<Process *> getProcessVector();

    /**
     * @brief Checks if the scheduling is done.
     *
     * @return true if the scheduling is done, false otherwise.
     */
    bool isSchedulingDone();
};

#endif // SCHEDULER_HPP
