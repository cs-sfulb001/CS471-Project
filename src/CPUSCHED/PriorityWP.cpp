#include "PriorityWP.h"
#include "queue"
#include "iostream"
#include "Tools/StringManip.h"
#include "Tools/UIHelper.h"
#include "Tools/Choices.h"

// schedule the processes using prioriy sort with preemption
void PriorityWP::prioitySort()
{
    std::queue<Process> process_que;

    // go through each process indivdually and schedule them
    for (int i = 0; i < processes.size(); i++)
    {
        if (processes[i].getArrivalTime() < total_time)
        {
            std::cout << "Process " << processes[i].getProcessId() << " arrived during a more imporant process and is sent to the que" << std::endl;
            processes[i].setBurstRemaing(processes[i].getBurstTime());
            process_que = sortProcessQue(process_que, processes[i]);

            std::cout << "This is the process que at the end of each cycle" << std::endl;
            std::queue<Process> temporaryq = process_que;
            std::cout << "ID   Burst_R  Priority" << std::endl;
            while (!temporaryq.empty())
            {
                std::cout << temporaryq.front().getProcessId() << "   " << temporaryq.front().getRemaingBurst() << "   " << temporaryq.front().getPriority() << std::endl;
                temporaryq.pop();
            }
            continue;
        }

        // check to see if the current process has the lower priority the fisrt item in the queue and run the processes in the que until total time reaches the next process
        if (process_que.front().getPriority() < processes[i].getPriority())
        {
            std::cout << "The current process, " << processes[i].getProcessId() << " has less priority than the que" << std::endl;
            processes[i].setBurstRemaing(processes[i].getBurstTime());
            process_que = sortProcessQue(process_que, processes[i]);
            // run processes from the que until it reaches the next process
            int estimated_completion = process_que.front().getRemaingBurst() + total_time;
            while (estimated_completion < processes[i + 1].getArrivalTime())
            {
                std::cout << "filling in the gap" << std::endl;
                // check to see if the process id has been scheduled before, if not set the start time
                bool scheduled_before = false;
                for (int i = 0; i < scheduled_processes.size(); ++i)
                {
                    if (process_que.front().getProcessId() == scheduled_processes[i].at(0))
                    {
                        scheduled_before = true;
                        break;
                    }
                }

                if (scheduled_before == false)
                {
                    process_que.front().setStartTime(total_time);
                }

                // if process has not already been scheduled set the start time to the current time
                process_que.front().setCompletionTime(estimated_completion);

                ArrayType temp = {process_que.front().getProcessId(), process_que.front().getArrivalTime(), process_que.front().getStartTime(), process_que.front().getCompletionTime(),
                                  process_que.front().getRemaingBurst(), process_que.front().getPriority()};

                scheduled_processes.push_back(temp);
                total_time = process_que.front().getCompletionTime();
                std::cout << "Total time being set to -> " << total_time << std::endl;
                process_que.pop();

                estimated_completion = total_time + process_que.front().getRemaingBurst();
                std::cout << "Next proccess in the que should run at " << estimated_completion << std::endl;
            }
            continue;
        }

        // if the queue is clear the processes get scheduled as such
        int j = i + 1;
        for (j; j < processes.size(); j++)
        {
            if (processes[j].getPriority() < processes[i].getPriority())
            {
                std::cout << "Found! | " << "Current proccess: " << processes[i].getProcessId() << " Next important process: " << processes[j].getProcessId() << std::endl;
                if ((total_time + processes[i].getBurstTime()) < processes[j].getArrivalTime())
                {
                    std::cout << "Process has been scheduled and completed" << std::endl;
                    std::cout << "number that is being calulated is: " << total_time + processes[i].getBurstTime() << std::endl;
                    std::cout << "Arrival time of next important process: " << processes[j].getArrivalTime() << std::endl;
                    if (processes[i].getArrivalTime() > total_time)
                    {
                        std::cout << "Process arrived after the current total time" << std::endl;
                        processes[i].setStartTime(processes[i].getArrivalTime());
                        processes[i].setCompletionTime(processes[i].getArrivalTime() + processes[i].getBurstTime());
                        total_time = processes[i].getCompletionTime();
                        std::cout << "Total time being set to -> " << total_time << std::endl;
                        ArrayType temp = {processes[i].getProcessId(), processes[i].getArrivalTime(), processes[i].getStartTime(), processes[i].getCompletionTime(), processes[i].getBurstTime(), processes[i].getPriority()};
                        // schedule the process
                        scheduled_processes.push_back(temp);
                    }
                    else
                    {
                        std::cout << "Process will start at current time" << std::endl;
                        processes[i].setStartTime(total_time);
                        processes[i].setCompletionTime(total_time + processes[i].getBurstTime());
                        total_time = processes[i].getCompletionTime();
                        ArrayType temp = {processes[i].getProcessId(), processes[i].getArrivalTime(), processes[i].getStartTime(), processes[i].getCompletionTime(), processes[i].getBurstTime(), processes[i].getPriority()};
                        // schedule the process
                        scheduled_processes.push_back(temp);
                    }
                }
                else
                {
                    std::cout << "Process has been scheduled but not completed" << std::endl;
                    if (processes[i].getArrivalTime() > total_time)
                    {
                        std::cout << "Process arrived after the current total time" << std::endl;
                        processes[i].setStartTime(processes[i].getArrivalTime());
                        processes[i].setBurstRemaing(processes[i].getBurstTime() - (processes[j].getArrivalTime() - processes[i].getArrivalTime()));
                        std::cout << "Remaining burst time set to -> " << processes[i].getBurstTime() << std::endl;
                        total_time = processes[j].getArrivalTime();
                        std::cout << "Total time being set to -> " << total_time << std::endl;
                        ArrayType temp = {processes[i].getProcessId(), processes[i].getArrivalTime(), processes[i].getStartTime(), processes[j].getArrivalTime(),
                                          (processes[j].getArrivalTime() - processes[i].getArrivalTime()), processes[i].getPriority()};
                        // schedule the process
                        scheduled_processes.push_back(temp);

                        process_que = sortProcessQue(process_que, processes[i]);

                        std::cout << "This is the process que at the end of each cycle" << std::endl;
                        std::queue<Process> temporaryq = process_que;
                        std::cout << "ID   Burst_R  Priority" << std::endl;
                        while (!temporaryq.empty())
                        {
                            std::cout << temporaryq.front().getProcessId() << "   " << temporaryq.front().getRemaingBurst() << "   " << temporaryq.front().getPriority() << std::endl;
                            temporaryq.pop();
                        }
                    }
                    else
                    {
                        std::cout << "Process will start at current time" << std::endl;
                        processes[i].setStartTime(total_time);
                        processes[i].setBurstRemaing(processes[i].getBurstTime() - (processes[j].getArrivalTime() - total_time));
                        ArrayType temp = {processes[i].getProcessId(), processes[i].getArrivalTime(), processes[i].getStartTime(), processes[j].getArrivalTime(),
                                          (processes[j].getArrivalTime() - total_time), processes[i].getPriority()};
                        total_time = processes[j].getArrivalTime();
                        // schedule the process
                        scheduled_processes.push_back(temp);

                        process_que = sortProcessQue(process_que, processes[i]);

                        std::cout << "This is the process que at the end of each cycle" << std::endl;
                        std::queue<Process> temporaryq = process_que;
                        std::cout << "ID   Burst_R  Priority" << std::endl;
                        while (!temporaryq.empty())
                        {
                            std::cout << temporaryq.front().getProcessId() << "   " << temporaryq.front().getRemaingBurst() << "   " << temporaryq.front().getPriority() << std::endl;
                            temporaryq.pop();
                        }
                    }
                }
                break;
            }
            std::cout << "Not found | Current process :" << processes[i].getProcessId() << std::endl;
        }

        // if there is no proccess with higher priority and the process is not scheduled run completely
        if (j == processes.size() && checkQueue(processes[i].getProcessId(), process_que) == false)
        {
            std::cout << "This Process " << processes[i].getProcessId() << " has the highest priority and will run completely" << std::endl;
            if (processes[i].getArrivalTime() > total_time)
            {
                std::cout << "Process arrived after the current total time" << std::endl;
                processes[i].setStartTime(processes[i].getArrivalTime());
                processes[i].setCompletionTime(processes[i].getArrivalTime() + processes[i].getBurstTime());
                total_time = processes[i].getCompletionTime();
                ArrayType temp = {processes[i].getProcessId(), processes[i].getArrivalTime(), processes[i].getStartTime(), processes[i].getCompletionTime(), processes[i].getBurstTime(), processes[i].getPriority()};
                // schedule the process
                scheduled_processes.push_back(temp);
            }
            else
            {
                std::cout << "Process will start at current time" << std::endl;
                processes[i].setStartTime(total_time);
                processes[i].setCompletionTime(total_time + processes[i].getBurstTime());
                total_time = processes[i].getCompletionTime();
                ArrayType temp = {processes[i].getProcessId(), processes[i].getArrivalTime(), processes[i].getStartTime(), processes[i].getCompletionTime(), processes[i].getBurstTime(), processes[i].getPriority()};
                // schedule the process
                scheduled_processes.push_back(temp);
            }
        }

        std::cout << "This is the process que at the end of each cycle" << std::endl;
        std::queue<Process> temporaryq = process_que;
        std::cout << "ID   Burst_R  Priority" << std::endl;
        while (!temporaryq.empty())
        {
            std::cout << temporaryq.front().getProcessId() << "   " << temporaryq.front().getRemaingBurst() << "   " << temporaryq.front().getPriority() << std::endl;
            temporaryq.pop();
        }

        /**/
    }
    // the que is still full after running 
    if (!process_que.empty())
    {
        int estimated_completion = total_time + process_que.front().getRemaingBurst();
        bool scheduled_before = false;
        for (int i = 0; i < scheduled_processes.size(); ++i)
        {
            if (process_que.front().getProcessId() == scheduled_processes[i].at(0))
            {
                scheduled_before = true;
                break;
            }
        }

        if (scheduled_before == false)
        {
            process_que.front().setStartTime(total_time);
        }

        // if process has not already been scheduled set the start time to the current time
        process_que.front().setCompletionTime(estimated_completion);

        ArrayType temp = {process_que.front().getProcessId(), process_que.front().getArrivalTime(), process_que.front().getStartTime(), process_que.front().getCompletionTime(),
                          process_que.front().getRemaingBurst(), process_que.front().getPriority()};

        scheduled_processes.push_back(temp);
        total_time = process_que.front().getCompletionTime();
        std::cout << "Total time being set to -> " << total_time << std::endl;
        process_que.pop();

        estimated_completion = total_time + process_que.front().getRemaingBurst();
        std::cout << "Next proccess in the que should run at " << estimated_completion << std::endl;
    }
}
// the proccess is in the queue return true
bool PriorityWP::checkQueue(int processID, std::queue<Process> processqueue)
{
    if (processqueue.empty())
    {
        return false;
    }
    else
    {
        std::queue<Process> tempqueue = processqueue;
        while (!tempqueue.empty())
        {
            if (tempqueue.front().getProcessId() == processID)
                return true;
            else
            {
                tempqueue.pop();
            }
        }
        return false;
    }
}

