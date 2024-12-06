#include "FIFO.h"
#include "iostream"

void FIFO::sort(){
    std::cout<<"This is a test\n";
}

FIFO::FIFO(std::vector<Process> newprocesses)
{
    processes = newprocesses;
}

FIFO::~FIFO()
{
}