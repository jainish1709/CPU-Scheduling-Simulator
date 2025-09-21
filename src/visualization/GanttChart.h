#ifndef GANTTCHART_H
#define GANTTCHART_H

#include "../Process.h"
#include <vector>
#include <memory>
#include <string>

class GanttChart {
public:
    static void printAdvancedGanttChart(const std::vector<std::shared_ptr<Process>>& processes,
                                       int numCPUs);
    
    static void saveGanttChartToFile(const std::vector<std::shared_ptr<Process>>& processes,
                                    int numCPUs, const std::string& filename);
    
    static void printTimelineHeader(int maxTime);
    static void printProcessTimeline(const std::shared_ptr<Process>& process, int maxTime);
};

#endif // GANTTCHART_H