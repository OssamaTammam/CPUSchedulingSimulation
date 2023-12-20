#ifndef PROCESS_FACTORY_HPP
#define PROCESS_FACTORY_HPP

#include <iostream>
#include <stdexcept>
#include <vector>
#include <process.hpp> // Assuming Process class is defined in process.hpp

/**
 * @class ProcessFactory
 * @brief A singleton class responsible for creating Process objects.
 *
 * The ProcessFactory class provides a centralized mechanism for creating Process objects.
 * It ensures that only one instance of the factory is created and provides a method to access that instance.
 * The factory keeps track of the last assigned process ID and maintains a vector of created processes.
 * The copy constructor and copy assignment operator are disabled to prevent copying of the factory.
 */
class ProcessFactory
{
private:
    static ProcessFactory *processFactoryInstance;
    int lastProcessId;
    std::vector<Process> processVector;

    ProcessFactory();

    // Destructor is made private to control the deletion of the singleton instance
    ~ProcessFactory();

public:
    // Declare copy constructor and copy assignment operator as private to prevent copying
    ProcessFactory(const ProcessFactory &) = delete;
    ProcessFactory &operator=(const ProcessFactory &) = delete;

    static ProcessFactory *getInstance();

    Process createProcess();
};

#endif // PROCESS_FACTORY_HPP
