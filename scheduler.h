#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NAME_LEN 32
#define MAX_TASKS 64

typedef enum {
    ALGO_RATE,
    ALGO_EDF
} SchedAlgo;

typedef struct {
    char name[MAX_NAME_LEN];
    int period;
    int deadline;
    int burst;
    int file_order;

    int remaining_burst;
    int current_deadline;
    int next_arrival;
    bool is_active;

    int completed_executions;
    int lost_deadlines;
    int killed;
} Task;

typedef struct {
    int total_time;
    int num_tasks;
    Task tasks[MAX_TASKS];
} SimulationData;

bool parse_input_file(const char *filename, SimulationData *sim);
void run_simulation(SimulationData *sim, SchedAlgo algo, const char *login);

#endif