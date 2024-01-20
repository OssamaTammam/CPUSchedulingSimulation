#include <iostream>
#include <ProcessFactory.hpp>
#include <Scheduler.hpp>

#define PROCESSES_NUMBER 100

using namespace std;

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