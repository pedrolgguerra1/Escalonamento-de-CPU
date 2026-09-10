#include "scheduler.h"

static int choose_task_rate(SimulationData *sim) {
    int best_idx = -1;
    for (int i = 0; i < sim->num_tasks; i++) {
        Task *t = &sim->tasks[i];
        if (t->is_active && t->remaining_burst > 0) {
            if (best_idx == -1) {
                best_idx = i;
            } else {
                if (t->period < sim->tasks[best_idx].period) {
                    best_idx = i;
                } else if (t->period == sim->tasks[best_idx].period) {
                    if (t->file_order < sim->tasks[best_idx].file_order) {
                        best_idx = i;
                    }
                }
            }
        }
    }
    return best_idx;
}

void run_simulation(SimulationData *sim, SchedAlgo algo, const char *login) {
    char out_filename[128];
    snprintf(out_filename, sizeof(out_filename), "%s_%s.out",
             (algo == ALGO_RATE ? "rate" : "edf"), login);

    FILE *out = fopen(out_filename, "w");
    if (!out) {
        fprintf(stderr, "Erro ao criar arquivo de saida %s\n", out_filename);
        exit(1);
    }

    fprintf(out, "EXECUTION BY RATE\n");

    int current_running = -1;
    int current_block_duration = 0;

    for (int t = 0; t < sim->total_time; t++) {
        for (int i = 0; i < sim->num_tasks; i++) {
            Task *task = &sim->tasks[i];
            if (t == task->next_arrival) {
                task->is_active = true;
                task->remaining_burst = task->burst;
                task->current_deadline = t + task->deadline;
                task->next_arrival = t + task->period;
            }
        }

        int chosen = choose_task_rate(sim);

        if (chosen != current_running && current_block_duration > 0) {
            if (current_running == -1) {
                fprintf(out, "idle for %d units\n", current_block_duration);
            } else {
                fprintf(out, "[%s] for %d units - H\n", sim->tasks[current_running].name, current_block_duration);
            }
            current_block_duration = 0;
        }

        current_running = chosen;
        current_block_duration++;

        if (current_running != -1) {
            sim->tasks[current_running].remaining_burst--;
        }

        if (current_running != -1 && sim->tasks[current_running].remaining_burst == 0) {
            sim->tasks[current_running].completed_executions++;
            sim->tasks[current_running].is_active = false;
            fprintf(out, "[%s] for %d units\n", sim->tasks[current_running].name, current_block_duration);
            fprintf(out, "F\n");
            current_block_duration = 0;
            current_running = -1;
        }
    }

    if (current_block_duration > 0) {
        if (current_running == -1) {
            fprintf(out, "idle for %d units\n", current_block_duration);
        } else {
            fprintf(out, "[%s] for %d units\n", sim->tasks[current_running].name, current_block_duration);
        }
    }

    fclose(out);
}