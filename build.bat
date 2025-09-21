@echo off
echo Building CPU Scheduling Simulator...

g++ -std=c++17 -Wall -Wextra -O2 ^
    src/main.cpp ^
    src/Process.cpp ^
    src/Scheduler.cpp ^
    src/algorithms/FCFS.cpp ^
    src/algorithms/SJF.cpp ^
    src/algorithms/RoundRobin.cpp ^
    src/algorithms/Priority.cpp ^
    src/core/CPU.cpp ^
    src/core/Statistics.cpp ^
    src/visualization/GanttChart.cpp ^
    src/utils/InputGenerator.cpp ^
    -o scheduler.exe

if %errorlevel% equ 0 (
    echo Build successful! Running program...
    echo.
    scheduler.exe
) else (
    echo Build failed!
    pause
)