#include "SJF.h"
#include <iostream>

SJF::SJF(int numCPUs, bool preempt) 
    : Scheduler(numCPUs, preempt ? "Shortest Remaining Time First (SRTF)" : "Shortest Job First (SJF)") {
    algorithm = preempt ? SRTF_ALG : SJF_ALG;
    preemptive = preempt;
}

void SJF::schedule() {
    // No initial sorting needed for SJF
}

std::shared_ptr<Process> SJF::selectNextProcess() {
    updateSJFQueue();
    
    if (sjfQueue.empty()) {
        return nullptr;
    }
    
    auto process = sjfQueue.top();
    sjfQueue.pop();
    return process;
}

void SJF::onProcessArrival(std::shared_ptr<Process> process) {
    if (preemptive) {
        // Check if we need to preempt any running process
        for (auto& cpu : cpus) {
            if (!cpu->getIsIdle()) {
                auto currentProcess = cpu->getCurrentProcess();
                if (currentProcess && 
                    process->getRemainingTime() < currentProcess->getRemainingTime()) {
                    cpu->releaseProcess();
                    sjfQueue.push(currentProcess);
                    cpu->assignProcess(process);
                    return;
                }
            }
        }
    }
    sjfQueue.push(process);
}

void SJF::preempt(int cpuID) {
    if (!preemptive) return;
    
    auto& cpu = cpus[cpuID];
    if (cpu->getIsIdle()) return;
    
    auto currentProcess = cpu->getCurrentProcess();
    if (!currentProcess || sjfQueue.empty()) return;
    
    auto shortestJob = sjfQueue.top();
    if (shortestJob->getRemainingTime() < currentProcess->getRemainingTime()) {
        cpu->releaseProcess();
        sjfQueue.push(currentProcess);
        sjfQueue.pop();
        cpu->assignProcess(shortestJob);
    }
}

void SJF::updateSJFQueue() {
    while (!readyQueue.empty()) {
        sjfQueue.push(readyQueue.front());
        readyQueue.pop();
    }
}