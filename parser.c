#include "scheduler.h"

bool parse_input_file(const char *filename, SimulationData *sim) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "Erro: Falha ao abrir o arquivo '%s'.\n", filename);
        return false;
    }

    if (fscanf(fp, "%d", &sim->total_time) != 1 || sim->total_time <= 0) {
        fprintf(stderr, "Erro: Tempo total de simulacao invalido.\n");
        fclose(fp);
        return false;
    }

    sim->num_tasks = 0;
    char name[MAX_NAME_LEN];
    int p, d, c;

    while (fscanf(fp, "%31s %d %d %d", name, &p, &d, &c) == 4) {
        if (sim->num_tasks >= MAX_TASKS) {
            fprintf(stderr, "Erro: Limite maximo de tarefas excedido.\n");
            fclose(fp);
            return false;
        }

        if (p <= 0 || d <= 0 || c <= 0) {
            fprintf(stderr, "Erro: Valores de P, D e C devem ser inteiros positivos (tarefa %s).\n", name);
            fclose(fp);
            return false;
        }

        if (c > d || d > p) {
            fprintf(stderr, "Erro: Violacao das restricoes C <= D <= P na tarefa %s (C=%d, D=%d, P=%d).\n",
                    name, c, d, p);
            fclose(fp);
            return false;
        }

        Task *t = &sim->tasks[sim->num_tasks];
        snprintf(t->name, sizeof(t->name), "%s", name);
        t->period = p;
        t->deadline = d;
        t->burst = c;
        t->file_order = sim->num_tasks;
        sim->num_tasks++;
    }

    fclose(fp);

    if (sim->num_tasks == 0) {
        fprintf(stderr, "Erro: Nenhuma tarefa valida encontrada no arquivo.\n");
        return false;
    }

    return true;
}