#include "vector"
#include "array"
#include "Process.h"
#include "queue"


/* Holds the information for process that been scheduled
    1. holds the process id
    2. arrival time
    3. holds the start time
    4. holds the end time
    5. holds the burst time
    6. holds the the processes priority
*/
typedef std::array<int, 6> ArrayType;

class PriorityWP
{
private:
    std::vector<Process> processes;
    std::vector<Process> scheduled_processes;
    int total_time;
    
public:
    void PrintResult();
    
    // schedule the process using priority schduling
    void prioityScheduling();

    // sort the processes in the queue
    std::queue<Process> sortProcessQue(std::queue<Process> prossesQue, Process newProcess);

    PriorityWP(std::vector<Process> new_processes);
    ~PriorityWP();
};
