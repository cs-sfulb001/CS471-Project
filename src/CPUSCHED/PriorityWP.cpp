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
        //std::cout<<processes.size();
    while(processes.size()>0 || !end){
        //std::cout<<processes.size()<<std::endl;
        //std::cout<<step<<" Step"<<std::endl;
        //waitTillEnter();
         while (processes.size() > 0 && processes[0].getArrivalTime() == step){
            //std::cout<<"Pushing to Queue "<<std::endl;
            ProcessQueue[processes[0].getPriority()].push(processes[0]);
            processes.erase(processes.begin()); // removes the add process
            //std::cout<<processes.size();
            //waitTillEnter();
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
            //std::cout<<running->getRemaingBurst()<<std::endl;
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