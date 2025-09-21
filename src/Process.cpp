#include "Process.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>

Process::Process() : processID(0), processName("P0"), arrivalTime(0), burstTime(0), 
                     remainingTime(0), priority(0), startTime(-1), completionTime(-1), 
                     waitingTime(0), turnaroundTime(0), responseTime(-1), state(NEW) {}

Process::Process(int id, int arrival, int burst, int prio, const std::string& name) 
    : processID(id), processName(name.empty() ? "P" + std::to_string(id) : name),
      arrivalTime(arrival), burstTime(burst), remainingTime(burst), priority(prio), 
      startTime(-1), completionTime(-1), waitingTime(0), turnaroundTime(0), 
      responseTime(-1), state(NEW) {}

Process::Process(const Process& other) 
    : processID(other.processID), processName(other.processName),
      arrivalTime(other.arrivalTime), burstTime(other.burstTime),
      remainingTime(other.remainingTime), priority(other.priority),
      startTime(other.startTime), completionTime(other.completionTime),
      waitingTime(other.waitingTime), turnaroundTime(other.turnaroundTime),
      responseTime(other.responseTime), state(other.state),
      executionHistory(other.executionHistory) {}

Process& Process::operator=(const Process& other) {
    if (this != &other) {
        processID = other.processID;
        processName = other.processName;
        arrivalTime = other.arrivalTime;
        burstTime = other.burstTime;
        remainingTime = other.remainingTime;
        priority = other.priority;
        startTime = other.startTime;
        completionTime = other.completionTime;
        waitingTime = other.waitingTime;
        turnaroundTime = other.turnaroundTime;
        responseTime = other.responseTime;
        state = other.state;
        executionHistory = other.executionHistory;
    }
    return *this;
}

void Process::setStartTime(int time) {
    startTime = time;
    if (responseTime == -1) {
        responseTime = startTime - arrivalTime;
    }
}

void Process::setCompletionTime(int time) {
    completionTime = time;
    calculateMetrics();
}

void Process::executeFor(int time, int currentTime) {
    if (startTime == -1) {
        setStartTime(currentTime);
    }
    
    // Record execution in history
    if (!executionHistory.empty() && 
        executionHistory.back().first + executionHistory.back().second == currentTime) {
        executionHistory.back().second += time;
    } else {
        executionHistory.push_back({currentTime, time});
    }
    
    remainingTime = std::max(0, remainingTime - time);
    
    if (remainingTime <= 0) {
        state = TERMINATED;
        setCompletionTime(currentTime + time);
    }
}

void Process::calculateMetrics() {
    if (completionTime != -1) {
        turnaroundTime = completionTime - arrivalTime;
        waitingTime = turnaroundTime - burstTime;
        if (responseTime == -1 && startTime != -1) {
            responseTime = startTime - arrivalTime;
        }
    }
}

void Process::reset() {
    remainingTime = burstTime;
    state = NEW;
    startTime = completionTime = -1;
    waitingTime = turnaroundTime = responseTime = -1;
    executionHistory.clear();
}

void Process::display() const {
    std::cout << std::setw(8) << processName
              << std::setw(10) << arrivalTime 
              << std::setw(10) << burstTime 
              << std::setw(10) << priority
              << std::setw(12) << (completionTime == -1 ? -1 : completionTime)
              << std::setw(12) << (turnaroundTime == -1 ? -1 : turnaroundTime)
              << std::setw(12) << (waitingTime == -1 ? -1 : waitingTime)
              << std::setw(12) << (responseTime == -1 ? -1 : responseTime) << std::endl;
}

std::string Process::toString() const {
    std::stringstream ss;
    ss << "Process " << processName << " (ID: " << processID << ", Arrival: " 
       << arrivalTime << ", Burst: " << burstTime << ", Priority: " << priority << ")";
    return ss.str();
}

void Process::printHeader() {
    std::cout << std::setw(8) << "Process"
              << std::setw(10) << "Arrival"
              << std::setw(10) << "Burst" 
              << std::setw(10) << "Priority"
              << std::setw(12) << "Completion"
              << std::setw(12) << "Turnaround"
              << std::setw(12) << "Waiting"
              << std::setw(12) << "Response" << std::endl;
    std::cout << std::string(88, '-') << std::endl;
}