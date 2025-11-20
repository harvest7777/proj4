# CPU Scheduling Algorithms Implementation
## CECS 326 - Operating Systems - Project 4

### Team Members
- Ryan Tran ( ID: 031190716)
- Phu Quach (ID: 029475548) 


## Overview
This project implements three classic CPU scheduling algorithms: **First-Come, First-Served (FCFS)**, **Priority Scheduling** and **Round Robin (RR)**

## Project Structure (From CPU_scheduler_demo Module Structure)  
```
.
├── CPU.c               # CPU simulation functions
├── cpu.h               # CPU header with QUANTUM definition
├── driver.c            # Main driver program that reads input and calls schedulers
├── list.c              # Linked list implementation
├── list.h              # Linked list header
├── task.h              # Task structure definition
├── schedulers.h        # Scheduler interface
├── schedule_fcfs.c     # FCFS implementation
├── schedule_priority.c # Priority scheduling implementation
├── schedule_rr.c       # Round Robin implementation
├── Makefile           # Build configuration
└── Test Files
    ├── schedule.txt    # Primary test file (8 tasks)
    ├── book.txt        # Secondary test file (5 tasks)
    ├── pri-schedule.txt # Priority test file
    └── rr-schedule.txt  # Round robin test file
```

## Compilation Instructions

### Using Make (Recommended)
```bash
# Clean previous builds
make clean

# Compile all schedulers
make fcfs      # Compile FCFS scheduler
make priority  # Compile Priority scheduler
make rr        # Compile Round Robin scheduler
```

### Manual Compilation
```bash
# FCFS
gcc -Wall -c driver.c
gcc -Wall -c list.c
gcc -Wall -c CPU.c
gcc -Wall -c schedule_fcfs.c
gcc -Wall -o fcfs driver.o schedule_fcfs.o list.o CPU.o

# Priority
gcc -Wall -c schedule_priority.c
gcc -Wall -o priority driver.o schedule_priority.o list.o CPU.o

# Round Robin
gcc -Wall -c schedule_rr.c
gcc -Wall -o rr driver.o schedule_rr.o list.o CPU.o
```

## Running the Schedulers

### Basic Execution
```bash
./fcfs schedule.txt      # Run FCFS with schedule.txt
./priority schedule.txt  # Run Priority scheduling
./rr schedule.txt        # Run Round Robin
```

### Testing with Different Input Files
```bash
./fcfs book.txt          # Test with book.txt
./priority pri-schedule.txt  # Test with priority-specific file
./rr rr-schedule.txt     # Test with round-robin file
```

## Input File Format
Input files should contain tasks in the format:
```
[task_name], [priority], [burst_time]
```

Example (schedule.txt):
```
T1, 4, 20
T2, 3, 25
T3, 3, 25
T4, 5, 15
T5, 5, 20
T6, 1, 10
T7, 3, 30
T8, 10, 25
```

## Output Format
Each scheduler outputs:
1. Task execution details (name, priority, burst)
2. Individual task metrics (wait time, turnaround time, response time for RR)
3. Summary statistics (total task, average wait time, average turnaround time)


