// Jennifer do Nascimento dos Santos Rocha de Souza
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LI {
    float valor;
    struct LI *prox;
} LI;

typedef struct LE {
    int valor;
    LI *lista;
    struct LE *ant, *prox;
} LE;

// Funções para criar nós
LI* novo_no_li(float v) {
    LI* no = malloc(sizeof(LI));
    no->valor = v;
    no->prox = NULL;
    return no;
}

LE* novo_no_le(int v) {
    LE* no = malloc(sizeof(LE));
    no->valor = v;
    no->lista = NULL;
    no->ant = no->prox = NULL;
    return no;
}

// Inserção ordenada na LE (crescente)
void insere_le(LE **ini, int valor) {
    LE *novo = novo_no_le(valor), *atual = *ini, *ant = NULL;

    while (atual && atual->valor < valor) {
        ant = atual;
        atual = atual->prox;
    }

    if (!ant) {
        novo->prox = *ini;
        if (*ini) (*ini)->ant = novo;
        *ini = novo;
    } else {
        novo->prox = ant->prox;
        novo->ant = ant;
        ant->prox = novo;
        if (novo->prox) novo->prox->ant = novo;
    }
}

// Inserção ordenada na LI (decrescente)
void insere_li(LI **ini, float valor) {
    LI *novo = novo_no_li(valor);
    if (!(*ini)) {
        novo->prox = novo;
        *ini = novo;
        return;
    }

    LI *atual = *ini, *ant = NULL;

    do {
        if (valor > atual->valor) break;
        ant = atual;
        atual = atual->prox;
    } while (atual != *ini);

    if (!ant) {
        while (atual->prox != *ini) atual = atual->prox;
        novo->prox = *ini;
        atual->prox = novo;
        *ini = novo;
    } else {
        novo->prox = atual;
        ant->prox = novo;
    }
}

// Atribui LI a LE mais próxima (por diferença < 1)
void associa_li(LE *lista, float valor) {
    LE *melhor = NULL;
    float menorDif = 1.0;

    for (LE *p = lista; p; p = p->prox) {
        float dif = fabs(p->valor - valor);
        if (dif < 1.0 && dif < menorDif) {
            menorDif = dif;
            melhor = p;
        }
    }

    if (melhor)
        insere_li(&(melhor->lista), valor);
}

void imprime_li(FILE *f, LI *ini) {
    if (!ini) return;
    LI *atual = ini;
    do {
        fprintf(f, "%.2f", atual->valor);
        atual = atual->prox;
        if (atual != ini) fprintf(f, " ->");
    } while (atual != ini);
}

void imprime_lista(FILE *f, LE *ini) {
    fprintf(f, "[");
    for (LE *p = ini; p; p = p->prox) {
        fprintf(f, "%d", p->valor);
        if (p->lista) {
            fprintf(f, "(");
            imprime_li(f, p->lista);
            fprintf(f, ")");
        }
        if (p->prox) fprintf(f, "->");
    }
    fprintf(f, "]\n");
}

int main() {
    FILE *fin = fopen("L1Q3.in", "r");
    FILE *fout = fopen("L1Q3.out", "w");

    if (!fin || !fout) {
        printf("Erro ao abrir arquivos.\n");
        return 1;
    }

    char linha[3000];

    while (fgets(linha, sizeof(linha), fin)) {
        LE *le = NULL;
        char *token = strtok(linha, " \n");

        int modo = 0; // 0 = lendo LE, 1 = lendo LI

        while (token) {
            if (strcmp(token, "LE") == 0) {
                modo = 0;
            } else if (strcmp(token, "LI") == 0) {
                modo = 1;
            } else {
                if (modo == 0) {
                    insere_le(&le, atoi(token));
                } else {
                    associa_li(le, atof(token));
                }
            }
            token = strtok(NULL, " \n");
        }

        imprime_lista(fout, le);

        // Libera memória (opcional para muitos casos)
    }

    fclose(fin);
    fclose(fout);
    return 0;
}
