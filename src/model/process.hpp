#ifndef PROCESS_H
#define PROCESS_H

/**
 * @class Process
 * @brief Represents a process in a CPU scheduling simulation.
 *
 * The Process class encapsulates the properties and behavior of a process,
 * including its process ID, burst time, remaining execution time, and status.
 * It provides methods to execute the process, set and get the process ID and burst time,
 * and retrieve the current status of the process.
 */
class Process
{
private:
    typedef enum
    {
        READY,   // Ready process to get executed
        WAITING, // Process in waiting queue
        RUNNING, // Process running in CPU
        DONE     // Terminated process (Done running)
    } ProcessStatus;

    int processId;                                        // Process PID
    int processBurst;                                     // Process burst time in queue
    int remainingTime;                                    // Process remaining time of execution
    ProcessStatus processStatus = ProcessStatus::WAITING; // Defaults to waiting

public:
    /**
     * @brief Constructs a Process object with the specified process ID and burst time.
     *
     * @param id The process ID.
     * @param burst The burst time of the process.
     */
    Process(int id, int burst);

    /**
     * @brief Executes the process for the specified execution time.
     *
     * @param executionTime The time to execute the process.
     */
    void executeProcess(int executionTime);

    /**
     * @brief Sets the process ID.
     *
     * @param id The process ID to set.
     */
    void setProcessId(int id);

    /**
     * @brief Gets the process ID.
     *
     * @return The process ID.
     */
    int getProcessId() const;

    /**
     * @brief Sets the burst time of the process.
     *
     * @param burst The burst time to set.
     */
    void setProcessBurst(int burst);

    /**
     * @brief Gets the burst time of the process.
     *
     * @return The burst time.
     */
    int getProcessBurst() const;

    /**
     * @brief Gets the current status of the process.
     *
     * @return The process status.
     */
    ProcessStatus getProcessStatus() const;
};

#endif
