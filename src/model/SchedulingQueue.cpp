#include <Process.hpp>
#include <SchedulingQueue.hpp>

SchedulingQueue::SchedulingQueue(size_t size, int quantum, int serveTime) : maxSize(size), currSize(0), quantum(quantum), isFcfs(false), serveTime(serveTime), remainingQuantum(quantum)
{
    if (quantum == 0)
    {
        isFcfs = true;
    }
}

int SchedulingQueue::executeFront(int execTime)
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

void SchedulingQueue::readyProcesses()
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

void SchedulingQueue::enqueue(Process *currProcess)
{
    currProcess->setProcessStatus(Process::WAITING);
    waitingQueue.push(currProcess);
    this->readyProcesses();
}

Process *SchedulingQueue::dequeue()
{
    Process *queueFront = readyQueue.front();
    readyQueue.pop();
    currSize--;
    this->remainingQuantum = this->quantum;

    this->readyProcesses();

    return queueFront;
}

Process *SchedulingQueue::front()
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

bool SchedulingQueue::waitingEmpty() const
{
    return waitingQueue.empty();
}

bool SchedulingQueue::readyEmpty()
{
    if (!this->waitingEmpty())
    {
        this->readyProcesses();
    }

    return readyQueue.empty();
}

bool SchedulingQueue::empty()
{
    return (this->waitingEmpty() && this->readyEmpty());
}

size_t SchedulingQueue::size() const
{
    return maxSize;
}

int SchedulingQueue::getQuantum() const
{
    return quantum;
}

int SchedulingQueue::getServeTime() const
{
    return serveTime;
}

bool SchedulingQueue::getFcfsStatus() const
{
    return isFcfs;
}

int SchedulingQueue::getRemainingQuantum() const
{
    return this->remainingQuantum;
}
