#include "scheduler.h"

bool parse_input_file(const char *filename, SimulationData *sim) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "Erro: Falha ao abrir o arquivo '%s'.\n", filename);
        return false;
    }

    if (fscanf(fp, "%d", &sim->total_time) != 1 || sim->total_time <= 0) {
        fprintf(stderr, "Erro: Tempo total invalido.\n");
        fclose(fp);
        return false;
    }

    sim->num_tasks = 0;
    char name[MAX_NAME_LEN];
    int p, d, c;

    while (fscanf(fp, "%31s %d %d %d", name, &p, &d, &c) == 4) {
        Task *t = &sim->tasks[sim->num_tasks];
        strncpy(t->name, name, sizeof(t->name) - 1);
        t->name[sizeof(t->name) - 1] = '\0';
        t->period = p;
        t->deadline = d;
        t->burst = c;
        t->file_order = sim->num_tasks;
        sim->num_tasks++;
    }

    fclose(fp);
    return true;
}