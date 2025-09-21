# CPU Scheduling Simulator

A comprehensive CPU scheduling simulator implemented in C++ that demonstrates various process scheduling algorithms with multi-core support.

## 🚀 Features

- **Multiple Scheduling Algorithms:**
  - First Come First Served (FCFS)
  - Shortest Job First (SJF)
  - Shortest Remaining Time First (SRTF)
  - Round Robin (RR)
  - Priority Scheduling (Preemptive & Non-preemptive)

- **Multi-Core Support:** Simulate scheduling on multiple CPU cores
- **Interactive Menu System:** Easy-to-use command-line interface
- **VS Code Integration:** Pre-configured build tasks for seamless development
- **Comprehensive Statistics:** Detailed performance metrics and comparisons
- **Gantt Chart Visualization:** Visual representation of process execution
- **Test Case Generator:** Built-in random process generation
- **File I/O Support:** Save and load process configurations

## 📋 Requirements

- **Compiler:** GCC with C++17 support
- **IDE:** Visual Studio Code (recommended) with C/C++ extension
- **Operating System:** Windows, Linux, or macOS
- **Memory:** Minimal requirements

### VS Code Extensions (Recommended)
- C/C++ Extension Pack by Microsoft
- Code Runner (optional, for quick testing)

## 🛠️ Installation & Build

### Method 1: VS Code (Recommended)

1. **Clone the repository:**
   ```bash
   git clone https://github.com/yourusername/CPU-Scheduling-Simulator.git
   cd CPU-Scheduling-Simulator
   ```

2. **Open in VS Code:**
   ```bash
   code .
   ```

3. **Build using VS Code Tasks:**
   - Press `Ctrl+Shift+P` (Windows/Linux) or `Cmd+Shift+P` (macOS)
   - Type "Tasks: Run Task"
   - Select "Build CPU Scheduler"
   
   **OR**
   
   - Press `Ctrl+Shift+B` (Windows/Linux) or `Cmd+Shift+B` (macOS)
   - This will run the default build task

   The project includes a configured `tasks.json` file that handles the compilation automatically.

### Method 2: Command Line

#### Windows (Batch File)
```bash
build.bat
```

#### Manual Build (All Platforms)
```bash
# Windows
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

# Linux/macOS
g++ -std=c++17 -Wall -Wextra -O2 \
    src/main.cpp \
    src/Process.cpp \
    src/Scheduler.cpp \
    src/algorithms/FCFS.cpp \
    src/algorithms/SJF.cpp \
    src/algorithms/RoundRobin.cpp \
    src/algorithms/Priority.cpp \
    src/core/CPU.cpp \
    src/core/Statistics.cpp \
    src/visualization/GanttChart.cpp \
    src/utils/InputGenerator.cpp \
    -o scheduler
```

## 🎮 Usage

Run the compiled executable:
```bash
./scheduler.exe    # Windows
./scheduler        # Linux/macOS
```

### Main Menu Options

1. **Run Single Algorithm** - Execute one scheduling algorithm
2. **Compare All Algorithms** - Compare performance of all algorithms
3. **Test Multi-Core Scheduling** - Test with different CPU counts
4. **Generate Random Test Case** - Create random process sets
5. **Load Processes from File** - Load predefined process configurations
6. **Exit** - Close the simulator

### Available Test Cases

- **Classic Test Case** - Standard process set for general testing
- **Round Robin Test Case** - Optimized for time-slice demonstration
- **Priority Test Case** - Processes with varying priorities
- **Multi-Core Test Case** - Designed for multi-CPU testing
- **Convoy Effect Case** - Demonstrates convoy effect in FCFS

## 📊 Performance Metrics

The simulator calculates and displays:

- **Average Waiting Time** - Time processes wait in ready queue
- **Average Turnaround Time** - Total time from arrival to completion
- **Average Response Time** - Time from arrival to first execution
- **CPU Utilization** - Percentage of time CPUs are busy
- **Throughput** - Number of processes completed per time unit

## 🏗️ Project Structure

```
CPUSchedulingSimulator/
├── .vscode/
│   └── tasks.json               # VS Code build configuration
├── src/
│   ├── main.cpp                 # Main program entry point
│   ├── Process.cpp/.h           # Process class implementation
│   ├── Scheduler.cpp/.h         # Base scheduler class
│   ├── algorithms/              # Scheduling algorithms
│   │   ├── FCFS.cpp/.h
│   │   ├── SJF.cpp/.h
│   │   ├── RoundRobin.cpp/.h
│   │   └── Priority.cpp/.h
│   ├── core/                    # Core components
│   │   ├── CPU.cpp/.h           # CPU simulation
│   │   └── Statistics.cpp/.h    # Performance metrics
│   ├── utils/                   # Utility classes
│   │   └── InputGenerator.cpp/.h
│   └── visualization/           # Output formatting
│       └── GanttChart.cpp/.h
├── build.bat                    # Windows build script (alternative)
├── .gitignore
├── LICENSE
└── README.md
```

## 🔧 Algorithms Implemented

### 1. First Come First Served (FCFS)
- **Type:** Non-preemptive
- **Description:** Processes are executed in order of arrival
- **Pros:** Simple implementation, fair ordering
- **Cons:** Can cause convoy effect with long processes

### 2. Shortest Job First (SJF)
- **Type:** Non-preemptive
- **Description:** Selects process with shortest burst time
- **Pros:** Minimizes average waiting time
- **Cons:** Can cause starvation of longer processes

### 3. Shortest Remaining Time First (SRTF)
- **Type:** Preemptive
- **Description:** Preemptive version of SJF
- **Pros:** Better response time than SJF
- **Cons:** More context switches, complexity

### 4. Round Robin (RR)
- **Type:** Preemptive
- **Description:** Each process gets equal time slice
- **Pros:** Fair CPU sharing, good response time
- **Cons:** Performance depends on time quantum choice

### 5. Priority Scheduling
- **Type:** Preemptive & Non-preemptive
- **Description:** Processes scheduled based on priority
- **Pros:** Important processes get preference
- **Cons:** Can cause starvation of low-priority processes

## 📈 Example Output

```
=== ALGORITHM COMPARISON ===
Algorithm                 Avg Wait Time    Avg Turnaround Time    Avg Response Time    CPU Utilization
FCFS                      6.40             13.20                  6.40                 85.71%
SJF                       3.20             10.00                  3.20                 85.71%
SRTF                      2.60             9.40                   2.20                 85.71%
Round Robin               5.00             11.80                  2.20                 85.71%
Priority (Non-preemptive) 4.40             11.20                  4.40                 85.71%
Priority (Preemptive)     3.40             10.20                  2.60                 85.71%
```

## 🤝 Contributing

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/new-algorithm`)
3. Commit your changes (`git commit -am 'Add new scheduling algorithm'`)
4. Push to the branch (`git push origin feature/new-algorithm`)
5. Create a Pull Request

## 📝 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🙏 Acknowledgments

- Operating Systems course materials and textbooks
- CPU scheduling algorithm research papers
- C++ programming community

## 📞 Contact

- **Author:** [Your Name]
- **Email:** [your.email@example.com]
- **GitHub:** [@yourusername]

---

**Note:** This simulator is designed for educational purposes to understand CPU scheduling algorithms and their performance characteristics.
