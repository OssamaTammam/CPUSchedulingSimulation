#include <iostream>
#include <cstdlib>
#include <vector>
#include <random>
#include "SchedulingQueue.hpp"
#include "Process.hpp"

using namespace std;

class Scheduler
{
private:
    vector<SchedulingQueue> schedulingQueues;
    vector<Process *> processVector;

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
