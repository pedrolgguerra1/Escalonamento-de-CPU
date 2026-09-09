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

    return 0;
}