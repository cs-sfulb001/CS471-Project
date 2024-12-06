#include "Process.h"

// set the processes id
void Process::setProcessID(int processID){
    process_id = processID;
}

int Process::getProcessId() const{
    return process_id;
}

// set the processes arrival time
void Process::setArrivalTime(int arrivaltime){
    arrival_time = arrivaltime;
}

// get the processes arrival time 
int Process::getArrivalTime() const{
    return arrival_time;
}

// set the process priority
void Process::setBurstTime(int bursttime){
    burst_time = bursttime;
}

// get the processes burst time
int Process::getBurstTime() const{
    return burst_time;
}

// set the process priory
void Process::setPriority(int priority1){
    priority = priority1;
}

// get the process priority
int Process::getPriority() const{
    return priority;
}

//set the start time of a process (for FIFO scheduling)
void Process::setStartTime(int start1){
    start_time = start1;
}

// gets the start time of a process
int Process::getStartTime() const{
    return start_time;
}

// sets the processes completion time
void Process::setCompletionTime(int completion){
    completion_time = completion;
}

// gets the time completed
int Process::getCompletionTime() const{
    return completion_time;
}

//sets the amounnt of burst time remaining
void Process::setBurstRemaing(int timeworkedon){
    burst_remaining = timeworkedon;
}

// gets the remaing burst time
int Process::getRemaingBurst() const{
    return burst_remaining;
}

// default constuctor
Process::Process()
{
    process_id;
    arrival_time;
    burst_time;
    priority;
    start_time;
    completion_time;
    burst_remaining;
}

Process::~Process()
{
}
