/**
FCFS scheduling

References:
1. Lecture Slide: CPU Scheduling  From Professor slide number 13 and 14
2. FCFS Definition :https://www.geeksforgeeks.org/dsa/first-come-first-serve-cpu-scheduling-non-preemptive/
3. Implementation :https://www.scaler.com/topics/first-come-first-serve
4. Formula to calculate average waiting time and turnaround time : https://www.geeksforgeeks.org/operating-systems/difference-between-turn-around-time-tat-and-waiting-time-wt-in-cpu-scheduling/
5. Memory allocation and deallocation in C : https://www.geeksforgeeks.org/c/dynamic-memory-allocation-in-c-using-malloc-calloc-free-and-realloc/
6.Free Memory in C : https://stackoverflow.com/questions/9069205/how-do-i-free-memory-in-c

Note for project from professor description:
-It is assumed that all tasks arrive at the same time, so your scheduler algorithms do not have to support
higher-priority processes preempting processes with lower priorities.

*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "task.h"
#include "list.h"
#include "cpu.h"
#include "schedulers.h"

// Head of the list
struct node *head = NULL;
int task_id = 0;

// Add a task to the list - FCFS adds to  end
void add(char *name, int priority, int burst)
{
    // Allocate memory for  task structure
    Task *new_task = malloc(sizeof(Task)); // Resources:https://www.geeksforgeeks.org/c/dynamic-memory-allocation-in-c-using-malloc-calloc-free-and-realloc/

    new_task->name = malloc(strlen(name) + 1);
    strcpy(new_task->name, name);
    new_task->tid = ++task_id;
    new_task->priority = priority;
    new_task->burst = burst;

    // For FCFS, we need to add at the end of  list to maintain arrival order
    // But insert adds at begin, I will need to reverse it later
    insert(&head, new_task);
}

// Reverse list to get FCFS order
struct node *reverseList(struct node *head)
{
    struct node *prev = NULL;
    struct node *current = head;
    struct node *next = NULL;

    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    return prev;
}

// Do FCFS scheduling
void schedule()
{
    printf("FCFS Scheduling\n");
    // Reverse list to get FCFS order
    head = reverseList(head);

    struct node *current = head;
    int current_time = 0;
    int total_wait_time = 0;
    int total_turnaround_time = 0;
    int task_count = 0;

    // Process each task in FCFS order
    while (current != NULL)
    {
        Task *task = current->task;
        // Calculate wait time and turnaround time. I follow this link : https://www.geeksforgeeks.org/operating-systems/difference-between-turn-around-time-tat-and-waiting-time-wt-in-cpu-scheduling/
        int wait_time = current_time;                     // because on professor project pdf said that : "assumed that all tasks arrive at the same time" so which meaning arrive time is 0
        int turnaround_time = current_time + task->burst; // TAT = CT - AT but AT =0 so TAT = CT

        total_wait_time += wait_time;
        total_turnaround_time += turnaround_time;
        task_count++;
        printf("Task %s:\n", task->name);
        printf("Priority: %d, Burst: %d\n", task->priority, task->burst);
        printf("Wait Time: %d, Turnaround Time: %d\n", wait_time, turnaround_time);

        // Run the task
        run(task, task->burst);
        current_time += task->burst;
        current = current->next;
    }

    // Print summary
    printf("\n");
    printf("Total Tasks: %d\n", task_count);
    printf("Total CPU Time: %d\n", current_time);
    printf("Average Wait Time: %.2f\n", (float)total_wait_time / task_count);             // Resources :From professor slide number 14
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / task_count); // Resources :From professor slide number 14
    printf("Turnaround Time: %.2f\n", (float)total_turnaround_time);

    // We need to clean up memory( Resources: https://stackoverflow.com/questions/9069205/how-do-i-free-memory-in-c)
    while (head != NULL)
    {
        struct node *temp = head;
        head = head->next;
        free(temp->task->name);
        free(temp->task);
        free(temp);
    }
}
