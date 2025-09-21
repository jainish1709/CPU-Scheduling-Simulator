#include "FCFS.h"
#include <algorithm>

FCFS::FCFS(int numCPUs) : Scheduler(numCPUs, "First Come First Served (FCFS)") {
    algorithm = FCFS_ALG;
    preemptive = false;
}

void FCFS::schedule() {
    std::sort(processes.begin(), processes.end(), 
              [](const std::shared_ptr<Process>& a, const std::shared_ptr<Process>& b) {
                  if (a->getArrivalTime() == b->getArrivalTime()) {
                      return a->getProcessID() < b->getProcessID();
                  }
                  return a->getArrivalTime() < b->getArrivalTime();
              });
}

std::shared_ptr<Process> FCFS::selectNextProcess() {
    if (readyQueue.empty()) {
        return nullptr;
    }
    
    auto process = readyQueue.front();
    readyQueue.pop();
    return process;
}