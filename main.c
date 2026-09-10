#include "scheduler.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <rate|edf> <arquivo_de_entrada>\n", argv[0]);
        return 1;
    }

    SchedAlgo algo;
    if (strcmp(argv[1], "rate") == 0) {
        algo = ALGO_RATE;
    } else if (strcmp(argv[1], "edf") == 0) {
        algo = ALGO_EDF;
    } else {
        fprintf(stderr, "Erro: Algoritmo invalido '%s'. Escolha 'rate' ou 'edf'.\n", argv[1]);
        return 1;
    }

    SimulationData sim;
    if (!parse_input_file(argv[2], &sim)) {
        return 1;
    }

    const char *login = "plgg";
    run_simulation(&sim, algo, login);

    return 0;
}