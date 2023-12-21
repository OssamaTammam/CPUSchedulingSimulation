#include <iostream>
#include <queue>
#include <vector>
#include <stdexcept>

using namespace std;

template <typename T>
class SchedulingQueue
{
private:
    queue<T> myQueue; // Renamed to avoid conflict with std::queue
    size_t maxSize;
    int currSize;
    int quantum;

public:
    SchedulingQueue(size_t size, int quantum) : maxSize(size), quantum(quantum), currSize(0) {}

    void enqueue(const T &value)
    {
        if (currSize < maxSize)
        {
            myQueue.push(value);
            currSize++;
        }
        else
        {
            throw out_of_range("Queue is full. Cannot enqueue.");
        }
    }

    void dequeue()
    {
        if (!myQueue.empty())
        {
            myQueue.pop();
            currSize--;
        }
        else
        {
            throw out_of_range("Queue is empty. Cannot dequeue.");
        }
    }

    T front() const
    {
        if (!myQueue.empty())
        {
            return myQueue.front();
        }
        else
        {
            throw out_of_range("Queue is empty. Cannot access front element.");
        }
    }

    bool empty() const
    {
        return myQueue.empty();
    }

    size_t size() const
    {
        return myQueue.size();
    }
};

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

class ProcessFactory
{
private:
    int lastProcessId;
    vector<Process> processVector;

public:
    ProcessFactory()
    {
        lastProcessId = -1;
    }

    Process createProcess()
    {
        int burst = 1 + (rand() % 100); // Random burst time between 1 and 100
        Process newProcess(lastProcessId + 1, burst);
        lastProcessId++;
        processVector.push_back(newProcess);
        return newProcess;
    }
};

int main()
{
    ProcessFactory processFactory;
    SchedulingQueue<Process> queue1(10, 8), queue2(20, 16), queue3(30, 0); // 0 means fcfs queue
    queue<Process> waitingQueue1, waitingQueue2, waitingQueue3;
    vector<string> history;

    for (int i = 0; i < 100; i++)
    {
        waitingQueue1.push(processFactory.createProcess());
    }

    // We will use iterations as serve time 1 iteration of a loop is 1 ms

    return 0;
};