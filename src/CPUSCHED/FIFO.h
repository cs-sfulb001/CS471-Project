#ifndef FIFO_H_
#define FIFO_H_

#include "vector"
#include "Process.h"

class FIFO
{
private:
    std::vector<Process> processes;
public:
    void sort();
    FIFO(std::vector<Process> newprocesses);
    ~FIFO();
};
#endif