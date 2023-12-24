#include <iostream>
#include <cstdlib>
#include <queue>
#include <vector>
#include <random>
#include "Process.hpp"

#define PROCESSES_NUMBER 100

using namespace std;

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
