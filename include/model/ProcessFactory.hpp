#ifndef PROCESS_FACTORY_HPP
#define PROCESS_FACTORY_HPP

#include <iostream>
#include <cstdlib>
#include <queue>
#include <vector>
#include <random>
#include <Process.hpp>

#define PROCESSES_NUMBER 100

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
    ProcessFactory();

    /**
     * @brief Creates a new process with a random burst time.
     *
     * @return A pointer to the newly created process.
     */
    Process *createProcess();
};

#endif // PROCESS_FACTORY_HPP