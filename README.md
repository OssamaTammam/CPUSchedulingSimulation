# Multi-level Feedback Queue Scheduler Simulation
A multi-level feedback queue simulation that uses FCFS and Round Robin scheudling algorithms written as a bonus project for CSE366 Operating Systems class at Alexandria University.

## Prerequisites
- GNU compiler
- CMake

## How To Run
1. Navigate to the project directory where ```run.sh``` resides
2. Use a bash terminal and run the following command
   ```bash
   bash run.sh
   ```

## File Hierarchy
```
├── CMakeLists.txt
├── README.md
├── include ## Include directory for header files
│   └── model
│       ├── Process.hpp
│       ├── ProcessFactory.hpp
│       ├── Scheduler.hpp
│       └── SchedulingQueue.hpp
├── run.sh
└── src ## Main application files
    ├── main.cpp
    └── model
        ├── Process.cpp
        ├── ProcessFactory.cpp
        ├── Scheduler.cpp
        └── SchedulingQueue.cpp
```
