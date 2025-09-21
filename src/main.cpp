#include "algorithms/FCFS.h"
#include "algorithms/SJF.h"
#include "algorithms/RoundRobin.h"
#include "algorithms/Priority.h"
#include "utils/InputGenerator.h"
#include "core/Statistics.h"
#include "visualization/GanttChart.h"
#include <iostream>
#include <memory>
#include <vector>
#include <string>

void printMainMenu() {
    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << "CPU SCHEDULING SIMULATOR" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
    std::cout << "1. Run Single Algorithm" << std::endl;
    std::cout << "2. Compare All Algorithms" << std::endl;
    std::cout << "3. Test Multi-Core Scheduling" << std::endl;
    std::cout << "4. Generate Random Test Case" << std::endl;
    std::cout << "5. Load Processes from File" << std::endl;
    std::cout << "6. Exit" << std::endl;
    std::cout << "Choice: ";
}

void printAlgorithmMenu() {
    std::cout << "\nSelect Algorithm:" << std::endl;
    std::cout << "1. FCFS (First Come First Served)" << std::endl;
    std::cout << "2. SJF (Shortest Job First)" << std::endl;
    std::cout << "3. SRTF (Shortest Remaining Time First)" << std::endl;
    std::cout << "4. Round Robin" << std::endl;
    std::cout << "5. Priority (Non-preemptive)" << std::endl;
    std::cout << "6. Priority (Preemptive)" << std::endl;
    std::cout << "Choice: ";
}

void printTestCaseMenu() {
    std::cout << "\nSelect Test Case:" << std::endl;
    std::cout << "1. Classic Test Case" << std::endl;
    std::cout << "2. Round Robin Test Case" << std::endl;
    std::cout << "3. Priority Test Case" << std::endl;
    std::cout << "4. Multi-Core Test Case" << std::endl;
    std::cout << "5. Convoy Effect Case" << std::endl;
    std::cout << "6. Random Processes" << std::endl;
    std::cout << "Choice: ";
}

std::vector<std::shared_ptr<Process>> getTestCase() {
    printTestCaseMenu();
    int choice;
    std::cin >> choice;
    
    switch (choice) {
        case 1: return InputGenerator::getClassicTestCase();
        case 2: return InputGenerator::getRoundRobinTestCase();
        case 3: return InputGenerator::getPriorityTestCase();
        case 4: return InputGenerator::getMultiCoreTestCase();
        case 5: return InputGenerator::getConvoyEffectCase();
        case 6: {
            int count, maxArrival, maxBurst, maxPriority;
            std::cout << "Number of processes: ";
            std::cin >> count;
            std::cout << "Max arrival time: ";
            std::cin >> maxArrival;
            std::cout << "Max burst time: ";
            std::cin >> maxBurst;
            std::cout << "Max priority: ";
            std::cin >> maxPriority;
            return InputGenerator::generateRandomProcesses(count, maxArrival, maxBurst, maxPriority);
        }
        default:
            return InputGenerator::getClassicTestCase();
    }
}

std::unique_ptr<Scheduler> createScheduler(int algorithmChoice, int numCPUs = 1) {
    switch (algorithmChoice) {
        case 1: return std::make_unique<FCFS>(numCPUs);
        case 2: return std::make_unique<SJF>(numCPUs, false);
        case 3: return std::make_unique<SJF>(numCPUs, true);
        case 4: {
            int quantum;
            std::cout << "Enter time quantum: ";
            std::cin >> quantum;
            return std::make_unique<RoundRobin>(quantum, numCPUs);
        }
        case 5: return std::make_unique<Priority>(numCPUs, false);
        case 6: return std::make_unique<Priority>(numCPUs, true);
        default: return std::make_unique<FCFS>(numCPUs);
    }
}

void runSingleAlgorithm() {
    auto processes = getTestCase();
    InputGenerator::printProcessList(processes);
    
    std::cout << "\nNumber of CPUs: ";
    int numCPUs;
    std::cin >> numCPUs;
    
    printAlgorithmMenu();
    int algorithmChoice;
    std::cin >> algorithmChoice;
    
    auto scheduler = createScheduler(algorithmChoice, numCPUs);
    scheduler->addProcesses(processes);
    
    std::cout << "\nEnable verbose output? (1=Yes, 0=No): ";
    int verbose;
    std::cin >> verbose;
    scheduler->setVerbose(verbose == 1);
    
    scheduler->run();
    scheduler->printResults();
    scheduler->printGanttChart();
    
    std::cout << "\nSave results to file? (1=Yes, 0=No): ";
    int save;
    std::cin >> save;
    if (save == 1) {
        std::string filename;
        std::cout << "Enter filename: ";
        std::cin >> filename;
        Statistics::saveResultsToFile(filename, scheduler->getAlgorithmName(), processes);
    }
}