// sort the que based on how the porcess
std::queue<Process> PriorityWP::sortProcessQue(std::queue<Process> processQue, Process newProcess)
{
    // if the queue is empty push the process to the queue
    // que used to store results
    std::queue<Process> result_queue;

    if (processQue.empty())
    {
        std::cout << '\t' << "queue is empty add new process" << std::endl;
        result_queue.push(newProcess);

        return result_queue;
    }
    // if there are processes in the que
    else
    {
        // create a temp que to look for the right place to store the process
        std::queue<Process> destruct_queue = processQue;

        // que used to store results
        std::queue<Process> result_queue;

        // while the destruction que is not empty
        while (!destruct_queue.empty())
        {
            if (destruct_queue.front().getPriority() < newProcess.getPriority() || destruct_queue.front().getPriority() == newProcess.getPriority())
            {

                // add the higher priority que to the reult queue
                result_queue.push(destruct_queue.front());
                // pop the front of the queue
                destruct_queue.pop();
            }
            else
            {
                // add the process where it belongs
                result_queue.push(newProcess);

                // push the rest of the other queue into the result queue
                while (!destruct_queue.empty())
                {
                    result_queue.push(destruct_queue.front());
                    // pop the front of the queue
                    destruct_queue.pop();
                }
                return result_queue;
                ;
            }
        }

        // if all processes come before the new process add it to the back of the result que
        if (destruct_queue.empty())
            result_queue.push(newProcess);

        // set the process_que equal to the result que
        return result_queue;
    }
}

void PriorityWP::PrintResult()
{
    // prints ui stuff
    headerNoCls("Scheduling Results", 70, '=');
    dividingLine(50, '_');

    for (int x = 0; x < scheduled_processes.size(); x++)
    {
        std::cout << scheduled_processes[x].at(0) << "   " << scheduled_processes[x].at(1) << "   " << scheduled_processes[x].at(2)
                  << "   " << scheduled_processes[x].at(3) << "  " << scheduled_processes[x].at(4) << "   " << scheduled_processes[x].at(5) << std::endl;
    }

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