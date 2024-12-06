#ifndef FIFO_H_
#define FIFO_H_

#include "vector"
#include "Process.h"


class FIFO
{
private:
    // holds the the processes that have been loaded in from the file
    std::vector<Process> processes;

    //holds the total runtime of the file
    int total_runtime;
public:

    // calculates the start and completion times of all of the processes using FIFO scheduling
    void scheduleProcessesFIFO();

    // calculates the throughput and display it to the screen
    void calculateThrouphput();

    //calculates the cpu utilization for the processes
    void calculateCPUutilization();

    //calculates and prints the average waiting time
    void calculateAverageWaintingTime();

    //calculates and prints the average turnaround time
    void calculateAverageTurnAroundTime();

    // prints the list of start and completion times of the processes in the process list
    void printScheduledProcesses();

    // print the results of 
    void printResults();

    // default constructor
    FIFO(std::vector<Process> newprocesses);

    // destructor
    ~FIFO();
};
#endif