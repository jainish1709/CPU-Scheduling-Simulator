#ifndef SJF_H
#define SJF_H

#include "../Scheduler.h"
#include <queue>

class SJF : public Scheduler {
private:
    struct SJFComparator {
        bool operator()(const std::shared_ptr<Process>& a, 
                       const std::shared_ptr<Process>& b) const {
            if (a->getRemainingTime() == b->getRemainingTime()) {
                if (a->getArrivalTime() == b->getArrivalTime()) {
                    return a->getProcessID() > b->getProcessID();
                }
                return a->getArrivalTime() > b->getArrivalTime();
            }
            return a->getRemainingTime() > b->getRemainingTime();
        }
    };
    
    std::priority_queue<std::shared_ptr<Process>, 
                       std::vector<std::shared_ptr<Process>>, 
                       SJFComparator> sjfQueue;

public:
    SJF(int numCPUs = 1, bool preempt = false);
    
    void schedule() override;
    std::shared_ptr<Process> selectNextProcess() override;
    void onProcessArrival(std::shared_ptr<Process> process) override;
    void preempt(int cpuID) override;

private:
    void updateSJFQueue();
};

#endif // SJF_H