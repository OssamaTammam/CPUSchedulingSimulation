#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

/**
 * @class Process
 * @brief Represents a process in a CPU scheduling simulation.
 */
class Process
{
public:
    /**
     * @enum ProcessStatus
     * @brief Represents the status of a process.
     */
    typedef enum
    {
        READY,   /**< The process is ready to be executed. */
        WAITING, /**< The process is waiting for its turn to be executed. */
        RUNNING, /**< The process is currently being executed. */
        DONE     /**< The process has finished executing. */
    } ProcessStatus;

private:
    int processId;                 /**< The process ID. */
    int processBurst;              /**< The burst time of the process in the queue. */
    int remainingTime;             /**< The remaining time of execution for the process. */
    ProcessStatus processStatus;   /**< The current status of the process. Defaults to WAITING. */
    vector<string> processHistory; /**< A vector of strings tracking the stages of a process's lifespan. */

public:
    /**
     * @brief Constructor for the Process class.
     * @param id The process ID.
     * @param burst The burst time of the process.
     */
    Process(int id, int burst);

    /**
     * @brief Executes the process for a given amount of time.
     * @param execTime The time to execute the process.
     * @return The remaining execution time after executing the process.
     */
    int executeProcess(int execTime);

    /**
     * @brief Adds a new stage to the process history.
     * @param newStage The new stage to add.
     */
    void addStage(string newStage);

    /**
     * @brief Returns the history of the process as a string.
     * @return The history of the process.
     */
    string getHistoryString();

    /**
     * @brief Returns the process ID.
     * @return The process ID.
     */
    int getProcessId() const;

    /**
     * @brief Returns the burst time of the process.
     * @return The burst time of the process.
     */
    int getProcessBurst() const;

    /**
     * @brief Returns the current status of the process.
     * @return The current status of the process.
     */
    ProcessStatus getProcessStatus() const;

    /**
     * @brief Sets the status of the process.
     * @param newStatus The new status of the process.
     */
    void setProcessStatus(ProcessStatus newStatus);

    /**
     * @brief Returns the process history.
     * @return The process history.
     */
    vector<string> &getProcessHistory();
};

#endif // PROCESS_H
