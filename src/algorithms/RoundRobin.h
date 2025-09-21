#ifndef ROUNDROBIN_H
#define ROUNDROBIN_H

#include "../Scheduler.h"

class RoundRobin : public Scheduler {
public:
    RoundRobin(int quantum, int numCPUs = 1);
    
    void schedule() override;
    std::shared_ptr<Process> selectNextProcess() override;
    void preempt(int cpuID) override;
};

#endif // ROUNDROBIN_H