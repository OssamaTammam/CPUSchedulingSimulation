#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

class Process
{
public:
    typedef enum
    {
        READY,
        WAITING,
        RUNNING,
        DONE
    } ProcessStatus;

private:
    int processId;
    int processBurst;
    int remainingTime;
    ProcessStatus processStatus;
    vector<string> processHistory;

public:
    Process(int id, int burst) : processId(id), processBurst(burst), remainingTime(burst), processStatus(ProcessStatus::WAITING)
    {
        this->processHistory.push_back("Process created with burst time " + to_string(this->processBurst) + "\n");
    }

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

    void addStage(string newStage)
    {
        cout << newStage;
        this->processHistory.push_back(newStage);
    }

    string getHistoryString()
    {
        string history = "History of process " + to_string(this->processId) + ":\n";
        history += accumulate(this->processHistory.begin(), this->processHistory.end(), string());
        return history;
    }

    int getProcessId() const
    {
        return this->processId;
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

    vector<string> &getProcessHistory()
    {
        return this->processHistory;
    }
};
