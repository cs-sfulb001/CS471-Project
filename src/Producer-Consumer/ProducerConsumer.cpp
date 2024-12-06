#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <Windows.h>
#include <vector>
#include <fstream>
#include "Tools/StringManip.h"
#include "Tools/UIHelper.h"

HANDLE Mutex;
bool running = 0; //Allows for thread
int finshedConsumers = 0;

std::vector<std::pair<int, int>> readFile();

int insert_item(std::vector<bool>&buffer, int& full, int& empty);
void ProducerFunction(std::vector<bool>& buffer, int& full, int& empty);
void StartProducerThreads(int numberOfThreads, std::vector<bool>& buffer, int& full, int& emtpy, std::vector<std::thread>& ProducerThreads);

int remove_item(std::vector<bool>&buffer, int& full, int& empty);
void ConsumerFunction(std::vector<bool>& buffer, int& full, int& empty);
void StartConsumerThreads(int numberOfThreads, std::vector<bool>& buffer, int& full, int& emtpy, std::vector<std::thread>& ConsumerThreads);

/*
Items in the buffer is simplified to a bool since
there is no usage of the item beyond it being stored
*/
main(){
    int BufferSize=5;
    Mutex = CreateMutex(NULL, FALSE, NULL);
    std::vector<bool> Buffer;
    std::vector<std::pair<int, int>> ProducerConsumerCount = readFile();
    std::ofstream outputFile;
    outputFile.open("data/RuntimeInfo.txt");
    outputFile << "Number of Producers | Number of Consumers | Runtime (ms)"<<std::endl;
    for(int i = 0; i < ProducerConsumerCount.size(); i++){
        Buffer = std::vector<bool>(BufferSize);
        finshedConsumers=0;
        int empty = BufferSize;
        int full = 0;
        auto start_time = std::chrono::high_resolution_clock::now();
        //Create Threads for the ith interation
        running = 1;
        std::vector<std::thread> ProducerThreads;
        StartProducerThreads(ProducerConsumerCount[i].first, Buffer, full, empty, ProducerThreads);
        std::vector<std::thread> ConsumerThreads;
        StartConsumerThreads(ProducerConsumerCount[i].second, Buffer, full, empty, ConsumerThreads);
        std::cout<<ProducerConsumerCount[i].first<<" Producers threads and "<< ProducerConsumerCount[i].second<<" Consumer Threads started"<<std::endl;
        for(int i = 0; i < ConsumerThreads.size(); i++){
            ConsumerThreads[i].join();
        }
        running = 0;
        std::cout<<"Done with this interation"<<std::endl;
        auto end_time = std::chrono::high_resolution_clock::now();
        auto time = end_time-start_time;
        outputFile << std::setw(10) << ProducerConsumerCount[i].first <<std::setw(11) << "|"
                    << std::setw(10) << ProducerConsumerCount[i].second <<std::setw(12) << "|"
                    << std::setw(6) << time/std::chrono::milliseconds(1)<<std::endl;
        for(int i = 0; i < ProducerThreads.size();i++){
            std::cout<<"Waiting for Producer "<<i<<" to finish"<<std::endl;
            ProducerThreads[i].join();
        }
        Buffer.clear();
    }
    outputFile.close();
}

std::vector<std::pair<int, int>> readFile(){
    std::vector<std::pair<int, int>> ReturnValue;
    std::ifstream ReadInFile;
    ReadInFile.open("data/ProducerConsumer.txt");
    std::string line;
    while(std::getline(ReadInFile, line)){
        std::vector<std::string> brokenLine = SplitStringBySpaceOnly(line);
        int Producer = StringtoInt(brokenLine[0]);
        int Consumer = StringtoInt(brokenLine[1]);
        ReturnValue.push_back(std::pair<int, int>(Producer, Consumer));
    }
    ReadInFile.close();
    return ReturnValue;
}

/*
    Producer Section
*/
int insert_item(std::vector<bool>&buffer, int& full, int& empty){
    for(int i=0;i<buffer.size();i++){
        if(!buffer[i]){
            buffer[i]=1;
            full++;
            empty--;
            return 0;
        }
    }
    return -1;
}
void ProducerFunction(std::vector<bool>& buffer, int& full, int& empty){
        std::cout<<"Producer has started"<<std::endl;
    while(running){
        int time = rand()%1000+1; 
        std::cout<<"Producer is sleeping for "<<time<<"ms"<<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(time));//Sleep for 1ms - 1s 
        std::cout<<"Producer is now awake"<<std::endl;
        if(!running){//Prevents code from going into critical section if the process is set to end
            break;
        }
        while(empty==0); //Wait for an item to be avalible
        std::cout<<"Producer waiting for Mutex"<<std::endl;
        WaitForSingleObject(Mutex, INFINITE);
        std::cout<<"Producer has Mutex"<<std::endl;
        //Critical Section
        insert_item(buffer, full, empty);
        ReleaseMutex(Mutex);
        std::cout<<"Producer released Mutex"<<std::endl;
    }
}

void StartProducerThreads(int numberOfThreads, std::vector<bool>& buffer, int& full, int& empty, std::vector<std::thread>& ProducerThreads){
    for(int i = 0;i < numberOfThreads; i++){
        ProducerThreads.push_back(std::thread(ProducerFunction, std::ref(buffer), std::ref(full), std::ref(empty)));
    }
}

/*
    Consumer Section
*/
int remove_item(std::vector<bool>&buffer, int& full, int& empty){
    for(int i=0;i<buffer.size();i++){
        if(buffer[i]){
            buffer[i]=0;
            full--;
            empty++;
            return 0;
        }
    }
    return -1;
}
void ConsumerFunction(std::vector<bool>& buffer, int& full, int& empty){ //Runs until a request has been fullfiled
    bool item =0;
    while(!item){
        int time = rand()%1000+1;
        std::this_thread::sleep_for(std::chrono::milliseconds(time));//Sleep for 1ms - 1s
        std::cout<<"Consumer is now awake"<<std::endl;
        while(full==0); //Wait for an item to be avalible
        std::cout<<"Consumer waiting for Mutex"<<std::endl;
        WaitForSingleObject(Mutex, INFINITE);
        std::cout<<"Consumer has Mutex"<<std::endl;
        //Critical Section
        if(remove_item(buffer, full, empty)==0){    
            item = 1;
            finshedConsumers++;
        }
        ReleaseMutex(Mutex);
        std::cout<<"Consumer released Mutex"<<std::endl;
    }
}

void StartConsumerThreads(int numberOfThreads, std::vector<bool>& buffer, int& full, int& empty, std::vector<std::thread>& ConsumerThreads){
    for(int i = 0;i < numberOfThreads; i++){
        ConsumerThreads.push_back(std::thread(ConsumerFunction, std::ref(buffer), std::ref(full), std::ref(empty)));
    }
}