#include "InputGenerator.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include <chrono>
#include <iomanip>

std::vector<std::shared_ptr<Process>> InputGenerator::generateRandomProcesses(
    int count, int maxArrival, int maxBurst, int maxPriority) {
    
    std::vector<std::shared_ptr<Process>> processes;
    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> arrivalDist(0, maxArrival);
    std::uniform_int_distribution<int> burstDist(1, maxBurst);
    std::uniform_int_distribution<int> priorityDist(0, maxPriority);
    
    for (int i = 0; i < count; ++i) {
        auto process = std::make_shared<Process>(
            i + 1,
            arrivalDist(rng),
            burstDist(rng),
            priorityDist(rng),
            "P" + std::to_string(i + 1)
        );
        processes.push_back(process);
    }
    
    return processes;
}

std::vector<std::shared_ptr<Process>> InputGenerator::getClassicTestCase() {
    std::vector<std::shared_ptr<Process>> processes;
    
    processes.push_back(std::make_shared<Process>(1, 0, 8, 3, "P1"));
    processes.push_back(std::make_shared<Process>(2, 1, 4, 1, "P2"));
    processes.push_back(std::make_shared<Process>(3, 2, 9, 4, "P3"));
    processes.push_back(std::make_shared<Process>(4, 3, 5, 2, "P4"));
    processes.push_back(std::make_shared<Process>(5, 4, 2, 5, "P5"));
    
    return processes;
}

std::vector<std::shared_ptr<Process>> InputGenerator::getRoundRobinTestCase() {
    std::vector<std::shared_ptr<Process>> processes;
    
    processes.push_back(std::make_shared<Process>(1, 0, 10, 0, "P1"));
    processes.push_back(std::make_shared<Process>(2, 1, 1, 0, "P2"));
    processes.push_back(std::make_shared<Process>(3, 2, 2, 0, "P3"));
    processes.push_back(std::make_shared<Process>(4, 3, 1, 0, "P4"));
    processes.push_back(std::make_shared<Process>(5, 4, 5, 0, "P5"));
    
    return processes;
}

std::vector<std::shared_ptr<Process>> InputGenerator::getPriorityTestCase() {
    std::vector<std::shared_ptr<Process>> processes;
    
    processes.push_back(std::make_shared<Process>(1, 0, 4, 2, "P1"));
    processes.push_back(std::make_shared<Process>(2, 1, 3, 1, "P2"));
    processes.push_back(std::make_shared<Process>(3, 2, 1, 4, "P3"));
    processes.push_back(std::make_shared<Process>(4, 3, 5, 2, "P4"));
    processes.push_back(std::make_shared<Process>(5, 4, 2, 1, "P5"));
    
    return processes;
}

std::vector<std::shared_ptr<Process>> InputGenerator::getMultiCoreTestCase() {
    std::vector<std::shared_ptr<Process>> processes;
    
    for (int i = 0; i < 8; ++i) {
        processes.push_back(std::make_shared<Process>(
            i + 1, 
            i / 2,
            (i % 4) + 3,
            i % 3,
            "P" + std::to_string(i + 1)
        ));
    }
    
    return processes;
}

std::vector<std::shared_ptr<Process>> InputGenerator::getConvoyEffectCase() {
    std::vector<std::shared_ptr<Process>> processes;
    
    processes.push_back(std::make_shared<Process>(1, 0, 15, 0, "LongP1"));
    processes.push_back(std::make_shared<Process>(2, 1, 2, 0, "ShortP2"));
    processes.push_back(std::make_shared<Process>(3, 2, 3, 0, "ShortP3"));
    processes.push_back(std::make_shared<Process>(4, 3, 2, 0, "ShortP4"));
    
    return processes;
}

void InputGenerator::saveToFile(const std::vector<std::shared_ptr<Process>>& processes,
                               const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }
    
    file << "# ProcessID ArrivalTime BurstTime Priority ProcessName" << std::endl;
    for (const auto& process : processes) {
        file << process->getProcessID() << " "
             << process->getArrivalTime() << " "
             << process->getBurstTime() << " "
             << process->getPriority() << " "
             << process->getProcessName() << std::endl;
    }
    
    file.close();
    std::cout << "Saved " << processes.size() << " processes to " << filename << std::endl;
}

std::vector<std::shared_ptr<Process>> InputGenerator::loadFromFile(const std::string& filename) {
    std::vector<std::shared_ptr<Process>> processes;
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return processes;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        
        std::istringstream iss(line);
        int id, arrival, burst, priority;
        std::string name;
        
        if (iss >> id >> arrival >> burst >> priority >> name) {
            processes.push_back(std::make_shared<Process>(id, arrival, burst, priority, name));
        }
    }
    
    file.close();
    std::cout << "Loaded " << processes.size() << " processes from " << filename << std::endl;
    return processes;
}

void InputGenerator::printProcessList(const std::vector<std::shared_ptr<Process>>& processes) {
    std::cout << "\nProcess List:" << std::endl;
    Process::printHeader();
    for (const auto& process : processes) {
        std::cout << std::setw(8) << process->getProcessName()
                  << std::setw(10) << process->getArrivalTime()
                  << std::setw(10) << process->getBurstTime()
                  << std::setw(10) << process->getPriority()
                  << std::setw(12) << "-"
                  << std::setw(12) << "-"
                  << std::setw(12) << "-"
                  << std::setw(12) << "-" << std::endl;
    }
}