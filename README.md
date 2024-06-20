# CPU Scheduling Simulator

## Table of Contents
1. [Project Overview](#project-overview)
2. [How to Run](#how-to-run)
3. [Internal Working](#internal-working)
4. [Algorithms Implemented](#algorithms-implemented)
5. [GUI Interface](#gui-interface)
6. [Error Handling](#error-handling)
7. [Learning Takeaways](#learning-takeaways)
8. [Resources and References](#resources-and-references)

## 1. Project Overview
The CPU Scheduling Simulator project aims to simulate and analyze the performance of various CPU scheduling algorithms. These algorithms are fundamental in operating systems for managing process execution. The project includes implementations of FCFS (First Come First Serve), SJF (Shortest Job First), Round Robin, and Priority (both preemptive and non-preemptive) scheduling.

## 2. How to Run
### Dependencies
- Python (3.6 or higher)
- tkinter (standard library for GUI)
- C++ compiler (supporting C++17 standard)
- GNU Make (optional, for compilation automation)

### Steps to Run
1. **Compile the C++ Program:**
   - Ensure you have a C++ compiler installed (e.g., g++).
   - Navigate to the directory containing `cpu_scheduling.cpp`.
   - Compile the C++ program:
     ```bash
     g++ -std=c++17 -o acm.exe cpu_scheduling.cpp
     ```
   - This will generate an executable `acm.exe`.

2. **Run the Python Interface:**
   - Execute the Python script `py`:
     ```bash
     python py
     ```
   - This will launch the GUI interface.

3. **Input Data:**
   - Enter the number of tasks and details (burst time, arrival time, priority) using the GUI.

4. **Run Simulation:**
   - Click on "Run Program" in the GUI to execute the simulation with selected parameters.

## 3. Internal Working
The CPU scheduling algorithms are implemented in C++:
- **Task Struct:** Defines a task with attributes (ID, Burst Time, Arrival Time, Priority).
- **Scheduling Algorithms:** FCFS, SJF, Round Robin, Priority (preemptive and non-preemptive) are implemented using sorting and iterative calculations to determine average turnaround time and waiting time.

The Python interface (tkinter-based GUI) facilitates user input and displays simulation results. It interacts with the compiled C++ executable to perform computations based on user-provided data.

## 4. Algorithms Implemented
### FCFS (First Come First Serve)
- Description of FCFS algorithm.
- Implementation details.
- Example scenarios.

### SJF (Shortest Job First)
- Description of SJF algorithm.
- Implementation details.
- Example scenarios.

### Round Robin
- Description of Round Robin algorithm.
- Implementation details.
- Example scenarios.

### Priority Scheduling
- Description of Priority Scheduling algorithm (preemptive and non-preemptive).
- Implementation details.
- Example scenarios.

## 5. GUI Interface
The GUI interface is developed using Python's tkinter library:
- **Input Fields:** Number of tasks, burst time, arrival time, priority.
- **Buttons:** Proceed to input data, run simulation.
- **Output:** Display of results including average turnaround time and waiting time.

### Screenshots/Diagrams
Include screenshots or diagrams of the GUI interface to illustrate its functionality and layout.

## 6. Error Handling
The project includes robust error handling for user inputs:
- Validation checks for numerical inputs.
- Error messages for invalid inputs.

## 7. Learning Takeaways
- **Understanding CPU Scheduling:** Gain insights into scheduling algorithms used in operating systems.
- **Integration of C++ and Python:** Learn to integrate backend C++ computations with a frontend Python GUI.
- **Error Handling:** Implement effective error handling strategies in GUI applications.

## 8. Resources and References
- Operating System Concepts by Abraham Silberschatz, Peter B. Galvin, Greg Gagne.
- Online resources and tutorials on CPU scheduling algorithms.
- Documentation for Python tkinter library and C++ programming.

---

Feel free to expand each section with more detailed explanations, examples, or additional subsections to provide a comprehensive overview of your CPU Scheduling Simulator project.
