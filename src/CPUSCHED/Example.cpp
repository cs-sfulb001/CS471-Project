


void priorityScheduling(vector<process> Processes){
    vector<queue> ProcessQueue;
    process* Running=nullptr;
    int step = 0;
    bool end = 0;
    while(Processess.size()>0 && !end){
        while(Processess[0].getArrivalTime()==step){
            ProcessQueue[Processess.getPriority()].push(Processes[0]);
            Processes.erase(processes.front());//Removes added Process
        }
        if(running==nullptr){
            for(int i = 0; i < ProcessQueue.size(); i++){//Find Highest Priority Process
                if(!ProcessQueue.emtpy()){
                    Running = &Processqueue.front();
                    break;
                }
            }
            if(Running == nullptr){
                end = 1;
            }
        }
        else
        {
            for(int i = 0; i < Running->getPriority(); i++){//Look for higher Priority 
                if(!ProcessQueue.emtpy()){
                    Running = &Processqueue.front();
                    break;
                }
            }
        }
        Running->setBurstimeremaining(Running->getBurstimeremaining()-1);//Increment the time
        if(Running->getBursttimeremaining()==0){
            ProcessQueue[Running->getPriority()].pop;
        }
        step++;
    }
}