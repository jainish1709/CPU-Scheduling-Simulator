#ifndef INPUTGENERATOR_H
#define INPUTGENERATOR_H

#include "../Process.h"
#include <vector>
#include <memory>
#include <string>

class InputGenerator {
public:
    static std::vector<std::shared_ptr<Process>> generateRandomProcesses(
        int count, int maxArrival, int maxBurst, int maxPriority = 5);
    
    static std::vector<std::shared_ptr<Process>> getClassicTestCase();
    static std::vector<std::shared_ptr<Process>> getRoundRobinTestCase();
    static std::vector<std::shared_ptr<Process>> getPriorityTestCase();
    static std::vector<std::shared_ptr<Process>> getMultiCoreTestCase();
    static std::vector<std::shared_ptr<Process>> getConvoyEffectCase();
    
    static void saveToFile(const std::vector<std::shared_ptr<Process>>& processes,
                          const std::string& filename);
    static std::vector<std::shared_ptr<Process>> loadFromFile(const std::string& filename);
    
    static void printProcessList(const std::vector<std::shared_ptr<Process>>& processes);
};

#endif // INPUTGENERATOR_H