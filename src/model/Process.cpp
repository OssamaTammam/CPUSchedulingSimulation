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
    Process(int id, int burst) : processId(id), processBurst(burst), remainingTime(burst), processStatus(ProcessStatus::WAITING)
    {
        this->processHistory.push_back("Process created with burst time " + to_string(this->processBurst) + "\n");
    }

    /**
     * @brief Executes the process for a given amount of time.
     * @param execTime The time to execute the process.
     * @return The remaining execution time after executing the process.
     */
    int executeProcess(int execTime)
    {
        this->processStatus = ProcessStatus::RUNNING;

        int realExecTime = (execTime > this->remainingTime) ? this->remainingTime : execTime;
        this->remainingTime -= realExecTime;

        this->addStage("Process " + to_string(this->processId) + " executed for " + to_string(realExecTime) + " ms\n");

        this->processStatus = (this->remainingTime <= 0) ? ProcessStatus::DONE : ProcessStatus::READY;

        if (this->processStatus == ProcessStatus::DONE)
        {
            this->addStage("Process " + to_string(this->processId) + " finished executing\n");
        }

        return (execTime - realExecTime);
    }

    /**
     * @brief Adds a new stage to the process history.
     * @param newStage The new stage to add.
     */
    void addStage(string newStage)
    {
        cout << newStage;
        this->processHistory.push_back(newStage);
    }

    /**
     * @brief Returns the history of the process as a string.
     * @return The history of the process.
     */
    string getHistoryString()
    {
        string history = "History of process " + to_string(this->processId) + ":\n";
        history += accumulate(this->processHistory.begin(), this->processHistory.end(), string());
        return history;
    }

    /**
     * @brief Returns the process ID.
     * @return The process ID.
     */
    int getProcessId() const
    {
        return this->processId;
    }

    /**
     * @brief Returns the burst time of the process.
     * @return The burst time of the process.
     */
    int getProcessBurst() const
    {
        return this->processBurst;
    }

    /**
     * @brief Returns the current status of the process.
     * @return The current status of the process.
     */
    ProcessStatus getProcessStatus() const
    {
        return this->processStatus;
    }

    /**
     * @brief Sets the status of the process.
     * @param newStatus The new status of the process.
     */
    void setProcessStatus(ProcessStatus newStatus)
    {
        this->processStatus = newStatus;
    }

    /**
     * @brief Returns the process history.
     * @return The process history.
     */
    vector<string> &getProcessHistory()
    {
        return this->processHistory;
    }
};
