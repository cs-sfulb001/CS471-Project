#include "FIFO.h"
#include "iostream"
#include "Tools/StringManip.h"
#include "Tools/UIHelper.h"
#include "Tools/Choices.h"

// calculates the start and completion times of all of the processes using FIFO scheduling
void FIFO::scheduleProcessesFIFO()
{

    total_runtime = 0;

    // calculates the start and completion times of all of the processes using FIFO scheduling
    for (int i = 0; i < processes.size(); i++)
    {

        /*if the arrival time is greater than the current runtime of the cpu scheduling,
        set the start time of the process to it's arrival time and calculate the total runtime*/

        if (processes[i].getArrivalTime() > total_runtime)
        {
            // set when the process starts running
            processes[i].setStartTime(processes[i].getArrivalTime());
            // set the completion time
            processes[i].setCompletionTime(processes[i].getArrivalTime() + processes[i].getBurstTime());
            // make the total time the completion time of the proccess
            total_runtime = processes[i].getCompletionTime();
        }
        // if the arrival time is not greater than the total runtime
        else
        {
            // set the start time of the process
            processes[i].setStartTime(total_runtime);
            processes[i].setCompletionTime(total_runtime + processes[i].getBurstTime());
            total_runtime = processes[i].getCompletionTime();
        }
    }
}

// calculate the throughput of the processes
void FIFO::calculateThrouphput()
{

    // holds the total burst time of the
    double sumBurstTimes = 0;

    // find the sum of the burst times
    for (int i = 0; i < processes.size(); i++)
    {
        sumBurstTimes = sumBurstTimes + processes[i].getBurstTime();
    }

    // calculates the throughput
    double throughput = sumBurstTimes / processes.size();

    // print the calculated throughput of the processes
    std::cout << std::fixed << std::setprecision(2);
    std::cout << std::left << std::setw(30) << "Throughput:" << throughput << std::endl;
}

void FIFO::calculateCPUutilization()
{

    // holds the total burst time of the
    double sum = 0;

    // find the sum of the burst times
    for (int i = 0; i < processes.size(); i++)
    {
        sum = sum + processes[i].getBurstTime();
    }

    // calculate the cpu utiliztion
    double cpu_utilization = 100 * (sum / total_runtime);

    // print the results of the calculation
    std::cout << std::fixed << std::setprecision(2);
    std::cout << std::left << std::setw(30) << "CPU Utilization:" << cpu_utilization << "%\n";
}

void FIFO::calculateAverageWaintingTime()
{

    // holds the total waiting total of all processed
    double total_waiting_time = 0;

    for (int i = 0; i < processes.size(); ++i)
    {
        // calculate the waiting time
        total_waiting_time += processes[i].getStartTime() - processes[i].getArrivalTime();
    }

    // calculate the average waiting time
    double average_waiting_time = total_waiting_time / processes.size();

    // print the calculated average waiting time
    std::cout << std::fixed << std::setprecision(2);
    std::cout << std::left << std::setw(30) << "Average Waiting Time:" << average_waiting_time << std::endl;
}

void FIFO::calculateAverageTurnAroundTime()
{

    // holds the total waiting total of all processed
    double total_turnaround_time = 0;

    // calculate the total turnaround time
    for (int i = 0; i < processes.size(); ++i)
    {
        // calculate the indiviadual turnaround time
        total_turnaround_time += processes[i].getCompletionTime() - processes[i].getArrivalTime();
    }

    // calculate the average waiting time
    double average_turnaround_time = total_turnaround_time / processes.size();

    // print the calculated average waiting time
    std::cout << std::fixed << std::setprecision(2);
    std::cout << std::left << std::setw(30) << "Average Turnaround Time" << average_turnaround_time << std::endl;
}

void FIFO::printScheduledProcesses()
{

    // use FIFO scheduling to calculate the
    scheduleProcessesFIFO();

    // print results to the screen
    headerNoCls("Results", 70, '=');
    std::cout << std::setw(10) << "Process number" << "|" << std::setw(10) << "Arrival time" << std::setw(5) << "|" << std::setw(10) << "CPU Burst" << std::setw(5) << "|" << std::setw(10) << "Start Time" << std::setw(5) << "|" << std::setw(10) << "Completion" << std::endl;
    dividingLine(45, '_');
    for (int i = 0; i < processes.size(); ++i)
    {
        std::cout << std::setw(5) << processes[i].getProcessId() << std::setw(10) << "|" << std::setw(5) << processes[i].getArrivalTime() << std::setw(10) << "|" << std::setw(10) << processes[i].getBurstTime();
        std::cout << std::setw(10) << "|" << std::setw(5) << processes[i].getStartTime() << std::setw(5) << "|" << std::setw(5) << processes[i].getCompletionTime() << std::endl;
    }
}

void FIFO::printResults()
{
    // prints ui stuff
    headerNoCls("Scheduling Results", 70, '=');
    dividingLine(50, '_');

    // print out the total time elapsed
    std::cout << std::left << std::setw(30) << "Total Time Elapsed:" << total_runtime << std::endl;

    // calculates and prints the cpu ultization
    calculateCPUutilization();

    // calculates and prints the processes throughput
    calculateThrouphput();

    // calculate and prints the average waiting time
    calculateAverageWaintingTime();
    // calculate and prints the average turn around time
    calculateAverageTurnAroundTime();
}

// default constructor
FIFO::FIFO(std::vector<Process> newprocesses)
{
    processes = newprocesses;
    total_runtime = 0;
}

// destructor
FIFO::~FIFO()
{
}