#include <iostream>
#include <cstdlib>
#include <queue>
#include <vector>
#include <random>
#include "Process.hpp"

#define PROCESSES_NUMBER 100

using namespace std;

/**
 * @class ProcessFactory
 * @brief Represents a process factory.
 *
 * The ProcessFactory class is responsible for creating new processes with random burst times.
 */
class ProcessFactory
{
private:
    int lastProcessId; /**< The ID of the last process created. */

public:
    /**
     * @brief Constructs a ProcessFactory object.
     */
    ProcessFactory()
    {
        lastProcessId = -1;
    }

    /**
     * @brief Creates a new process with a random burst time.
     *
     * @return A pointer to the newly created process.
     */
    Process *createProcess()
    {
        int burst = 1 + (rand() % 100); // Random burst time between 1 and 100
        Process *newProcess = new Process(++lastProcessId + 1, burst);
        return newProcess;
    }
};

/**
 * @class Scheduler
 * @brief Represents a CPU scheduler.
 *
 * The Scheduler class is responsible for managing the scheduling queues and executing the processes.
 */
