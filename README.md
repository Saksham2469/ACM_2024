# CPU Scheduling Simulator

## Table of Contents
1. [Project Overview](#1-project-overview)
2. [How to Run](#2-how-to-run)
3. [Internal Working](#3-internal-working)
4. [Algorithms Implemented](#4-algorithms-implemented)
   - [FCFS (First Come First Serve)](#41-fcfs-first-come-first-serve)
   - [SJF (Shortest Job First)](#42-sjf-shortest-job-first)
   - [Round Robin](#43-round-robin)
   - [Priority Scheduling](#44-priority-scheduling)
5. [GUI Interface](#5-gui-interface)
6. [Error Handling](#6-error-handling)
7. [Learning Takeaways](#7-learning-takeaways)
8. [Resources and References](#8-resources-and-references)

---

## 1. Project Overview
The CPU Scheduling Simulator project is designed to simulate and analyze the performance of various CPU scheduling algorithms. These algorithms are fundamental in operating systems for managing process execution. The project includes implementations of FCFS, SJF, Round Robin, and Priority (both preemptive and non-preemptive) scheduling.

## 2. How to Run
### Dependencies
- Python (3.6 or higher)
- tkinter (standard library for GUI)
- C++ compiler (supporting C++17 standard)
- GNU Make (optional, for compilation automation)

### Steps to Run
1. **Compile the C++ Program:**
   - Ensure you have a C++ compiler installed (e.g., g++).
   - Navigate to the directory containing `acm.cpp`.
   - Compile the C++ program:
     ```bash
     g++ -std=c++17 -o acm.exe acm.cpp
     ```
   - This will generate an executable `acm.exe`.

2. **Run the Python Interface:**
   - Execute the Python script `py`:
     ```bash
     python py
     ```
   - This will launch the GUI interface.
   - Make sure that directory path of the cpp , compiled cpp and py files is the same.

3. **Input Data:**
   - Enter the number of tasks and details (burst time, arrival time, priority) using the GUI.

4. **Run Simulation:**
   - Click on "Run Program" in the GUI to execute the simulation with selected parameters.

---

## 3. Internal Working
The CPU scheduling algorithms are implemented in C++:
- **Task Struct:** Defines a task with attributes (ID, Burst Time, Arrival Time, Priority).
- **Scheduling Algorithms:** Each algorithm is implemented using sorting and iterative calculations to determine average turnaround time and waiting time.

The Python interface (tkinter-based GUI) facilitates user input and displays simulation results. It interacts with the compiled C++ executable to perform computations based on user-provided data.

---

## 4. Algorithms Implemented

### 4.1 FCFS (First Come First Serve)
#### Description
FCFS is the simplest scheduling algorithm, where processes are executed in the order they arrive in the ready queue.

#### Implementation Details
1. **Sorting:** Tasks are sorted based on their arrival time.
2. **Execution:** Tasks are executed sequentially, calculating turnaround and waiting times.

#### Example Scenario
- **Tasks:** T1, T2, T3
- **Arrival Times:** T1(0), T2(1), T3(2)
- **Burst Times:** T1(5), T2(3), T3(4)
- **Execution Order:** T1, T2, T3

### 4.2 SJF (Shortest Job First)
#### Description
SJF executes the shortest burst time task first to minimize average waiting time.

#### Implementation Details
1. **Sorting:** Tasks are sorted based on their burst time.
2. **Execution:** Tasks are executed sequentially, calculating turnaround and waiting times.

#### Example Scenario
- **Tasks:** T1, T2, T3
- **Burst Times:** T1(3), T2(2), T3(4)
- **Execution Order:** T2, T1, T3

### 4.3 Round Robin
#### Description
Round Robin allocates CPU time to each task for a fixed time quantum, cycling through tasks in a circular queue.

#### Implementation Details
1. **Time Quantum:** A fixed time slice is allocated to each task.
2. **Execution:** Tasks are executed in a round-robin fashion until all are completed or until the time quantum expires.

#### Example Scenario
- **Tasks:** T1, T2, T3
- **Burst Times:** T1(5), T2(3), T3(4)
- **Time Quantum:** 2 units
- **Execution Order:** T1, T2, T3, T1, T3, T1, ...

### 4.4 Priority Scheduling
#### Description
Priority Scheduling executes tasks based on their priority, with higher priority tasks preempting lower priority ones (in preemptive mode).

#### Implementation Details
1. **Sorting:** Tasks are sorted based on their priority (and arrival time in non-preemptive).
2. **Execution:** Tasks are executed based on their priority order, calculating turnaround and waiting times.

#### Example Scenario
- **Tasks:** T1, T2, T3
- **Priorities:** T1(2), T2(1), T3(3)
- **Execution Order:** T3, T1, T2 (Preemptive)
   - T3 arrives first, executes.
   - T1 arrives, preempts T3 due to higher priority.
   - T2 arrives, preempts T1 due to higher priority.

---

## 5. GUI Interface
The GUI interface is developed using Python's tkinter library:
- **Input Fields:** Number of tasks, burst time, arrival time, priority.
- **Buttons:** Proceed to input data, run simulation.
- **Output:** Display of results including average turnaround time and waiting time.

---

## 6. Error Handling
The project includes robust error handling for user inputs:
- Validation checks for numerical inputs.
- Error messages for invalid inputs.

---

## 7. Learning Takeaways
- **Understanding CPU Scheduling:** Gain insights into scheduling algorithms used in operating systems.
- **Integration of C++ and Python:** Learn to integrate backend C++ computations with a frontend Python GUI.
- **Error Handling:** Implement effective error handling strategies in GUI applications.

---

## 8. Resources and References
- Operating System Concepts by Abraham Silberschatz, Peter B. Galvin, Greg Gagne.
- Online resources and tutorials on CPU scheduling algorithms.
- Documentation for Python tkinter library and C++ programming.

