# CPU Scheduling Algorithms Implementation
## CECS 326 - Operating Systems - Project 4

## Overview
This project implements three classic CPU scheduling algorithms:
1. **First-Come, First-Served (FCFS)** - Non-preemptive, processes executed in arrival order
2. **Priority Scheduling** - Non-preemptive, processes executed based on priority
3. **Round Robin (RR)** - Preemptive, time-sharing with 10ms quantum

## Project Structure
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

**Note:** 
- Priority: Lower number = Higher priority (1 is highest, 10 is lowest)
- Burst time: CPU time required in milliseconds

## Algorithm Details

### FCFS (First-Come, First-Served)
- **Type:** Non-preemptive
- **Selection:** Tasks executed in arrival order
- **Pros:** Simple, fair (in FIFO terms), no starvation
- **Cons:** Convoy effect, poor average waiting time

### Priority Scheduling
- **Type:** Non-preemptive
- **Selection:** Highest priority task (lowest number) executes first
- **Pros:** Important tasks execute quickly
- **Cons:** Potential starvation of low-priority tasks

### Round Robin
- **Type:** Preemptive
- **Time Quantum:** 10 milliseconds
- **Selection:** Circular queue, each task gets time slice
- **Pros:** Good response time, fair CPU distribution
- **Cons:** Higher context switch overhead, higher average turnaround time

## Output Format
Each scheduler outputs:
1. Task execution details (name, priority, burst)
2. Individual task metrics (wait time, turnaround time, response time for RR)
3. Summary statistics (average wait time, average turnaround time)

## Performance Metrics

### Definitions
- **Waiting Time:** Time a process spends waiting in ready queue
- **Turnaround Time:** Total time from arrival to completion
- **Response Time:** Time from arrival to first CPU access (RR only)

### Expected Results (schedule.txt)
| Algorithm | Avg Wait Time | Avg Turnaround Time | Avg Response Time |
|-----------|---------------|---------------------|-------------------|
| FCFS      | 73.12 ms     | 94.38 ms           | N/A               |
| Priority  | 73.75 ms     | 95.00 ms           | N/A               |
| Round Robin| 98.12 ms    | 119.38 ms          | 35.0 ms           |

## Implementation Notes

1. **Memory Management:** All dynamically allocated memory is properly freed
2. **List Operations:** Tasks are added at head, FCFS/RR reverse list for proper order
3. **Priority Handling:** Equal priorities maintain FIFO order
4. **Round Robin:** Tracks remaining burst time for each process

## Testing Recommendations

1. **Basic Test:** Run all three schedulers with schedule.txt
2. **Edge Cases:** Test with single task, equal priorities, equal burst times
3. **Performance:** Compare metrics across different workload types
4. **Validation:** Verify Gantt chart timing matches expected behavior

## Known Limitations

- All tasks assumed to arrive at time 0
- No support for dynamic priority adjustment
- Fixed time quantum for Round Robin
- No I/O operations or blocking states

## Troubleshooting

**Compilation Errors:**
- Ensure all .c and .h files are present
- Check gcc is installed: `gcc --version`
- Use make clean before rebuilding

**Runtime Errors:**
- Verify input file format is correct
- Check file permissions
- Ensure input file exists in current directory

**Unexpected Results:**
- Verify priority values (lower = higher priority)
- Check for typos in input file
- Review task order in output

## Authors
Group Project - CECS 326
[Add your names and student IDs here]

## License
Educational project for CECS 326 - Operating Systems
