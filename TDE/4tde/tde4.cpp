#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TAREFAS 26 // Máximo de tarefas (a-z)

// Estrutura para armazenar informações de uma tarefa
typedef struct {
    char id; // Identificação da tarefa
    int duracao; // Duração da tarefa
    int inicio_cedo;
    int fim_cedo;
    int inicio_tarde;
    int fim_tarde;
    int dependencias[MAX_TAREFAS]; // Lista de dependências
    int num_dependencias; // Número de dependências
} Tarefa;

Tarefa tarefas[MAX_TAREFAS]; // Array de tarefas
int contador_tarefas = 0; // Contador de tarefas
int matriz[MAX_TAREFAS][MAX_TAREFAS] = {0}; // Matriz de dependências

// Função que retorna o índice de uma tarefa dado o seu identificador
int indice(char c) {
    return c - 'a';
}

// Função que lê as tarefas do arquivo e preenche a matriz de dependências
void ler_tarefas(FILE *arquivo) {
    char linha[100];
    char tarefa;
    int duracao;

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        sscanf(linha, "%c,%d", &tarefa, &duracao); // Lê o identificador da tarefa e a duração
        int indice_tarefa = indice(tarefa);

        tarefas[indice_tarefa].id = tarefa;
        tarefas[indice_tarefa].duracao = duracao;
        tarefas[indice_tarefa].num_dependencias = 0;

        char *dependencias = strchr(linha, ',') + 1;
        while (*dependencias && !isdigit(*dependencias)) {
            dependencias++;
        }
        while (*dependencias) {
            if (isalpha(*dependencias)) {
                int indice_dependencia = indice(*dependencias);
                matriz[indice_dependencia][indice_tarefa] = 1; // Marca a dependência na matriz
                tarefas[indice_tarefa].dependencias[tarefas[indice_tarefa].num_dependencias++] = indice_dependencia;
            }
            dependencias++;
        }
        contador_tarefas++;
    }
}

// Função que calcula os tempos mais cedo de início e término para cada tarefa
void calcular_tempos_cedo() {
    for (int i = 0; i < contador_tarefas; i++) {
        for (int j = 0; j < contador_tarefas; j++) {
            if (matriz[i][j]) {
                if (tarefas[j].inicio_cedo < tarefas[i].fim_cedo) {
                    tarefas[j].inicio_cedo = tarefas[i].fim_cedo;
                    tarefas[j].fim_cedo = tarefas[j].inicio_cedo + tarefas[j].duracao;
                }
            }
        }
    }
}

// Função que calcula os tempos mais tarde de início e término para cada tarefa
void calcular_tempos_tarde(int duracao_projeto) {
    for (int i = 0; i < contador_tarefas; i++) {
        tarefas[i].fim_tarde = duracao_projeto;
        tarefas[i].inicio_tarde = duracao_projeto - tarefas[i].duracao;
    }

    for (int i = contador_tarefas - 1; i >= 0; i--) {
        for (int j = contador_tarefas - 1; j >= 0; j--) {
            if (matriz[j][i]) {
                if (tarefas[j].fim_tarde > tarefas[i].inicio_tarde) {
                    tarefas[j].fim_tarde = tarefas[i].inicio_tarde;
                    tarefas[j].inicio_tarde = tarefas[j].fim_tarde - tarefas[j].duracao;
                }
            }
        }
    }
}

int main() {
    FILE *arquivo = fopen("input.txt", "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }

    ler_tarefas(arquivo); // Lê as tarefas do arquivo
    fclose(arquivo);

    // Inicializa os tempos mais cedo
    for (int i = 0; i < contador_tarefas; i++) {
        tarefas[i].inicio_cedo = 0;
        tarefas[i].fim_cedo = tarefas[i].duracao;
    }
    calcular_tempos_cedo(); // Calcula os tempos mais cedo

    int duracao_projeto = 0;
    for (int i = 0; i < contador_tarefas; i++) {
        if (tarefas[i].fim_cedo > duracao_projeto) {
            duracao_projeto = tarefas[i].fim_cedo;
        }
    }

    calcular_tempos_tarde(duracao_projeto); // Calcula os tempos mais tarde

    printf("Duração mínima do projeto: %d\n", duracao_projeto);
    printf("Atividades críticas: ");
    for (int i = 0; i < contador_tarefas; i++) {
        if (tarefas[i].inicio_cedo == tarefas[i].inicio_tarde) {
            printf("%c ", tarefas[i].id);
        }
    }
    printf("\n");

    return 0;
}
