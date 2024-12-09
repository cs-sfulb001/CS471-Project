#ifndef PROCESS_H_
#define PROCESS_H_

class Process
{
private:
    // holds the id for process
    int process_id;

    // holds arrival time
    int arrival_time;

    // holds burst time
    int burst_time;

    // holds priority
    int priority;

    // holds the time at which a 
    int start_time;

    // holds the time at which the process is completed
    int completion_time;

    // the amount of burst time left
    int burst_remaining;

public:
    // constructor
    Process();

    // destructor
    ~Process();
    
    // setters
    void setProcessID(int processID);
    void setArrivalTime(int arrivaltime);
    void setBurstTime(int bursttime);
    void setPriority(int priority1);
    void setStartTime(int start);
    void setCompletionTime(int copmletion);
    void setBurstRemaing(int timeworkedon);

    // getters 
    int getProcessId() const;
    int getArrivalTime() const;
    int getBurstTime() const;
    int getPriority() const;
    int getStartTime() const;
    int getCompletionTime() const;
    int getRemaingBurst() const;
};

#endif