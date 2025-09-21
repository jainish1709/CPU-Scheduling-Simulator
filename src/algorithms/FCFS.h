#ifndef FCFS_H
#define FCFS_H

#include "../Scheduler.h"

class FCFS : public Scheduler {
public:
    FCFS(int numCPUs = 1);
    
    void schedule() override;
    std::shared_ptr<Process> selectNextProcess() override;
};

#endif // FCFS_H