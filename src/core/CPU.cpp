#include "CPU.h"
#include <iostream>
#include <iomanip>

CPU::CPU(int id) : cpuID(id), isIdle(true), totalIdleTime(0), 
                   totalBusyTime(0), currentTimeSlice(0) {}

void CPU::assignProcess(std::shared_ptr<Process> process) {
    if (!process) return;
    
    currentProcess = process;
    isIdle = false;
    currentTimeSlice = 0;
    process->setState(RUNNING);
}

void CPU::releaseProcess() {
    if (currentProcess) {
        if (currentProcess->isCompleted()) {
            currentProcess->setState(TERMINATED);
        } else {
            currentProcess->setState(READY);
        }
        currentProcess = nullptr;
    }
    isIdle = true;
    currentTimeSlice = 0;
}

void CPU::tick(int currentTime) {
    if (isIdle) {
        totalIdleTime++;
    } else {
        totalBusyTime++;
        currentTimeSlice++;
        
        if (currentProcess) {
            currentProcess->executeFor(1, currentTime);
            if (currentProcess->isCompleted()) {
                releaseProcess();
            }
        }
    }
}

double CPU::getUtilization() const {
    int totalTime = totalIdleTime + totalBusyTime;
    return totalTime > 0 ? (double)totalBusyTime / totalTime * 100.0 : 0.0;
}

void CPU::reset() {
    currentProcess = nullptr;
    isIdle = true;
    totalIdleTime = 0;
    totalBusyTime = 0;
    currentTimeSlice = 0;
}

void CPU::displayStatus() const {
    std::cout << "CPU " << cpuID << ": ";
    if (isIdle) {
        std::cout << "IDLE";
    } else {
        std::cout << "Running " << currentProcess->getProcessName()
                  << " (Remaining: " << currentProcess->getRemainingTime() << ")";
    }
    std::cout << " | Utilization: " << std::fixed << std::setprecision(1) 
              << getUtilization() << "%" << std::endl;
}