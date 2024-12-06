#include "Process.h"


int Process::getArrivalTime() const{
    return arrival_time;
}

void Process::setArrivalTime(int arrivaltime){
    arrival_time = arrivaltime;
}

int Process::getBurstTime() const{
    return burst_time;
}

void Process::setBurstTime(int bursttime){
    burst_time = bursttime;
}

int Process::getPriority() const{
    return priority;
}

void Process::setPriority(int priority1){
    priority = priority1;
}

// default constuctor
Process::Process()
{
    arrival_time;
    burst_time;
    priority;
    time_worked_on;
}

Process::~Process()
{
}
