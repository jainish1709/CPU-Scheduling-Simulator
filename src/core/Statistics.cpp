#include "Statistics.h"
#include <iostream>
#include <iomanip>
#include <fstream>

void Statistics::compareAlgorithms(
    const std::vector<std::unique_ptr<Scheduler>>& schedulers,
    const std::vector<std::shared_ptr<Process>>& testProcesses) {
    
    std::vector<std::string> algorithmNames;
    std::vector<double> avgWaitingTimes, avgTurnaroundTimes, avgResponseTimes, cpuUtilizations;
    
    for (const auto& scheduler : schedulers) {
        algorithmNames.push_back(scheduler->getAlgorithmName());
        avgWaitingTimes.push_back(scheduler->calculateAverageWaitingTime());
        avgTurnaroundTimes.push_back(scheduler->calculateAverageTurnaroundTime());
        avgResponseTimes.push_back(scheduler->calculateAverageResponseTime());
        cpuUtilizations.push_back(scheduler->calculateAverageCPUUtilization());
    }
    
    printComparisonTable(algorithmNames, avgWaitingTimes, avgTurnaroundTimes, 
                        avgResponseTimes, cpuUtilizations);
}

void Statistics::printComparisonTable(
    const std::vector<std::string>& algorithmNames,
    const std::vector<double>& avgWaitingTimes,
    const std::vector<double>& avgTurnaroundTimes,
    const std::vector<double>& avgResponseTimes,
    const std::vector<double>& cpuUtilizations) {
    
    std::cout << "\n" << std::string(100, '=') << std::endl;
    std::cout << "ALGORITHM COMPARISON" << std::endl;
    std::cout << std::string(100, '=') << std::endl;
    
    std::cout << std::left << std::setw(25) << "Algorithm"
              << std::setw(15) << "Avg Wait Time"
              << std::setw(20) << "Avg Turnaround Time"
              << std::setw(20) << "Avg Response Time"
              << std::setw(15) << "CPU Utilization" << std::endl;
    std::cout << std::string(100, '-') << std::endl;
    
    for (size_t i = 0; i < algorithmNames.size(); ++i) {
        std::cout << std::left << std::setw(25) << algorithmNames[i]
                  << std::fixed << std::setprecision(2)
                  << std::setw(15) << avgWaitingTimes[i]
                  << std::setw(20) << avgTurnaroundTimes[i]
                  << std::setw(20) << avgResponseTimes[i]
                  << std::setw(15) << cpuUtilizations[i] << "%" << std::endl;
    }
    std::cout << std::string(100, '-') << std::endl;
}

void Statistics::saveResultsToFile(const std::string& filename,
                                  const std::string& algorithmName,
                                  const std::vector<std::shared_ptr<Process>>& processes) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }
    
    file << "Algorithm: " << algorithmName << std::endl;
    file << "Process,Arrival,Burst,Priority,Completion,Turnaround,Waiting,Response" << std::endl;
    
    for (const auto& process : processes) {
        file << process->getProcessName() << ","
             << process->getArrivalTime() << ","
             << process->getBurstTime() << ","
             << process->getPriority() << ","
             << process->getCompletionTime() << ","
             << process->getTurnaroundTime() << ","
             << process->getWaitingTime() << ","
             << process->getResponseTime() << std::endl;
    }
    
    file.close();
    std::cout << "Results saved to " << filename << std::endl;
}