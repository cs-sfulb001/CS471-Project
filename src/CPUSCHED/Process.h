#ifndef PROCESS_H_
#define PROCESS_H_

class Process
{
private:
    int arrival_time;
    int burst_time;
    int priority;
    int time_worked_on;
public:
    Process();
    ~Process();
    
    int getArrivalTime() const;
    int getBurstTime() const;
    int getPriority() const;

    void setArrivalTime(int arrivaltime);
    void setBurstTime(int bursttime);
    void setPriority(int priority1);
};

#endif