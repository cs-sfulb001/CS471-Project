#include "PriorityWP.h"
#include "queue"
#include "iostream"
#include "Tools/StringManip.h"
#include "Tools/UIHelper.h"
#include "Tools/Choices.h"

// schedule the processes using prioriy sort with preemption
void PriorityWP::prioityScheduling()
{
    std::vector<std::queue<Process>> ProcessQueue(20);
    Process* running = nullptr;
    int step = 0;
    bool end = 0;
    headerNoCls("Results", 70, '=');
    std::cout << std::setw(10) << "Process number" << "|" << std::setw(10) << "Arrival time" << std::setw(5) << "|" << std::setw(10) << "CPU Burst" << std::setw(5) << "|" << std::setw(10) << "Start Time" << std::setw(5) << "|" << std::setw(10) << "Completion" << std::endl;
    dividingLine(45, '_');
    while(processes.size()>0 || !end){
         while (processes.size() > 0 && processes[0].getArrivalTime() == step){
            ProcessQueue[processes[0].getPriority()].push(processes[0]);
            processes.erase(processes.begin()); // removes the add process
         }
         if(running == nullptr){
            for(int i = 0; i < ProcessQueue.size(); i++){//find highest priority
                if(!ProcessQueue[i].empty()){
                running = &ProcessQueue[i].front();
                running->setStartTime(step);
                break;
                }
                if(running == nullptr && processes.size() == 0 && i == ProcessQueue.size()-1){// finish
                    end = 1;
                    step--; //Disregard this step
                }
            }
         }
         else{
            for(int i = 0; i < running->getPriority(); i++){//
                if(!ProcessQueue[i].empty()){
                    std::cout << std::setw(5) << running->getProcessId() << std::setw(10) << "|" << std::setw(5) << running->getArrivalTime() << std::setw(10) << "|" << std::setw(10) << running->getBurstTime();
                    std::cout << std::setw(10) << "|" << std::setw(5) << running->getStartTime() << std::setw(5) << "|" << std::setw(5) << "interupted"<< std::endl;
                    running = &ProcessQueue[i].front();
                    running->setStartTime(step);
                }
            }
         }
        step++;
        if(running!=nullptr)
        {
            running->setBurstRemaing((running->getRemaingBurst())-1);
            if(running->getRemaingBurst()==0){
                running->setCompletionTime(step);
                scheduled_processes.push_back(ProcessQueue[running->getPriority()].front());
                ProcessQueue[running->getPriority()].pop();
                std::cout << std::setw(5) << running->getProcessId() << std::setw(10) << "|" << std::setw(5) << running->getArrivalTime() << std::setw(10) << "|" << std::setw(10) << running->getBurstTime();
                std::cout << std::setw(10) << "|" << std::setw(5) << running->getStartTime() << std::setw(5) << "|" << std::setw(5) << running->getCompletionTime() << std::endl;
                running = nullptr;
            }
        }
    }
    total_time = step;
}

void PriorityWP::calculateCPUutilization()
{

    // holds the total burst time of the
    double sum = 0;

    // find the sum of the burst times
    for (int i = 0; i < scheduled_processes.size(); i++)
    {
        sum = sum + scheduled_processes[i].getBurstTime();
    }

    // calculate the cpu utiliztion
    double cpu_utilization = 100 * (sum / total_time);

    // print the results of the calculation
    std::cout << std::fixed << std::setprecision(2);
    std::cout << std::left << std::setw(30) << "CPU Utilization:" << cpu_utilization << "%\n";
}

void PriorityWP::calculateAverageTurnAroundTime()
{
    // holds the total waiting total of all processed
    double total_turnaround_time = 0;

    // calculate the total turnaround time
    for (int i = 0; i < scheduled_processes.size(); ++i)
    {
        // calculate the indiviadual turnaround time
        total_turnaround_time += scheduled_processes[i].getCompletionTime() - scheduled_processes[i].getArrivalTime();
    }

    // calculate the average waiting time
    double average_turnaround_time = total_turnaround_time / scheduled_processes.size();

    // print the calculated average waiting time
    std::cout << std::fixed << std::setprecision(2);
    std::cout << std::left << std::setw(30) << "Average Turnaround Time" << average_turnaround_time << std::endl;
}

void PriorityWP::calculateAverageWaintingTime()
{
    // holds the total waiting total of all processed
    double total_waiting_time = 0;

    for (int i = 0; i < scheduled_processes.size(); ++i)
    {
        // calculate the waiting time
        total_waiting_time += scheduled_processes[i].getStartTime() - scheduled_processes[i].getArrivalTime();
    }

    // calculate the average waiting time
    double average_waiting_time = total_waiting_time / scheduled_processes.size();

    // print the calculated average waiting time
    std::cout << std::fixed << std::setprecision(2);
    std::cout << std::left << std::setw(30) << "Average Waiting Time:" << average_waiting_time << std::endl;
}

void PriorityWP::calculateThrouphput()
{

    // holds the total burst time of the
    double sumBurstTimes = 0;

    // find the sum of the burst times
    for (int i = 0; i < scheduled_processes.size(); i++)
    {
        sumBurstTimes = sumBurstTimes + scheduled_processes[i].getBurstTime();
    }

    // calculates the throughput
    double throughput = sumBurstTimes / scheduled_processes.size();

    // print the calculated throughput of the processes
    std::cout << std::fixed << std::setprecision(2);
    std::cout << std::left << std::setw(30) << "Throughput:" << throughput << std::endl;
}

void PriorityWP::PrintResult()
{
    // prints ui stuff
    headerNoCls("Scheduling Results", 70, '=');
    dividingLine(50, '_');

    // print out the total time elapsed
    std::cout << std::left << std::setw(30) << "Total Time Elapsed:" << total_time << std::endl;

     // calculates and prints the cpu ultization
    calculateCPUutilization();

    // calculates and prints the processes throughput
    calculateThrouphput();

    // calculate and prints the average waiting time
    calculateAverageWaintingTime();

    // calculate and prints the average turn around time
    calculateAverageTurnAroundTime();
}


// defualt constuctor
PriorityWP::PriorityWP(std::vector<Process> new_processes)
{
    processes = new_processes;
    scheduled_processes;
    total_time = 0;
}

PriorityWP::~PriorityWP()
{
}