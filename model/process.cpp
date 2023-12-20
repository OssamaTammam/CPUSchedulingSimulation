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

    int processId;                                        // Process PID
    int processBurst;                                     // Process burst time in queue
    int remainingTime = this->remainingTime;              // Process remaining time of execution
    ProcessStatus processStatus = ProcessStatus::WAITING; // Defaults to waiting

public:
    Process(int id, int burst)
    {
        this->processId = id;
        this->processBurst = burst;
    }

    void executeProcess(int executionTime)
    {
        this->remainingTime = (this->remainingTime - executionTime) > 0 ? (this->remainingTime - executionTime) : 0;
    }

    void setProcessId(int id)
    {
        this->processId = id;
    }

    int getProcessId()
    {
        return this->processId;
    }

    void setProcessBurst(int burst)
    {
        this->processBurst = burst;
    }

    int getProcessBurst()
    {
        return this->processBurst;
    }

    ProcessStatus getProcessStatus()
    {
        return this->processStatus;
    }
};