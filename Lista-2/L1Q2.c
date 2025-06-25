// Jennifer do Nascimento dos Santos Rocha de Souza
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PILHA 100
#define MAX_LINHA 3000
#define MAX_NOME 100

typedef struct {
    char nomes[MAX_PILHA][MAX_NOME];
    int topo;
} Pilha;

void push(Pilha *p, const char *nome) {
    strcpy(p->nomes[p->topo], nome);
    p->topo++;
}

void pop(Pilha *p, char *dest) {
    p->topo--;
    strcpy(dest, p->nomes[p->topo]);
}

void ordena_alfabeticamente(char nomes[][MAX_NOME], int qtde) {
    for (int i = 0; i < qtde - 1; i++) {
        for (int j = 0; j < qtde - i - 1; j++) {
            if (strcmp(nomes[j], nomes[j + 1]) > 0) {
                char tmp[MAX_NOME];
                strcpy(tmp, nomes[j]);
                strcpy(nomes[j], nomes[j + 1]);
                strcpy(nomes[j + 1], tmp);
            }
        }
    }
}

int main() {
    FILE *fin = fopen("L1Q2.in", "r");
    FILE *fout = fopen("L1Q2.out", "w");

    if (!fin || !fout) {
        printf("Erro ao abrir arquivos.\n");
        return 1;
    }

    char linha[MAX_LINHA];

    while (fgets(linha, sizeof(linha), fin)) {
        Pilha pilha;
        pilha.topo = 0;

        char nomes[MAX_PILHA][MAX_NOME];
        int n = 0;

        char *token = strtok(linha, " \n");
        while (token) {
            strcpy(nomes[n++], token);
            token = strtok(NULL, " \n");
        }

        for (int i = 0; i < n; i++) {
            // Extrai todos da pilha
            char todos[MAX_PILHA][MAX_NOME];
            int qtd_pop = 0;

            while (pilha.topo > 0) {
                pop(&pilha, todos[qtd_pop]);
                qtd_pop++;
            }

            // Inclui novo nome
            strcpy(todos[qtd_pop], nomes[i]);
            qtd_pop++;

            // Ordena
            ordena_alfabeticamente(todos, qtd_pop);

            // Acha posição do novo nome
            int pos;
            for (pos = 0; pos < qtd_pop; pos++) {
                if (strcmp(todos[pos], nomes[i]) == 0) break;
            }

            if (pos > 0)
                fprintf(fout, "push=%s %dx=pop ", nomes[i], pos);
            else
                fprintf(fout, "push=%s ", nomes[i]);

            // Reconstrói pilha
            for (int j = qtd_pop - 1; j >= 0; j--)
                push(&pilha, todos[j]);
        }

        fprintf(fout, "\n");
    }

    fclose(fin);
    fclose(fout);
    return 0;
}
