#include <iostream>
#include <queue>
#include <vector>
#include <random>
#include "Process.hpp"

using namespace std;

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
