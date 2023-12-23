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

/**
 * @class SchedulingQueue
 * @brief Represents a scheduling queue for processes.
 *
 * The SchedulingQueue class manages a queue of processes, allowing for process enqueueing, dequeueing, and execution.
 * It supports both First-Come-First-Serve (FCFS) and Round Robin scheduling algorithms.
 */
class SchedulingQueue
{
private:
    queue<Process *> readyQueue;   /**< A queue of Process pointers representing the processes that are ready to be executed. */
    queue<Process *> waitingQueue; /**< A queue of Process pointers representing the processes that are waiting to be executed. */
    size_t maxSize;                /**< The maximum size of the scheduling queue. */
    size_t currSize;               /**< The current size of the scheduling queue. */
    int quantum;                   /**< The time quantum for the Round Robin scheduling algorithm. */
    bool isFcfs;                   /**< A boolean flag indicating whether the scheduling algorithm is FCFS or not. */
    int serveTime;                 /**< The time required to serve a process. */
    int remainingQuantum;          /**< The remaining time quantum for the current process being executed. */

public:
    /**
     * @brief Constructs a SchedulingQueue object with the given parameters.
     *
     * @param size The maximum size of the scheduling queue.
     * @param quantum The time quantum for the Round Robin scheduling algorithm.
     * @param serveTime The time required to serve a process.
     */
    SchedulingQueue(size_t size, int quantum, int serveTime) : maxSize(size), currSize(0), quantum(quantum), isFcfs(false), serveTime(serveTime), remainingQuantum(quantum)
    {
        if (quantum == 0)
        {
            isFcfs = true;
        }
    }

    /**
     * @brief Executes the front process in the scheduling queue for the given execution time.
     *
     * @param execTime The execution time for the front process.
     * @return The saved time due to preemption or completion of the front process.
     */
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

    /**
     * @brief Moves processes from the waiting queue to the ready queue until the ready queue is full.
     */
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

    /**
     * @brief Enqueues a process into the waiting queue.
     *
     * @param currProcess The process to be enqueued.
     */
    void enqueue(Process *currProcess)
    {
        currProcess->setProcessStatus(Process::WAITING);
        waitingQueue.push(currProcess);
        this->readyProcesses();
    }

    /**
     * @brief Dequeues the front process from the ready queue.
     *
     * @return The dequeued process.
     */
    Process *dequeue()
    {
        Process *queueFront = readyQueue.front();
        readyQueue.pop();
        currSize--;
        this->remainingQuantum = this->quantum;

        this->readyProcesses();

        return queueFront;
    }

    /**
     * @brief Returns the front process in the ready queue.
     *
     * @return The front process.
     * @throws std::out_of_range if the ready queue is empty.
     */
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

    /**
     * @brief Checks if the waiting queue is empty.
     *
     * @return true if the waiting queue is empty, false otherwise.
     */
    bool waitingEmpty() const
    {
        return waitingQueue.empty();
    }

    /**
     * @brief Checks if the ready queue is empty.
     *
     * If the waiting queue is not empty, moves processes from the waiting queue to the ready queue.
     *
     * @return true if the ready queue is empty, false otherwise.
     */
    bool readyEmpty()
    {
        if (!this->waitingEmpty())
        {
            this->readyProcesses();
        }

        return readyQueue.empty();
    }

    /**
     * @brief Checks if the scheduling queue is empty.
     *
     * @return true if the scheduling queue is empty, false otherwise.
     */
    bool empty()
    {
        return (this->waitingEmpty() && this->readyEmpty());
    }

    /**
     * @brief Returns the maximum size of the scheduling queue.
     *
     * @return The maximum size of the scheduling queue.
     */
    size_t size() const
    {
        return maxSize;
    }

    /**
     * @brief Returns the remaining time quantum for the current process being executed.
     *
     * @return The remaining time quantum for the current process being executed.
     */
    int getQuantum() const
    {
        return quantum;
    }

