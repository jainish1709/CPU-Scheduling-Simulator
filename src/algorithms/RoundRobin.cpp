#include "RoundRobin.h"
#include <algorithm>

RoundRobin::RoundRobin(int quantum, int numCPUs) 
    : Scheduler(numCPUs, "Round Robin") {
    algorithm = RR_ALG;
    preemptive = true;
    timeQuantum = quantum;
}

void RoundRobin::schedule() {
    std::sort(processes.begin(), processes.end(), 
              [](const std::shared_ptr<Process>& a, const std::shared_ptr<Process>& b) {
                  if (a->getArrivalTime() == b->getArrivalTime()) {
                      return a->getProcessID() < b->getProcessID();
                  }
                  return a->getArrivalTime() < b->getArrivalTime();
              });
}

std::shared_ptr<Process> RoundRobin::selectNextProcess() {
    if (readyQueue.empty()) {
        return nullptr;
    }
    
    auto process = readyQueue.front();
    readyQueue.pop();
    return process;
}

void RoundRobin::preempt(int cpuID) {
    auto& cpu = cpus[cpuID];
    
    if (cpu->getIsIdle()) return;
    
    if (cpu->getCurrentTimeSlice() >= timeQuantum) {
        auto currentProcess = cpu->getCurrentProcess();
        if (currentProcess && !currentProcess->isCompleted()) {
            cpu->releaseProcess();
            readyQueue.push(currentProcess);
        }
    }
}