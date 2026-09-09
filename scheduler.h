#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NAME_LEN 32
#define MAX_TASKS 64

typedef struct {
    char name[MAX_NAME_LEN];
    int period;
    int deadline;
    int burst;
    int file_order;
} Task;

typedef struct {
    int total_time;
    int num_tasks;
    Task tasks[MAX_TASKS];
} SimulationData;

#endif
#define SCHEDULER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NAME_LEN 32
#define MAX_TASKS 64

typedef struct {
    char name[MAX_NAME_LEN];
    int period;
    int deadline;
    int burst;
    int file_order;
} Task;

typedef struct {
    int total_time;
    int num_tasks;
    Task tasks[MAX_TASKS];
} SimulationData;

#endif