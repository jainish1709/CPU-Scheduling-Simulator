#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <vector>
#include <iostream>

enum ProcessState {
    NEW,
    READY, 
    RUNNING,
    WAITING,
    TERMINATED
};

class Process {
private:
    int processID;
    std::string processName;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int priority;
    int startTime;
    int completionTime;
    int waitingTime;
    int turnaroundTime;
    int responseTime;
    ProcessState state;
    std::vector<std::pair<int, int>> executionHistory;

public:
    // Constructors
    Process();
    Process(int id, int arrival, int burst, int prio = 0, const std::string& name = "");
    Process(const Process& other);
    Process& operator=(const Process& other);
    
    // Getters
    int getProcessID() const { return processID; }
    std::string getProcessName() const { return processName; }
    int getArrivalTime() const { return arrivalTime; }
    int getBurstTime() const { return burstTime; }
    int getRemainingTime() const { return remainingTime; }
    int getPriority() const { return priority; }
    int getStartTime() const { return startTime; }
    int getCompletionTime() const { return completionTime; }
    int getWaitingTime() const { return waitingTime; }
    int getTurnaroundTime() const { return turnaroundTime; }
    int getResponseTime() const { return responseTime; }
    ProcessState getState() const { return state; }
    const std::vector<std::pair<int, int>>& getExecutionHistory() const { return executionHistory; }
    
    // Setters
    void setStartTime(int time);
    void setCompletionTime(int time);
    void setState(ProcessState newState) { state = newState; }
    void setRemainingTime(int time) { remainingTime = time; }
    void setPriority(int prio) { priority = prio; }
    
    // Utility methods
    void executeFor(int time, int currentTime);
    void calculateMetrics();
    bool isCompleted() const { return remainingTime <= 0; }
    void reset();
    
    // Display
    void display() const;
    std::string toString() const;
    static void printHeader();
};

#endif // PROCESS_H