void compareAllAlgorithms() {
    auto processes = getTestCase();
    InputGenerator::printProcessList(processes);
    
    std::cout << "\nNumber of CPUs: ";
    int numCPUs;
    std::cin >> numCPUs;
    
    std::vector<std::unique_ptr<Scheduler>> schedulers;
    std::vector<std::string> names;
    std::vector<double> avgWaitingTimes, avgTurnaroundTimes, avgResponseTimes, cpuUtilizations;
    
    // Create all schedulers
    schedulers.push_back(std::make_unique<FCFS>(numCPUs));
    schedulers.push_back(std::make_unique<SJF>(numCPUs, false));
    schedulers.push_back(std::make_unique<SJF>(numCPUs, true));
    schedulers.push_back(std::make_unique<RoundRobin>(4, numCPUs));  // Quantum = 4
    schedulers.push_back(std::make_unique<Priority>(numCPUs, false));
    schedulers.push_back(std::make_unique<Priority>(numCPUs, true));
    
    // Run each algorithm
    for (auto& scheduler : schedulers) {
        // Reset processes for each algorithm
        for (auto& process : processes) {
            process->reset();
        }
        
        scheduler->addProcesses(processes);
        scheduler->run();
        
        names.push_back(scheduler->getAlgorithmName());
        avgWaitingTimes.push_back(scheduler->calculateAverageWaitingTime());
        avgTurnaroundTimes.push_back(scheduler->calculateAverageTurnaroundTime());
        avgResponseTimes.push_back(scheduler->calculateAverageResponseTime());
        cpuUtilizations.push_back(scheduler->calculateAverageCPUUtilization());
        
        std::cout << "\nCompleted: " << scheduler->getAlgorithmName() << std::endl;
    }
    
    // Print comparison
    Statistics::printComparisonTable(names, avgWaitingTimes, avgTurnaroundTimes, 
                                    avgResponseTimes, cpuUtilizations);
}

void testMultiCoreScheduling() {
    auto processes = InputGenerator::getMultiCoreTestCase();
    InputGenerator::printProcessList(processes);
    
    std::cout << "\nTesting with different CPU counts:" << std::endl;
    
    for (int numCPUs = 1; numCPUs <= 4; ++numCPUs) {
        std::cout << "\n" << std::string(50, '-') << std::endl;
        std::cout << "Testing with " << numCPUs << " CPU(s)" << std::endl;
        std::cout << std::string(50, '-') << std::endl;
        
        // Reset processes
        for (auto& process : processes) {
            process->reset();
        }
        
        auto scheduler = std::make_unique<FCFS>(numCPUs);
        scheduler->addProcesses(processes);
        scheduler->run();
        
        std::cout << "Average Waiting Time: " << scheduler->calculateAverageWaitingTime() << std::endl;
        std::cout << "Average CPU Utilization: " << scheduler->calculateAverageCPUUtilization() << "%" << std::endl;
        std::cout << "Total Execution Time: " << scheduler->getCurrentTime() << std::endl;
    }
}

void generateRandomTestCase() {
    int count, maxArrival, maxBurst, maxPriority;
    
    std::cout << "Number of processes: ";
    std::cin >> count;
    std::cout << "Maximum arrival time: ";
    std::cin >> maxArrival;
    std::cout << "Maximum burst time: ";
    std::cin >> maxBurst;
    std::cout << "Maximum priority: ";
    std::cin >> maxPriority;
    
    auto processes = InputGenerator::generateRandomProcesses(count, maxArrival, maxBurst, maxPriority);
    InputGenerator::printProcessList(processes);
    
    std::cout << "\nSave to file? (1=Yes, 0=No): ";
    int save;
    std::cin >> save;
    if (save == 1) {
        std::string filename;
        std::cout << "Enter filename: ";
        std::cin >> filename;
        InputGenerator::saveToFile(processes, filename);
    }
}

void loadFromFile() {
    std::string filename;
    std::cout << "Enter filename: ";
    std::cin >> filename;
    
    auto processes = InputGenerator::loadFromFile(filename);
    if (processes.empty()) {
        std::cout << "No processes loaded or file not found." << std::endl;
        return;
    }
    
    InputGenerator::printProcessList(processes);
    
    std::cout << "\nRun algorithm on loaded processes? (1=Yes, 0=No): ";
    int run;
    std::cin >> run;
    if (run == 1) {
        std::cout << "\nNumber of CPUs: ";
        int numCPUs;
        std::cin >> numCPUs;
        
        printAlgorithmMenu();
        int algorithmChoice;
        std::cin >> algorithmChoice;
        
        auto scheduler = createScheduler(algorithmChoice, numCPUs);
        scheduler->addProcesses(processes);
        scheduler->run();
        scheduler->printResults();
        scheduler->printGanttChart();
    }
}

int main() {
    std::cout << "CPU Scheduling Simulator - Windows Version" << std::endl;
    std::cout << "Compiled with: " << __VERSION__ << std::endl;
    
    while (true) {
        printMainMenu();
        int choice;
        std::cin >> choice;
        
        try {
            switch (choice) {
                case 1: runSingleAlgorithm(); break;
                case 2: compareAllAlgorithms(); break;
                case 3: testMultiCoreScheduling(); break;
                case 4: generateRandomTestCase(); break;
                case 5: loadFromFile(); break;
                case 6: 
                    std::cout << "Thank you for using CPU Scheduling Simulator!" << std::endl;
                    return 0;
                default:
                    std::cout << "Invalid choice. Please try again." << std::endl;
            }
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
        
        std::cout << "\nPress Enter to continue...";
        std::cin.ignore();
        std::cin.get();
    }
    
    return 0;
}