#ifndef CPU_H
#define CPU_H

#include "../Process.h"
#include <memory>

class CPU {
private:
    int cpuID;
    std::shared_ptr<Process> currentProcess;
    bool isIdle;
    int totalIdleTime;
    int totalBusyTime;
    int currentTimeSlice;

public:
    CPU(int id);
    ~CPU() = default;
    
    // Process management
    void assignProcess(std::shared_ptr<Process> process);
    void releaseProcess();
    std::shared_ptr<Process> getCurrentProcess() const { return currentProcess; }
    
    // State management
    bool getIsIdle() const { return isIdle; }
    void tick(int currentTime);
    int getCurrentTimeSlice() const { return currentTimeSlice; }
    void resetTimeSlice() { currentTimeSlice = 0; }
    
    // Statistics
    double getUtilization() const;
    int getIdleTime() const { return totalIdleTime; }
    int getBusyTime() const { return totalBusyTime; }
    int getTotalTime() const { return totalIdleTime + totalBusyTime; }
    
    // Utility
    void reset();
    int getCpuID() const { return cpuID; }
    void displayStatus() const;
};

#endif // CPU_H