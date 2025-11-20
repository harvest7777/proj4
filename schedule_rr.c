/**
Round-robin scheduling

 References:
 1.Lecture Slide: CPU Scheduling  From Professor slide number 22 to 25
 2. Coding Implementation Reference : https://www.geeksforgeeks.org/operating-systems/program-for-round-robin-scheduling-for-the-same-arrival-time/
 3. Free Memory in C : https://stackoverflow.com/questions/9069205/how-do-i-free-memory-in-c
 4. Formula to calculate average waiting time and turnaround time : https://www.geeksforgeeks.org/operating-systems/difference-between-turn-around-time-tat-and-waiting-time-wt-in-cpu-scheduling/


Note for implementation from professor description: :
- For round-robin scheduling, the length of a time quantum is 10 milliseconds

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
struct node *current_node = NULL;
int task_id = 0;

// Add task to list
void add(char *name, int priority, int burst)
{
    // I do the same with other FCFS and Priority( Resources:https://www.geeksforgeeks.org/c/dynamic-memory-allocation-in-c-using-malloc-calloc-free-and-realloc/)
    Task *new_task = malloc(sizeof(Task));

    new_task->name = malloc(strlen(name) + 1);
    strcpy(new_task->name, name);
    new_task->tid = ++task_id;
    new_task->priority = priority;
    new_task->burst = burst;

    insert(&head, new_task);
}

// Reverse list to maintain FIFO order for round robin
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

// Get next task in round-robin
Task *pickNextTask()
{
    if (head == NULL)
        return NULL;

    if (current_node == NULL || current_node->next == NULL)
    {
        current_node = head;
    }
    else
    {
        current_node = current_node->next;
    }

    return current_node->task;
}

// Round Robin scheduling
void schedule()
{
    printf("Round Robin Scheduling (Time Quantum = %d)\n", QUANTUM);

    // Reverse list to get FIFO order
    head = reverseList(head);

    // Create a copy of burst times to track remaining time
    struct node *temp = head;
    int task_count = 0;
    int total_burst = 0;

    while (temp != NULL)
    {
        task_count++;
        total_burst += temp->task->burst;
        temp = temp->next;
    }

    // Allocate arrays track remaining burst times and completion
    int *remaining_burst = malloc(task_count * sizeof(int));
    int *wait_time = malloc(task_count * sizeof(int));
    int *turnaround_time = malloc(task_count * sizeof(int));
    int *response_time = malloc(task_count * sizeof(int));
    int *first_run = malloc(task_count * sizeof(int));

    // Initialize arrays
    temp = head;
    for (int i = 0; i < task_count; i++)
    {
        remaining_burst[i] = temp->task->burst;
        wait_time[i] = 0;
        turnaround_time[i] = 0;
        response_time[i] = -1; // -1 because of not started yet
        first_run[i] = 0;
        temp = temp->next;
    }

    int current_time = 0;
    int completed_tasks = 0;
    int task_index = 0;

    // Run round robin
    while (completed_tasks < task_count)
    {
        int tasks_processed = 0;
        temp = head;
        task_index = 0;

        while (temp != NULL)
        {
            if (remaining_burst[task_index] > 0)
            {
                tasks_processed++;

                // Record first response time
                if (!first_run[task_index])
                {
                    response_time[task_index] = current_time;
                    first_run[task_index] = 1;
                }

                // Determine time slice
                int time_slice = (remaining_burst[task_index] < QUANTUM) ? remaining_burst[task_index] : QUANTUM;

                printf("Time %d: Running %s for %d units (remaining: %d)\n",
                       current_time, temp->task->name, time_slice,
                       remaining_burst[task_index] - time_slice);

                // Run the task
                run(temp->task, time_slice);

                // Update times
                remaining_burst[task_index] -= time_slice;
                current_time += time_slice;

                // Check if task completed, if not continue
                if (remaining_burst[task_index] == 0)
                {
                    completed_tasks++;
                    turnaround_time[task_index] = current_time;
                    wait_time[task_index] = current_time - temp->task->burst;
                    printf("Task %s completed at time %d\n", temp->task->name, current_time);
                }

                printf("\n");
            }

            temp = temp->next;
            task_index++;
        }

        // Break if no tasks were processed (all tasks completed)
        if (tasks_processed == 0)
            break;
    }
    // Print each task
    temp = head;
    task_index = 0;
    int total_wait = 0;
    int total_turnaround = 0;
    int total_response = 0;

    while (temp != NULL)
    {
        printf("Task %s:\n", temp->task->name);
        printf("Priority: %d, Burst: %d\n", temp->task->priority, temp->task->burst);
        printf("Wait Time: %d, Turnaround Time: %d, Response Time: %d\n",
               wait_time[task_index], turnaround_time[task_index], response_time[task_index]);

        total_wait += wait_time[task_index];
        total_turnaround += turnaround_time[task_index];
        total_response += response_time[task_index];

        temp = temp->next;
        task_index++;
    }

    // Summary Calculations ( Resources : https://www.geeksforgeeks.org/operating-systems/difference-between-turn-around-time-tat-and-waiting-time-wt-in-cpu-scheduling/
    printf("\n");
    printf("Total Tasks: %d\n", task_count);
    printf("Total CPU Time: %d\n", current_time);
    printf("Average Wait Time: %.2f\n", (float)total_wait / task_count);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround / task_count);
    printf("Turnaround Time: %.2f\n", (float)total_turnaround);

    // Clean up memory( Resources: https://stackoverflow.com/questions/9069205/how-do-i-free-memory-in-c)
    free(remaining_burst);
    free(wait_time);
    free(turnaround_time);
    free(response_time);
    free(first_run);

    while (head != NULL)
    {
        struct node *temp = head;
        head = head->next;
        free(temp->task->name);
        free(temp->task);
        free(temp);
    }
}