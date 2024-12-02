#include<vector>
#include<queue>
#include<iostream>
#include<fstream>
#include<string>
#include"Tools/StringManip.h"
#include"Tools/UIHelper.h"
#include"Tools/Choices.h"
std::vector<std::pair<int, std::pair<int, int>>> setup(){
    int numOfProcesses;
    std::cout<<"How many processes are there?"<<std::endl;
    std::cin>>numOfProcesses;
    std::vector<std::pair<int, std::pair<int, int>>> processes;
    for(int i=0;i<numOfProcesses;i++){
        std::pair<int, std::pair<int, int>> process;
        std::cout<<"What is the arival time of process "<<(i+1)<<"?"<<std::endl;
        std::cin>>process.first;
        std::cout<<"What is the CPU Burst of process "<<(i+1)<<"?"<<std::endl;
        std::cin>>process.second.first;
        std::cout<<"What is the Priority of process "<<(i+1)<<"?"<<std::endl;
        std::cin>>process.second.second;
        processes.push_back(process);   
    }
    return processes;
}
std::vector<std::pair<int, std::pair<int, int>>> LoadProcessesFromFile(std::string fileName){
    fileName = "Data/"+fileName;
    std::vector<std::pair<int, std::pair<int, int>>> Processes;
    std::ifstream file;
    file.open(fileName);
    std::string line;
    std::getline(file, line); //Skip first line
    while(std::getline(file, line)){
        std::pair<int, std::pair<int, int>> process;
        std::vector<std::string> brokenLine = SplitStringByDelimiter(line, '\t');
        process.first = stoi(brokenLine[0]);
        process.second.first = stoi(brokenLine[1]);
        process.second.second = stoi(brokenLine[2]);
        Processes.push_back(process);
    }
    return Processes;
}
void listProcesses(std::vector<std::pair<int, std::pair<int, int>>> Processes){
    headerNoCls("List of Processes", 45, '=');
    std::cout<<"Process number | Arrival time | CPU Burst | Priority "<<std::endl;
    dividingLine(45, '_');
    for(int i=0;i<Processes.size();i++){
        std::cout<<std::setw(5)<<i+1<<std::setw(10)<<"|"<<std::setw(5)<<Processes[i].first<<std::setw(10)<<"|"<<std::setw(8)<<Processes[i].second.first<<std::setw(5)<<"|"<<std::setw(5)<<Processes[i].second.second<<std::endl;
    } 
}
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
    std::vector<std::pair<int, std::pair<int, int>>> Processes;
    if(choiceYN("Would you like to create a custom process list?"))
    {
        Processes = setup();
    }
    else{
        std::string fileName = choiceWord("What is the name of the file in the Data directory? (Include .txt)");
        Processes = LoadProcessesFromFile(fileName);
    }
    listProcesses(Processes);
    std::vector<std::string> choices;
    choices.push_back("FIFO");
    choices.push_back("Priority with preemption");
    switch (choiceList(choices))
    {
    case 0:
        break;
    case 1:

        break;
    default:
        break;
    }
    //listResults(Processes, runtime(Processes));
}