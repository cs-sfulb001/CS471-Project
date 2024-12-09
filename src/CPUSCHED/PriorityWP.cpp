#include "PriorityWP.h"
#include "queue"
#include "iostream"
#include "Tools/StringManip.h"
#include "Tools/UIHelper.h"
#include "Tools/Choices.h"

// schedule the processes using prioriy sort with preemption
void PriorityWP::prioityScheduling()
{
    std::vector<std::queue<Process>> ProcessQueue;
    Process* running = nullptr;
    int step = 0;
    int end = 0;
    headerNoCls("Results", 70, '=');
    std::cout << std::setw(10) << "Process number" << "|" << std::setw(10) << "Arrival time" << std::setw(5) << "|" << std::setw(10) << "CPU Burst" << std::setw(5) << "|" << std::setw(10) << "Start Time" << std::setw(5) << "|" << std::setw(10) << "Completion" << std::endl;
    dividingLine(45, '_');

    while(processes.size()>0 && !end){
         while (ProcessQueue[0].front().getArrivalTime() == step){
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
                if(running == nullptr && processes.size() == 0){// finish
                    end = 1;
                }
            }
         }
         else{
            for(int i = 0; i < running->getPriority(); i++){//
                if(!ProcessQueue[i].empty()){
                    std::cout << std::setw(5) << running->getProcessId() << std::setw(10) << "|" << std::setw(5) << running->getArrivalTime() << std::setw(10) << "|" << std::setw(10) << running->getBurstTime();
                    std::cout << std::setw(10) << "|" << std::setw(5) << running->getStartTime() << std::setw(5) << "|" << std::setw(5) << "interupted"<< std::endl;
                    running = &ProcessQueue[i].front();
                }
            }
         }
        running->setBurstRemaing((running->getRemaingBurst())-1);
        if(running->getRemaingBurst()==0){
            running->setCompletionTime(step);
            scheduled_processes.push_back(ProcessQueue[running->getPriority()].front());
            ProcessQueue[running->getPriority()].pop();
            std::cout << std::setw(5) << running->getProcessId() << std::setw(10) << "|" << std::setw(5) << running->getArrivalTime() << std::setw(10) << "|" << std::setw(10) << running->getBurstTime();
            std::cout << std::setw(10) << "|" << std::setw(5) << running->getStartTime() << std::setw(5) << "|" << std::setw(5) << running->getCompletionTime() << std::endl;
            running = nullptr;
        }
        step++;
    }
    total_time = step;
}

void PriorityWP::PrintResult()
{
    // prints ui stuff
    headerNoCls("Scheduling Results", 70, '=');
    dividingLine(50, '_');

    std::cout << "this is the total time " << total_time << std::endl;
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