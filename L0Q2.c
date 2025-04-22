//Jennifer do Nascimento e Vinicius dos Santos

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define MAX_LINE 512


typedef struct {
    float x, y;
} Ponto;

int cmp_int(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int cmp_float(const void *a, const void *b) {
    float diff = *(float *)a - *(float *)b;
    return (diff > 0) - (diff < 0);
}

int cmp_str(const void *a, const void *b) {
    return strcmp(*(char **)a, *(char **)b);
}

float distancia(Ponto p) {
    return sqrt(p.x * p.x + p.y * p.y);
}

int cmp_ponto(const void *a, const void *b) {
    float d1 = distancia(*(Ponto *)a);
    float d2 = distancia(*(Ponto *)b);
    return (d1 > d2) - (d1 < d2);
}

int is_integer(const char *s) {
    if (*s == '-' || *s == '+') s++;
    if (!*s) return 0;
    while (*s) {
        if (!isdigit(*s)) return 0;
        s++;
    }
    return 1;
}

int is_float(const char *s) {
    int dot = 0;
    if (*s == '-' || *s == '+') s++;
    if (!*s) return 0;
    while (*s) {
        if (*s == '.') {
            if (dot) return 0;
            dot = 1;
        } else if (!isdigit(*s)) {
            return 0;
        }
        s++;
    }
    return dot;
}

int main() {
    
    FILE *entrada = fopen("L0Q2.in", "r");
    FILE *saida = fopen("L0Q2.out", "w");

    if (!entrada || !saida) {
        perror("Erro ao abrir arquivos");
        return 1;
    }
    
    char linha[MAX_LINE];

    while (fgets(linha, MAX_LINE, entrada)) {
        char *strings[100]; int qtd_s = 0;
        int inteiros[100], qtd_i = 0;
        float floats[100]; int qtd_f = 0;
        Ponto pontos[100]; int qtd_p = 0;

        char *token = strtok(linha, " \n");

        while (token) {
            if (token[0] == '(') {
                float x, y;
                sscanf(token, "(%f,%f)", &x, &y);
                pontos[qtd_p++] = (Ponto){x, y};
            }
            else if (is_integer(token)) {
                inteiros[qtd_i++] = atoi(token);
            }
            else if (is_float(token)) {
                floats[qtd_f++] = atof(token);
            }
            else {
                strings[qtd_s] = malloc(strlen(token) + 1);
                strcpy(strings[qtd_s++], token);
            }

            token = strtok(NULL, " \n");
        }

        qsort(strings, qtd_s, sizeof(char *), cmp_str);
        qsort(inteiros, qtd_i, sizeof(int), cmp_int);
        qsort(floats, qtd_f, sizeof(float), cmp_float);
        qsort(pontos, qtd_p, sizeof(Ponto), cmp_ponto);

        fprintf(saida,"str:");
        for (int i = 0; i < qtd_s; i++) fprintf(saida, "%s ", strings[i]);

        fprintf(saida, " int:");
        for (int i = 0; i < qtd_i; i++) fprintf(saida, "%d ", inteiros[i]);

        fprintf(saida, " float:");
        for (int i = 0; i < qtd_f; i++) fprintf(saida, "%.2f ", floats[i]);

        fprintf(saida, " p:");
        for (int i = 0; i < qtd_p; i++) fprintf(saida, "(%.1f,%.1f) ", pontos[i].x, pontos[i].y);

        fprintf(saida, "\n");

        for (int i = 0; i < qtd_s; i++) free(strings[i]);
    }
    
    fclose(entrada);
    fclose(saida);

    return 0;
}
