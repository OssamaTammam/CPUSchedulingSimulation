#include <iostream>
#include <queue>
#include <vector>
#include <random>
#include "Process.hpp"

using namespace std;

class SchedulingQueue
{
private:
    queue<Process *> readyQueue;
    queue<Process *> waitingQueue;
    size_t maxSize;
    size_t currSize;
    int quantum;
    bool isFcfs;
    int serveTime;
    int remainingQuantum;

public:
    SchedulingQueue(size_t size, int quantum, int serveTime) : maxSize(size), currSize(0), quantum(quantum), isFcfs(false), serveTime(serveTime), remainingQuantum(quantum)
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
