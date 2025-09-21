#include "Priority.h"

Priority::Priority(int numCPUs, bool preempt) 
    : Scheduler(numCPUs, preempt ? "Preemptive Priority" : "Non-preemptive Priority") {
    algorithm = PRIORITY_ALG;
    preemptive = preempt;
}

void Priority::schedule() {
    // No initial sorting needed
}

std::shared_ptr<Process> Priority::selectNextProcess() {
    updatePriorityQueue();
    
    if (priorityQueue.empty()) {
        return nullptr;
    }
    
    auto process = priorityQueue.top();
    priorityQueue.pop();
    return process;
}

void Priority::onProcessArrival(std::shared_ptr<Process> process) {
    if (preemptive) {
        for (auto& cpu : cpus) {
            if (!cpu->getIsIdle()) {
                auto currentProcess = cpu->getCurrentProcess();
                if (currentProcess && 
                    process->getPriority() < currentProcess->getPriority()) {
                    cpu->releaseProcess();
                    priorityQueue.push(currentProcess);
                    cpu->assignProcess(process);
                    return;
                }
            }
        }
    }
    priorityQueue.push(process);
}

void Priority::preempt(int cpuID) {
    if (!preemptive) return;
    
    auto& cpu = cpus[cpuID];
    if (cpu->getIsIdle() || priorityQueue.empty()) return;
    
    auto currentProcess = cpu->getCurrentProcess();
    if (!currentProcess) return;
    
    auto highestPriorityJob = priorityQueue.top();
    if (highestPriorityJob->getPriority() < currentProcess->getPriority()) {
        cpu->releaseProcess();
        priorityQueue.push(currentProcess);
        priorityQueue.pop();
        cpu->assignProcess(highestPriorityJob);
    }
}

void Priority::updatePriorityQueue() {
    while (!readyQueue.empty()) {
        priorityQueue.push(readyQueue.front());
        readyQueue.pop();
    }
}