    /**
     * @brief Returns the remaining time quantum for the current process being executed.
     *
     * @return The remaining time quantum for the current process being executed.
     */
    int getServeTime() const
    {
        return serveTime;
    }
    /**
     * @brief Returns the remaining time quantum for the current process being executed.
     *
     * @return The remaining time quantum for the current process being executed.
     */
    bool getFcfsStatus() const
    {
        return isFcfs;
    }

    /**
     * @brief Returns the remaining time quantum for the current process being executed.
     *
     * @return The remaining time quantum for the current process being executed.
     */
    int getRemainingQuantum() const
    {
        return this->remainingQuantum;
    }
};

/**
 * @class ProcessFactory
 * @brief Represents a process factory.
 *
 * The ProcessFactory class is responsible for creating new processes with random burst times.
 */
class ProcessFactory
{
private:
    int lastProcessId; /**< The ID of the last process created. */

public:
    /**
     * @brief Constructs a ProcessFactory object.
     */
    ProcessFactory()
    {
        lastProcessId = -1;
    }

    /**
     * @brief Creates a new process with a random burst time.
     *
     * @return A pointer to the newly created process.
     */
    Process *createProcess()
    {
        int burst = 1 + (rand() % 100); // Random burst time between 1 and 100
        Process *newProcess = new Process(++lastProcessId + 1, burst);
        return newProcess;
    }
};

/**
 * @class Scheduler
 * @brief Represents a CPU scheduler.
 *
 * The Scheduler class is responsible for managing the scheduling queues and executing the processes.
 */
class Scheduler
{
private:
    vector<SchedulingQueue> schedulingQueues; /**< A vector of scheduling queues. */
    vector<Process *> processVector;          /**< A vector of pointers to the processes. */

    /**
     * @brief Upgrades a process to a higher priority queue.
     *
     * @param currProcess A pointer to the process to be upgraded.
     * @param currQueueIndex The index of the current queue of the process.
     */
    void upgradeProcess(Process *currProcess, int currQueueIndex)
    {

        if (currQueueIndex == 0)
        {
            this->schedulingQueues[currQueueIndex + 1].enqueue(currProcess);
        }
        else if (currQueueIndex == int((this->schedulingQueues).size()) - 1)
        {
            this->schedulingQueues[currQueueIndex - 1].enqueue(currProcess);
        }
        else
        {
            rand() % 2 ? this->schedulingQueues[currQueueIndex - 1].enqueue(currProcess) : this->schedulingQueues[currQueueIndex + 1].enqueue(currProcess);
        }
    }

public:
    /**
     * @brief Constructs a Scheduler object.
     */
    Scheduler(){};

    /**
     * @brief Destructs a Scheduler object.
     */
    ~Scheduler()
    {
        for (auto process : processVector)
        {
            delete process;
        }
        processVector.clear();
    }

    /**
     * @brief Adds a new scheduling queue to the scheduler.
     *
     * @param size The maximum size of the scheduling queue.
     * @param quantum The time quantum for the Round Robin scheduling algorithm.
     * @param serveTime The time required to serve a process.
     */
    void addQueue(size_t size, int quantum, int serveTime)
    {
        SchedulingQueue newQueue(size, quantum, serveTime);
        schedulingQueues.push_back(newQueue);
    }

    /**
     * @brief Adds a new process to the scheduler.
     *
     * @param currProcess A pointer to the process to be added.
     */
    void addProcess(Process *currProcess)
    {
        currProcess->addStage("Process " + to_string(currProcess->getProcessId()) + " added to the system with burst time " + to_string(currProcess->getProcessBurst()) + "\n");
        processVector.push_back(currProcess);
        schedulingQueues[0].enqueue(currProcess);
    }

    /**
     * @brief Starts the execution of the processes.
     */
    void startExecution()
    {
        while (!this->isSchedulingDone())
        {
            // Iterate over every queue
            for (int queueIndex = 0; queueIndex < int((this->schedulingQueues).size()); queueIndex++)
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

    /**
     * @brief Returns the scheduling queues.
     *
     * @return The scheduling queues.
     */
    vector<Process *> getProcessVector()
    {
        return this->processVector;
    }

    /**
     * @brief Checks if the scheduling is done.
     *
     * @return true if the scheduling is done, false otherwise.
     */
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