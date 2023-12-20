#include <iostream>
#include <stdexcept>
#include <vector>
#include "process.hpp"
using namespace std;

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
