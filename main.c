#include "scheduler.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <rate|edf> <arquivo_de_entrada>\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "rate") != 0 && strcmp(argv[1], "edf") != 0) {
        fprintf(stderr, "Erro: Algoritmo invalido '%s'. Escolha 'rate' ou 'edf'.\n", argv[1]);
        return 1;
    }

    SimulationData sim;
    if (!parse_input_file(argv[2], &sim)) {
        return 1;
    }

    printf("Arquivo carregado com sucesso: %d tarefas lidas.\n", sim.num_tasks);
    return 0;
}