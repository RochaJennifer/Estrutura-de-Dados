// Equipe: Jennifer do Nascimento dos Santos Rocha de Souza
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LISTAS 100
#define MAX_NUMEROS 100
#define MAX_LINHA 3100

typedef struct {
    int numeros[MAX_NUMEROS];
    int qtde;
    int soma;
    int linha_original;
} Lista;

void ordena_decrescente(int *v, int n) {
    for (int i = 0; i < n -1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (v[j] < v[j+1]) {
                int tmp = v[j]; v[j] = v[j+1]; v[j+1] = tmp;
            }
}

int main() {
    FILE *fin = fopen("L1Q1.in", "r");
    FILE *fout = fopen("L1Q1.out", "w");

    if (!fin || !fout) {
        printf("Erro ao abrir arquivos.\n");
        return 1;
    }

    char linha[MAX_LINHA];
    int linha_index = 0;

    while (fgets(linha, sizeof(linha), fin)) {
        Lista listas[MAX_LISTAS];
        int total_listas = 0;

        char *token = strtok(linha, " \n");
        while (token) {
            if (strcmp(token, "start") == 0) {
                listas[total_listas].qtde = 0;
                listas[total_listas].soma = 0;
                listas[total_listas].linha_original = linha_index;
                total_listas++;
            } else {
                int val = atoi(token);
                Lista *lst = &listas[total_listas - 1];
                lst->numeros[lst->qtde++] = val;
                lst->soma += val;
            }
            token = strtok(NULL, " \n");
        }

        // Remove duplicatas de soma (mantendo a última)
        int ultima_soma[MAX_LISTAS];
        int idx_validas[MAX_LISTAS];
        int novas_qtde = 0;

        for (int i = total_listas - 1; i >= 0; i--) {
            int ja_foi = 0;
            for (int j = 0; j < novas_qtde; j++) {
                if (listas[i].soma == ultima_soma[j]) {
                    ja_foi = 1;
                    break;
                }
            }
            if (!ja_foi) {
                ultima_soma[novas_qtde] = listas[i].soma;
                idx_validas[novas_qtde] = i;
                novas_qtde++;
            }
        }

        // Reordenar idx_validas por soma crescente
        for (int i = 0; i < novas_qtde - 1; i++) {
            for (int j = 0; j < novas_qtde - i - 1; j++) {
                if (listas[idx_validas[j]].soma > listas[idx_validas[j+1]].soma) {
                    int tmp = idx_validas[j];
                    idx_validas[j] = idx_validas[j+1];
                    idx_validas[j+1] = tmp;
                }
            }
        }

        for (int i = 0; i < novas_qtde; i++) {
            Lista *lst = &listas[idx_validas[i]];
            ordena_decrescente(lst->numeros, lst->qtde);
            fprintf(fout, "start");
            for (int j = 0; j < lst->qtde; j++) {
                fprintf(fout, " %d", lst->numeros[j]);
            }
            fprintf(fout, "\n");
        }

        linha_index++;
    }

    fclose(fin);
    fclose(fout);
    return 0;
}

