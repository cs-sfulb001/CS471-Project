#include<vector>
#include<queue>
#include<iostream>
#include<fstream>
#include<string>
#include"Tools/StringManip.h"
#include"Tools/UIHelper.h"
#include"Tools/Choices.h"
#include "Process.h"
#include "FIFO.h"

/*
A process is of the data type std::pair<int, std::pair<int, int>> thus each element is accessed as followed:
Arival time: Process.first
CPU Burst: Process.second.first 
Priority: Process.second.second
*/
/*
Creates a vector of Processes from a given info as requested from the User
Each Process conatains 3 numbers: Arrival time, CPU Burst, Priority
*/
std::vector<Process> setup(){
    int numOfProcesses;
    std::cout<<"How many processes are there?"<<std::endl;
    std::cin>>numOfProcesses;
    std::vector<Process> processes;
    for(int i=0;i<numOfProcesses;i++){
        Process process;
        int arrival, burst, priority;
        std::cout<<"What is the arival time of process "<<(i+1)<<"?"<<std::endl;
        std::cin>>arrival;
        std::cout<<"What is the CPU Burst of process "<<(i+1)<<"?"<<std::endl;
        std::cin>>burst;
        std::cout<<"What is the Priority of process "<<(i+1)<<"?"<<std::endl;
        std::cin>>priority;

        process.setProcessID(i);
        process.setArrivalTime(arrival);
        process.setBurstTime(burst);
        process.setPriority(priority);

        processes.push_back(process);
    }
    return processes;
}
/*
Creates a vector of Processes from a given text file in the Data Directory
Each Process conatains 3 numbers: Arrival time, CPU Burst, Priority
First line of the text file is ignored and each number should be tab deliminated
example:
Junk
15  23  5
*/
std::vector<Process> LoadProcessesFromFile(std::string fileName){
    fileName = "Data/"+fileName;
    std::vector<Process> Processes;
    std::ifstream file;
    file.open(fileName);
    std::string line;
    std::getline(file, line); //Skip first line
    int i = 0;
    while(std::getline(file, line)){
        Process process;
        std::vector<std::string> brokenLine = SplitStringByDelimiter(line, '\t');
        process.setProcessID(i);
        process.setArrivalTime(stoi(brokenLine[0]));
        process.setBurstTime(stoi(brokenLine[1]));
        process.setPriority(stoi(brokenLine[2]));
        Processes.push_back(process);
        ++i;

    }
    return Processes;
}
void listProcesses(std::vector<Process> Processes){
    headerNoCls("List of Processes", 45, '=');
    std::cout<<"Process number | Arrival time | CPU Burst | Priority "<<std::endl;
    dividingLine(45, '_');
    for(int i=0;i<Processes.size();i++){
        std::cout<<std::setw(5)<<Processes[i].getProcessId()<<std::setw(10)<<"|"<<std::setw(5)<<Processes[i].getArrivalTime() <<std::setw(10)<<"|"<<std::setw(8)<<Processes[i].getBurstTime()<<std::setw(5)<<"|"<<std::setw(5)<<Processes[i].getPriority()<<std::endl;
    } 
}
/*

*/
void listResults(std::vector<std::pair<int, int>> Processes, std::vector<std::pair<int,std::pair<int,int>>> ProcessesFinished){
    headerNoCls("Results", 70, '=');
    std::cout<<std::setw(10)<<"Process number"<<"|"<<std::setw(10)<<"Arrival time"<<std::setw(5)<<"|"<<std::setw(10)<<"CPU Burst"<<std::setw(5)<<"|"<<std::setw(10)<<"Start Time"<<std::setw(5)<<"|"<<std::setw(10)<<"Completion"<<std::endl;
    dividingLine(45, '_');
    for(int i=0;i<Processes.size();i++){
        std::cout<<std::setw(5)<<i+1<<std::setw(10)<<"|"<<std::setw(5)<<Processes[i].first<<std::setw(10)<<"|"<<std::setw(10)<<Processes[i].second;
        for(int j=0;j<ProcessesFinished.size();j++){
            if(ProcessesFinished[j].first==i+1){
                std::cout<<std::setw(10)<<"|"<<std::setw(5)<<ProcessesFinished[j].second.first<<std::setw(5)<<"|"<<std::setw(5)<<ProcessesFinished[j].second.second<<std::endl;
                break;
            }            
        }
    } 
}

/*
From assignment 2
Is created for FIFO without priority
*/
std::vector<std::pair<int, std::pair<int, int>>> runtime(std::vector<std::pair<int, int>> Processes){
    std::queue<std::pair<int,std::pair<int,int>>> ProcessQ;
    std::vector<std::pair<int, std::pair<int,int>>> ProcessesLeftToQ;
    for(int i=0;i<Processes.size();i++){
        ProcessesLeftToQ.push_back(std::pair<int, std::pair<int,int>>(i+1, Processes[i]));
    }
    int timestep=0;
    int burstTime=0;
    int waitTime=0;
    std::vector<std::pair<int, std::pair<int, int>>> finishedProcesses;
    std::cout<<"Start of runtime "<<ProcessesLeftToQ.size()<<std::endl;
    while(ProcessesLeftToQ.size()>0||ProcessQ.size()>0){
        for(int i=0;i<ProcessesLeftToQ.size();i++){
            if(timestep==ProcessesLeftToQ[i].second.first)
            {
                ProcessQ.push(ProcessesLeftToQ[i]);
                ProcessesLeftToQ.erase(ProcessesLeftToQ.begin()+i);
                i--;
            }
        }
        if(ProcessQ.size()>0){
            if(burstTime==0&&timestep!=0){
                waitTime=timestep;
            }
            burstTime++;
            if(burstTime==ProcessQ.front().second.second){
                finishedProcesses.push_back(std::pair<int,std::pair<int,int>>(ProcessQ.front().first, std::pair<int,int>(waitTime, timestep+1)));
                burstTime=0;
                waitTime=0;
                ProcessQ.pop();
                if(ProcessQ.size()!=0)
                    waitTime=timestep;
            }
        }
        timestep++;
    }
    return finishedProcesses;
}
main(){
    headerNoCls("CS571 Homework 2", 100, '_');
    headerNoCls("Define processes", 60, '*');
    std::vector<Process> Processes;
    if(choiceYN("Would you like to create a custom process list?"))
    {
        Processes = setup();
    }
    else{
        std::string fileName = choiceWord("What is the name of the file in the Data directory? (Include .txt)");
        Processes = LoadProcessesFromFile(fileName);
    }
    listProcesses(Processes);
    FIFO fifoOrder(Processes);
    std::vector<std::string> choices;
    choices.push_back("FIFO");
    choices.push_back("Priority with preemption");
    switch(choiceList(choices))
    {
    case 0:
        // print the processes using FIFO scheduling
        fifoOrder.printScheduledProcesses();

        /* Calculates and prints out the Total time elapsed, CPU ultilzation, 
        Average waiting time, Average turnaround time, and Response Time  */
        fifoOrder.printResults();
        break;
    case 1:

        break;
    default:
        break;
    }
    //listResults(Processes, runtime(Processes));
}