#include <iostream>
using namespace std;

class Process
{
private:
    // Different status for the processes
    typedef enum
    {
        READY,   // Ready process to get executed
        WAITING, // Process in waiting queue
        RUNNING, // Process running in CPU
        DONE     // Terminated process (Done running)
    } ProcessStatus;

    int processId;               // Process PID
    int processBurst;            // Process burst time in queue
    int remainingTime;           // Process remaining time of execution
    ProcessStatus processStatus; // Defaults to waiting

public:
    Process(int id, int burst) : processId(id), processBurst(burst), remainingTime(burst), processStatus(ProcessStatus::WAITING)
    {
    }

    void executeProcess(int executionTime)
    {
        this->remainingTime = (this->remainingTime - executionTime) > 0 ? (this->remainingTime - executionTime) : 0;
    }

    void setProcessId(int id)
    {
        this->processId = id;
    }

    int getProcessId() const
    {
        return this->processId;
    }

    void
    setProcessBurst(int burst)
    {
        this->processBurst = burst;
    }

    int getProcessBurst() const
    {
        return this->processBurst;
    }

    ProcessStatus getProcessStatus() const
    {
        return this->processStatus;
    }

    void setProcessStatus(ProcessStatus newStatus)
    {
        this->processStatus = newStatus;
    }
};