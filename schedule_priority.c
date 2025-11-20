/*
 Priority scheduling Algorithm

References:
1. Lecture Slide: CPU Scheduling  From Professor slide number 20 and 21
2. Scheduling Algorithms - Priority Scheduling : https://www.youtube.com/watch?v=yKD3pcFvGmY
3. Program for Priority CPU: https://www.geeksforgeeks.org/operating-systems/program-for-priority-cpu-scheduling-set-1/
4. Formula to calculate average waiting time and turnaround time : https://www.geeksforgeeks.org/operating-systems/difference-between-turn-around-time-tat-and-waiting-time-wt-in-cpu-scheduling/
5. Free Memory in C : https://stackoverflow.com/questions/9069205/how-do-i-free-memory-in-c

Note for implementation from professor description:
-“Priorities range from 1 to 10, where a higher numeric value indicates a higher relative priority.”

 */

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>

#include "task.h"
#include "list.h"
#include "cpu.h"
#include "schedulers.h"

// Head of the list
struct node *head = NULL;
int task_id = 0;

// Add a task to list
void add(char *name, int priority, int burst)
{
    // Same to schedule_fcfs.c, we need allocate memory for task structure
    Task *new_task = malloc(sizeof(Task)); // Resources:https://www.geeksforgeeks.org/c/dynamic-memory-allocation-in-c-using-malloc-calloc-free-and-realloc/

    new_task->name = malloc(strlen(name) + 1);
    strcpy(new_task->name, name);
    new_task->tid = ++task_id;
    new_task->priority = priority;
    new_task->burst = burst;

    insert(&head, new_task);
}

// Find task with highest priority (largest priority number)
// Professor Project Description : higher numeric value == higher priority (10 -> 1).
Task *mynexttask()
{
    if (head == NULL)
        return NULL;

    struct node *current = head;
    struct node *best_node = head;
    Task *best_task = head->task;

    while (current != NULL)
    {
        // Higher numeric value means higher priority per spec
        if (current->task->priority > best_task->priority)
        {
            best_task = current->task;
            best_node = current;
        }
        current = current->next;
    }

    return best_task;
}

// Priority scheduling implementation
void schedule()
{
    printf("Priority Scheduling\n");

    int current_time = 0;
    int total_wait_time = 0;
    int total_turnaround_time = 0;
    int task_count = 0;

    // Count tasks up-front so we can compute averages at the end.
    struct node *temp = head;
    while (temp != NULL)
    {
        task_count++;
        temp = temp->next;
    }

    // Process tasks in priority order
    while (head != NULL)
    {
        // Pick highest priority task (largest numeric priority)
        Task *task = mynexttask();

        // Calculate TAT and WT (Resources: https://www.geeksforgeeks.org/operating-systems/difference-between-turn-around-time-tat-and-waiting-time-wt-in-cpu-scheduling/)
        int wait_time = current_time;
        int turnaround_time = current_time + task->burst;

        total_wait_time += wait_time;
        total_turnaround_time += turnaround_time;

        printf("Task %s:\n", task->name);
        printf("  Priority: %d, Burst: %d\n", task->priority, task->burst);
        printf("  Wait Time: %d, Turnaround Time: %d\n", wait_time, turnaround_time);

        // Run task
        run(task, task->burst);

        current_time += task->burst;

        // Remove chosen task from linked list, then free its memory.
        delete(&head, task);

        // Free task memory ( Resources : https://stackoverflow.com/questions/9069205/how-do-i-free-memory-in-c)
        free(task->name);
        free(task);
        printf("\n");
    }

    printf("Total Tasks: %d\n", task_count);
    printf("Total CPU Time: %d\n", current_time);
    printf("Average Wait Time: %.2f\n", (float)total_wait_time / task_count);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / task_count);
    printf("Turnaround Time: %.2f\n", (float)total_turnaround_time);
}