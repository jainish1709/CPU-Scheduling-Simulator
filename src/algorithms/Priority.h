#ifndef PRIORITY_H
#define PRIORITY_H

#include "../Scheduler.h"
#include <queue>

class Priority : public Scheduler {
private:
    struct PriorityComparator {
        bool operator()(const std::shared_ptr<Process>& a, 
                       const std::shared_ptr<Process>& b) const {
            if (a->getPriority() == b->getPriority()) {
                if (a->getArrivalTime() == b->getArrivalTime()) {
                    return a->getProcessID() > b->getProcessID();
                }
                return a->getArrivalTime() > b->getArrivalTime();
            }
            return a->getPriority() > b->getPriority();
        }
    };
    
    std::priority_queue<std::shared_ptr<Process>, 
                       std::vector<std::shared_ptr<Process>>, 
                       PriorityComparator> priorityQueue;

public:
    Priority(int numCPUs = 1, bool preempt = false);
    
    void schedule() override;
    std::shared_ptr<Process> selectNextProcess() override;
    void onProcessArrival(std::shared_ptr<Process> process) override;
    void preempt(int cpuID) override;

private:
    void updatePriorityQueue();
};

#endif // PRIORITY_H