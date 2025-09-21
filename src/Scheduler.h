#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "Process.h"
#include "core/CPU.h"
#include <vector>
#include <memory>
#include <queue>
#include <string>

enum SchedulingAlgorithm {
    FCFS_ALG,
    SJF_ALG,
    SRTF_ALG,
    RR_ALG,
    PRIORITY_ALG
};

class Scheduler {
protected:
    std::vector<std::shared_ptr<Process>> processes;
    std::vector<std::shared_ptr<Process>> allProcesses;
    std::vector<std::unique_ptr<CPU>> cpus;
    std::queue<std::shared_ptr<Process>> readyQueue;
    int currentTime;
    int timeQuantum;
    SchedulingAlgorithm algorithm;
    std::string algorithmName;
    bool preemptive;
    bool verbose;

    // Helper methods
    void updateReadyQueue();
    bool areAllProcessesCompleted() const;
    void advanceTime();
    std::vector<std::shared_ptr<Process>> getArrivedProcesses() const;
    void assignProcessesToCPUs();
    void displayCurrentState() const;

public:
    Scheduler(int numCPUs = 1, const std::string& name = "Base Scheduler");
    virtual ~Scheduler() = default;
    
    // Process management
    void addProcess(std::shared_ptr<Process> process);
    void addProcesses(const std::vector<std::shared_ptr<Process>>& procs);
    
    // Core scheduling methods
    virtual void schedule() = 0;
    virtual void preempt(int cpuID) {}
    virtual std::shared_ptr<Process> selectNextProcess() = 0;
    virtual void onProcessArrival(std::shared_ptr<Process> process) {}
    
    // Simulation control
    void run();
    void reset();
    
    // Getters/Setters
    void setTimeQuantum(int quantum) { timeQuantum = quantum; }
    void setVerbose(bool v) { verbose = v; }
    int getCurrentTime() const { return currentTime; }
    std::string getAlgorithmName() const { return algorithmName; }
    
    // Statistics and output
    void printResults() const;
    void printGanttChart() const;
    void printStatistics() const;
    
    // Statistics methods 
    double calculateAverageWaitingTime() const;
    double calculateAverageTurnaroundTime() const;
    double calculateAverageResponseTime() const;
    double calculateAverageCPUUtilization() const;
    double calculateThroughput() const;
};

#endif // SCHEDULER_H