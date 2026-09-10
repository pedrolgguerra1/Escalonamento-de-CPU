Simulador de Escalonamento de Tarefas Criticas de Voo

Arquivos implementados:
- scheduler.h: Definicao das estruturas de dados e prototipos
- parser.c: Leitura e validacao estrita dos parametros de entrada
- simulador.c: Execucao discreta das politicas Rate-Monotonic e EDF
- main.c: Ponto de entrada e validacao dos argumentos da linha de comando
- Makefile: Automacao do processo de compilacao e limpeza

Ambiente de execucao:
- Sistema Operacional: Linux x86_64
- Compilador: GCC (C99)

Compilacao:
make clean
make

Execucao:
./scheduler rate voo.txt
./scheduler edf voo.txt