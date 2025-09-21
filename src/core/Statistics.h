#ifndef STATISTICS_H
#define STATISTICS_H

#include "../Scheduler.h"
#include <vector>
#include <string>

class Statistics {
public:
    static void compareAlgorithms(
        const std::vector<std::unique_ptr<Scheduler>>& schedulers,
        const std::vector<std::shared_ptr<Process>>& testProcesses);
    
    static void printComparisonTable(
        const std::vector<std::string>& algorithmNames,
        const std::vector<double>& avgWaitingTimes,
        const std::vector<double>& avgTurnaroundTimes,
        const std::vector<double>& avgResponseTimes,
        const std::vector<double>& cpuUtilizations);
        
    static void saveResultsToFile(const std::string& filename,
                                 const std::string& algorithmName,
                                 const std::vector<std::shared_ptr<Process>>& processes);
};

#endif // STATISTICS_H