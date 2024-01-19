#include <Process.hpp>
#include <ProcessFactory.hpp>

#define PROCESSES_NUMBER 100

using namespace std;

ProcessFactory::ProcessFactory()
{
    lastProcessId = -1;
}

Process *ProcessFactory::createProcess()
{
    int burst = 1 + (rand() % 100); // Random burst time between 1 and 100
    Process *newProcess = new Process(++lastProcessId + 1, burst);
    return newProcess;
}
