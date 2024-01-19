#include <Process.hpp>

Process::Process(int id, int burst) : processId(id), processBurst(burst), remainingTime(burst), processStatus(ProcessStatus::WAITING)
{
    this->processHistory.push_back("Process created with burst time " + to_string(this->processBurst) + "\n");
}

int Process::executeProcess(int execTime)
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

void Process::addStage(string newStage)
{
    cout << newStage;
    this->processHistory.push_back(newStage);
}

string Process::getHistoryString()
{
    string history = "History of process " + to_string(this->processId) + ":\n";
    history += accumulate(this->processHistory.begin(), this->processHistory.end(), string());
    return history;
}

int Process::getProcessId() const
{
    return this->processId;
}

int Process::getProcessBurst() const
{
    return this->processBurst;
}

Process::ProcessStatus Process::getProcessStatus() const
{
    return this->processStatus;
}

void Process::setProcessStatus(ProcessStatus newStatus)
{
    this->processStatus = newStatus;
}

vector<string> &Process::getProcessHistory()
{
    return this->processHistory;
}
