#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <queue>
#include <vector>
#include <numeric>
#include <stdexcept>
#include <climits>
#include <random>

#define PROCESSES_NUMBER 100

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
    int processId;                 // Process PID
    int processBurst;              // Process burst time in queue
    int remainingTime;             // Process remaining time of execution
    ProcessStatus processStatus;   // Defaults to waiting
    vector<string> processHistory; // A vector of strings tracking the stages of a process's lifespan

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

class SchedulingQueue
{
private:
    queue<Process *> readyQueue;   // Renamed to avoid conflict with std::queue
    queue<Process *> waitingQueue; // Waiting queue for process if the main scheduling queue
    size_t maxSize;
    int currSize;
    int quantum;
    bool isFcfs;
    int serveTime;        // The time that the queue has been served for by the CPU in ms
    int remainingQuantum; // Remaining quantum for the front of the queue

public:
    SchedulingQueue(size_t size, int quantum, int serveTime) : maxSize(size), quantum(quantum), currSize(0), serveTime(serveTime), remainingQuantum(quantum), isFcfs(false)
    {
        if (quantum == 0)
        {
            isFcfs = true;
        }
    }

    int executeFront(int execTime)
    {
        int savedTime = 0;
        Process *queueFront = readyQueue.front();

        if (queueFront == nullptr)
        {
            return execTime;
        }

        if (this->remainingQuantum < execTime && !this->getFcfsStatus())
        {
            int potentialTimeSave = execTime - this->remainingQuantum;
            execTime = this->remainingQuantum;
            savedTime += potentialTimeSave;
        }

        savedTime += queueFront->executeProcess(execTime);

        this->remainingQuantum -= execTime;

        if (queueFront->getProcessStatus() == Process::DONE)
        {
            this->dequeue();
            this->readyProcesses();
        }

        return savedTime;
    }

    void readyProcesses()
    {
        while (currSize < maxSize)
        {
            if (!waitingQueue.empty())
            {
                readyQueue.push(waitingQueue.front());
                (waitingQueue.front())->setProcessStatus(Process::READY);
                currSize++;
                waitingQueue.pop();
            }
            else
            {
                break;
            }
        }
    }

    void enqueue(Process *currProcess)
    {
        currProcess->setProcessStatus(Process::WAITING);
        waitingQueue.push(currProcess);
        this->readyProcesses();
    }

    Process *dequeue()
    {
        Process *queueFront = readyQueue.front();
        readyQueue.pop();
        currSize--;
        this->remainingQuantum = this->quantum;

        this->readyProcesses();

        return queueFront;
    }

    Process *front()
    {
        if (!readyQueue.empty())
        {
            return readyQueue.front();
        }
        else
        {
            throw out_of_range("Queue is empty. Cannot access front element.");
        }
    }

    bool waitingEmpty() const
    {
        return waitingQueue.empty();
    }

    bool readyEmpty()
    {
        if (!this->waitingEmpty())
        {
            this->readyProcesses();
        }

        return readyQueue.empty();
    }

    bool empty()
    {
        return (this->waitingEmpty() && this->readyEmpty());
    }

    size_t size() const
    {
        return maxSize;
    }

    int getQuantum() const
    {
        return quantum;
    }

    int getServeTime() const
    {
        return serveTime;
    }

    bool getFcfsStatus() const
    {
        return isFcfs;
    }

    int getRemainingQuantum() const
    {
        return this->remainingQuantum;
    }
};

class ProcessFactory
{
private:
    int lastProcessId;

public:
    ProcessFactory()
    {
        lastProcessId = -1;
    }

    Process *createProcess()
    {
        int burst = 1 + (rand() % 100); // Random burst time between 1 and 100
        Process *newProcess = new Process(++lastProcessId + 1, burst);
        return newProcess;
    }
};

class Scheduler
{
private:
    vector<SchedulingQueue> schedulingQueues;
    vector<Process *> processVector; // Vector of pairs to keep track of the process its history in the CPU

    void upgradeProcess(Process *currProcess, int currQueueIndex)
    {

        if (currQueueIndex == 0)
        {
            this->schedulingQueues[currQueueIndex + 1].enqueue(currProcess);
        }
        else if (currQueueIndex == (this->schedulingQueues).size() - 1)
        {
            this->schedulingQueues[currQueueIndex - 1].enqueue(currProcess);
        }
        else
        {
            rand() % 2 ? this->schedulingQueues[currQueueIndex - 1].enqueue(currProcess) : this->schedulingQueues[currQueueIndex + 1].enqueue(currProcess);
        }
    }

public:
    Scheduler(){};

    ~Scheduler()
    {
        for (auto process : processVector)
        {
            delete process;
        }
        processVector.clear();
    }

    void addQueue(size_t size, int quantum, int serveTime)
    {
        SchedulingQueue newQueue(size, quantum, serveTime);
        schedulingQueues.push_back(newQueue);
    }

    void addProcess(Process *currProcess)
    {
        currProcess->addStage("Process " + to_string(currProcess->getProcessId()) + " added to the system with burst time " + to_string(currProcess->getProcessBurst()) + "\n");
        processVector.push_back(currProcess);
        schedulingQueues[0].enqueue(currProcess);
    }

    void startExecution()
    {
        while (!this->isSchedulingDone())
        {
            // Iterate over every queue
            for (int queueIndex = 0; queueIndex < (this->schedulingQueues).size(); queueIndex++)
            {
                SchedulingQueue &currQueue = schedulingQueues[queueIndex];

                // If the queue is empty, continue to the next queue
                if (currQueue.empty())
                {
                    continue;
                }

                // Serve for the intended serve time of each queue
                int remainingServeTime = currQueue.getServeTime();
                while (remainingServeTime > 0)
                {
                    if (currQueue.empty())
                    {
                        break;
                    }

                    int savedTime = 0;
                    if (currQueue.getFcfsStatus())
                    {
                        savedTime += currQueue.executeFront(remainingServeTime);
                    }
                    else
                    {
                        Process *currProcess = currQueue.front();
                        savedTime += currQueue.executeFront(remainingServeTime);

                        if (currProcess->getProcessStatus() == Process::READY && currQueue.getRemainingQuantum() == 0)
                        {
                            currQueue.dequeue();
                            this->upgradeProcess(currProcess, queueIndex);
                        }
                    }
                    remainingServeTime = savedTime;
                }
            }
        }
    }

    vector<Process *> getProcessVector()
    {
        return this->processVector;
    }

    bool isSchedulingDone()
    {
        for (auto queue : schedulingQueues)
        {
            if (!queue.empty())
            {
                return false;
            }
        }

        return true;
    }
};

int main()
{
    srand(time(NULL)); // For random seed

    // Initializing the process factory and scheduling queues
    ProcessFactory *processFactory = new ProcessFactory();
    Scheduler *scheduler = new Scheduler();

    // Initializing scheduling queues
    scheduler->addQueue(30, 8, 50);
    scheduler->addQueue(20, 16, 30);
    scheduler->addQueue(10, 0, 20);

    // Initializing processes
    for (int i = 0; i < PROCESSES_NUMBER; i++)
    {
        scheduler->addProcess(processFactory->createProcess());
    }

    // Start execution
    scheduler->startExecution();

    // Free memory
    delete processFactory;
    delete scheduler;

    return 0;
}