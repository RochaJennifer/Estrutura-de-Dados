#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

typedef enum { STRING, INTEIRO, REAL, PONTO } Tipo;

typedef struct {
    Tipo tipo;
    union {
        char string[50];
        int inteiro;
        float real;
        struct {
            float x, y;
        } ponto;
    } valor;
} Elemento;

float distancia2(float x, float y) {
    return x * x + y * y;
}

int cmp_str(const void *a, const void *b) {
    return strcmp(((Elemento *)a)->valor.string, ((Elemento *)b)->valor.string);
}

int cmp_int(const void *a, const void *b) {
    return ((Elemento *)a)->valor.inteiro - ((Elemento *)b)->valor.inteiro;
}

int cmp_float(const void *a, const void *b) {
    float diff = ((Elemento *)a)->valor.real - ((Elemento *)b)->valor.real;
    return (diff > 0) - (diff < 0);
}

int cmp_ponto(const void *a, const void *b) {
    float d1 = distancia2(((Elemento *)a)->valor.ponto.x, ((Elemento *)a)->valor.ponto.y);
    float d2 = distancia2(((Elemento *)b)->valor.ponto.x, ((Elemento *)b)->valor.ponto.y);
    return (d1 > d2) - (d1 < d2);
}

int main() {
    FILE *fin = fopen("L0Q2.in", "r");
    FILE *fout = fopen("L0Q2.out", "w");

    if (!fin || !fout) {
        printf("Erro ao abrir arquivos.\n");
        return 1;
    }

    Elemento strings[100], inteiros[100], reais[100], pontos[100];
    int s = 0, i = 0, r = 0, p = 0;

    char token[1000];

    while (fscanf(fin, "%s", token) != EOF) {
        float x, y;
        int inteiro;
        float real;

        // Verifica se é ponto
        if (sscanf(token, "(%f,%f)", &x, &y) == 2) {
            pontos[p].tipo = PONTO;
            pontos[p].valor.ponto.x = x;
            pontos[p].valor.ponto.y = y;
            p++;
        }
        // Verifica se é inteiro
        else if (sscanf(token, "%d", &inteiro) == 1 && strchr(token, '.') == NULL) {
            inteiros[i].tipo = INTEIRO;
            inteiros[i].valor.inteiro = inteiro;
            i++;
        }
        // Verifica se é real
        else if (sscanf(token, "%f", &real) == 1 && strchr(token, '.') != NULL) {
            reais[r].tipo = REAL;
            reais[r].valor.real = real;
            r++;
        }
        // Senão, é string
        else {
            strings[s].tipo = STRING;
            strncpy(strings[s].valor.string, token, sizeof(strings[s].valor.string));
            s++;
        }
    }

    // Ordenar
    qsort(strings, s, sizeof(Elemento), cmp_str);
    qsort(inteiros, i, sizeof(Elemento), cmp_int);
    qsort(reais, r, sizeof(Elemento), cmp_float);
    qsort(pontos, p, sizeof(Elemento), cmp_ponto);

    // Saída formatada no arquivo
    if (s > 0) {
        fprintf(fout, "str:");
        for (int j = 0; j < s; j++) {
            fprintf(fout, "%s%s", j == 0 ? "" : " ", strings[j].valor.string);
        }
        fprintf(fout, "\n");
    }

    if (i > 0) {
        fprintf(fout, "int:");
        for (int j = 0; j < i; j++) {
            fprintf(fout, "%d%s", inteiros[j].valor.inteiro, j == i - 1 ? "\n" : " ");
        }
    }

    if (r > 0) {
        fprintf(fout, "float:");
        for (int j = 0; j < r; j++) {
            fprintf(fout, "%.2f%s", reais[j].valor.real, j == r - 1 ? "\n" : " ");
        }
    }

    if (p > 0) {
        fprintf(fout, "p:");
        for (int j = 0; j < p; j++) {
            fprintf(fout, "(%.1f,%.1f)%s", pontos[j].valor.ponto.x, pontos[j].valor.ponto.y, j == p - 1 ? "\n" : " ");
        }
    }

    fclose(fin);
    fclose(fout);
    return 0;
}
