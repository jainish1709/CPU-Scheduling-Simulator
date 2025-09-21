#include "GanttChart.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>

void GanttChart::printAdvancedGanttChart(const std::vector<std::shared_ptr<Process>>& processes,
                                        int numCPUs) {
    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "ADVANCED GANTT CHART" << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    
    int maxTime = 0;
    for (const auto& process : processes) {
        maxTime = std::max(maxTime, process->getCompletionTime());
    }
    
    printTimelineHeader(maxTime);
    
    for (const auto& process : processes) {
        printProcessTimeline(process, maxTime);
    }
    
    std::cout << std::string(maxTime * 3 + 10, '-') << std::endl;
}

void GanttChart::printTimelineHeader(int maxTime) {
    std::cout << std::setw(8) << "Time:";
    for (int t = 0; t <= maxTime; ++t) {
        std::cout << std::setw(3) << t;
    }
    std::cout << std::endl;
    
    std::cout << std::setw(8) << "";
    for (int t = 0; t <= maxTime; ++t) {
        std::cout << std::setw(3) << "|";
    }
    std::cout << std::endl;
}

void GanttChart::printProcessTimeline(const std::shared_ptr<Process>& process, int maxTime) {
    std::cout << std::setw(8) << process->getProcessName() << "";
    
    std::vector<bool> timeline(maxTime + 1, false);
    
    for (const auto& execution : process->getExecutionHistory()) {
        int startTime = execution.first;
        int duration = execution.second;
        
        for (int t = startTime; t < startTime + duration && t <= maxTime; ++t) {
            timeline[t] = true;
        }
    }
    
    for (int t = 0; t <= maxTime; ++t) {
        if (timeline[t]) {
            std::cout << std::setw(3) << "█";
        } else if (t >= process->getArrivalTime() && t < process->getCompletionTime()) {
            std::cout << std::setw(3) << "░";  // Waiting
        } else {
            std::cout << std::setw(3) << " ";
        }
    }
    std::cout << std::endl;
}

void GanttChart::saveGanttChartToFile(const std::vector<std::shared_ptr<Process>>& processes,
                                     int numCPUs, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }
    
    int maxTime = 0;
    for (const auto& process : processes) {
        maxTime = std::max(maxTime, process->getCompletionTime());
    }
    
    file << "Gantt Chart Data" << std::endl;
    file << "Process,ExecutionIntervals" << std::endl;
    
    for (const auto& process : processes) {
        file << process->getProcessName() << ",";
        for (const auto& execution : process->getExecutionHistory()) {
            file << "[" << execution.first << "-" << (execution.first + execution.second) << "]";
        }
        file << std::endl;
    }
    
    file.close();
    std::cout << "Gantt chart saved to " << filename << std::endl;
}