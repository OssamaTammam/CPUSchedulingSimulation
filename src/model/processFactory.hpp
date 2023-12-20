#ifndef PROCESS_FACTORY_HPP
#define PROCESS_FACTORY_HPP

#include <iostream>
#include <stdexcept>
#include <vector>
#include "process.hpp" // Assuming you have a header file for the Process class
using namespace std;
class ProcessFactory
{
private:
    int lastProcessId;
    vector<Process> processVector;

public:
    ProcessFactory();

    Process createProcess();
};

#endif // PROCESS_FACTORY_HPP
