#include <iostream>
#include <queue>
#include <vector>
#include <stdexcept>

using namespace std;

template <typename T>
class BoundedQueue
{
private:
    queue<T> myQueue; // Renamed to avoid conflict with std::queue
    size_t maxSize;
    int currSize;

public:
    BoundedQueue(size_t size) : maxSize(size), currSize(0) {}

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
    Process p1 = processFactory.createProcess();

    cout << p1.getProcessId() << endl
         << p1.getProcessBurst() << endl
         << p1.getProcessStatus() << endl;
    return 0;
};