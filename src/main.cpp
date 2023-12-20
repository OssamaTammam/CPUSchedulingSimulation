#include <iostream>
#include "model/processFactory.hpp"
#include "model/process.hpp"

using namespace std;

int main()
{
    ProcessFactory processFactory;
    Process p1 = processFactory.createProcess();

    cout << p1.getProcessId() << endl
         << p1.getProcessBurst() << endl
         << p1.getProcessStatus() << endl;
    return 0;
};