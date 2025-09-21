#include "Scheduler.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

Scheduler::Scheduler(int numCPUs, const std::string& name) 
    : currentTime(0), timeQuantum(4), algorithm(FCFS_ALG), 
      algorithmName(name), preemptive(false), verbose(false) {
    
    for (int i = 0; i < numCPUs; ++i) {
        cpus.push_back(std::make_unique<CPU>(i));
    }
}

void Scheduler::addProcess(std::shared_ptr<Process> process) {
    if (process) {
        processes.push_back(process);
        allProcesses.push_back(std::make_shared<Process>(*process));
    }
}

void Scheduler::addProcesses(const std::vector<std::shared_ptr<Process>>& procs) {
    for (const auto& process : procs) {
        addProcess(process);
    }
}

void Scheduler::run() {
    std::cout << "\n=== Running " << algorithmName << " ===" << std::endl;
    std::cout << "Number of CPUs: " << cpus.size() << std::endl;
    if (preemptive && algorithm == RR_ALG) {
        std::cout << "Time Quantum: " << timeQuantum << std::endl;
    }
    std::cout << "Total Processes: " << processes.size() << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    
    schedule();
    
    while (!areAllProcessesCompleted()) {
        if (verbose && currentTime % 5 == 0) {
            std::cout << "\n--- Time " << currentTime << " ---" << std::endl;
        }
        
        updateReadyQueue();
        assignProcessesToCPUs();
        
        for (size_t i = 0; i < cpus.size(); ++i) {
            cpus[i]->tick(currentTime);
            if (preemptive) {
                preempt(static_cast<int>(i));
            }
        }
        
        if (verbose && currentTime % 5 == 0) {
            displayCurrentState();
        }
        
        advanceTime();
    }
    
    std::cout << "Simulation completed at time " << currentTime << std::endl;
}

void Scheduler::updateReadyQueue() {
    auto arrivedProcesses = getArrivedProcesses();
    for (auto& process : arrivedProcesses) {
        if (process->getState() == NEW) {
            process->setState(READY);
            readyQueue.push(process);
            onProcessArrival(process);
        }
    }
}

bool Scheduler::areAllProcessesCompleted() const {
    return std::all_of(processes.begin(), processes.end(),
                      [](const std::shared_ptr<Process>& p) {
                          return p->getState() == TERMINATED;
                      });
}

void Scheduler::advanceTime() {
    currentTime++;
}

std::vector<std::shared_ptr<Process>> Scheduler::getArrivedProcesses() const {
    std::vector<std::shared_ptr<Process>> arrived;
    for (const auto& process : processes) {
        if (process->getArrivalTime() <= currentTime && process->getState() == NEW) {
            arrived.push_back(process);
        }
    }
    return arrived;
}

void Scheduler::assignProcessesToCPUs() {
    for (auto& cpu : cpus) {
        if (cpu->getIsIdle()) {
            auto nextProcess = selectNextProcess();
            if (nextProcess) {
                cpu->assignProcess(nextProcess);
            }
        }
    }
}

void Scheduler::displayCurrentState() const {
    for (const auto& cpu : cpus) {
        std::cout << "  ";
        cpu->displayStatus();
    }
    std::cout << "  Ready Queue Size: " << readyQueue.size() << std::endl;
}

void Scheduler::reset() {
    currentTime = 0;
    
    while (!readyQueue.empty()) {
        readyQueue.pop();
    }
    
    for (auto& cpu : cpus) {
        cpu->reset();
    }
    
    processes.clear();
    for (const auto& original : allProcesses) {
        processes.push_back(std::make_shared<Process>(*original));
    }
}

void Scheduler::printResults() const {
    std::cout << "\n=== SCHEDULING RESULTS ===" << std::endl;
    Process::printHeader();
    
    for (const auto& process : processes) {
        process->display();
    }
    
    std::cout << std::string(88, '-') << std::endl;
    printStatistics();
}

void Scheduler::printGanttChart() const {
    std::cout << "\n=== GANTT CHART ===" << std::endl;
    
    int maxTime = 0;
    for (const auto& process : processes) {
        if (process->getCompletionTime() > maxTime) {
            maxTime = process->getCompletionTime();
        }
    }
    
    for (size_t cpuID = 0; cpuID < cpus.size(); ++cpuID) {
        std::cout << "CPU " << cpuID << ": ";
        
        std::vector<std::string> timeline(maxTime, "--");
        
        for (const auto& process : processes) {
            for (const auto& execution : process->getExecutionHistory()) {
                int startTime = execution.first;
                int duration = execution.second;
                
                for (int t = startTime; t < startTime + duration && t < maxTime; ++t) {
                    if (timeline[t] == "--") {
                        timeline[t] = process->getProcessName().substr(0, 2);
                    }
                }
            }
        }
        
        for (const auto& slot : timeline) {
            std::cout << "|" << slot;
        }
        std::cout << "|" << std::endl;
    }
    
    std::cout << "Time: ";
    for (int t = 0; t <= maxTime; ++t) {
        if (t < 10) {
            std::cout << " " << t << " ";
        } else {
            std::cout << t << " ";
        }
    }
    std::cout << std::endl;
}

void Scheduler::printStatistics() const {
    std::cout << "\n=== PERFORMANCE METRICS ===" << std::endl;
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Average Waiting Time: " << calculateAverageWaitingTime() << std::endl;
    std::cout << "Average Turnaround Time: " << calculateAverageTurnaroundTime() << std::endl;
    std::cout << "Average Response Time: " << calculateAverageResponseTime() << std::endl;
    std::cout << "Average CPU Utilization: " << calculateAverageCPUUtilization() << "%" << std::endl;
    std::cout << "Throughput: " << calculateThroughput() << " processes/unit time" << std::endl;
    std::cout << "Total Execution Time: " << currentTime << " units" << std::endl;
}

double Scheduler::calculateAverageWaitingTime() const {
    if (processes.empty()) return 0.0;
    
    double total = 0.0;
    for (const auto& process : processes) {
        total += process->getWaitingTime();
    }
    return total / processes.size();
}

double Scheduler::calculateAverageTurnaroundTime() const {
    if (processes.empty()) return 0.0;
    
    double total = 0.0;
    for (const auto& process : processes) {
        total += process->getTurnaroundTime();
    }
    return total / processes.size();
}

double Scheduler::calculateAverageResponseTime() const {
    if (processes.empty()) return 0.0;
    
    double total = 0.0;
    for (const auto& process : processes) {
        total += process->getResponseTime();
    }
    return total / processes.size();
}

double Scheduler::calculateAverageCPUUtilization() const {
    if (cpus.empty()) return 0.0;
    
    double totalUtilization = 0.0;
    for (const auto& cpu : cpus) {
        totalUtilization += cpu->getUtilization();
    }
    return totalUtilization / cpus.size();
}

double Scheduler::calculateThroughput() const {
    return currentTime > 0 ? (double)processes.size() / currentTime : 0.0;
}