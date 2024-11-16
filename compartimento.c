#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compartimento.h"

void flvaziarocha(tlistarocha* plistarocha) {
    plistarocha->pprimeiro = (Apontador_c)malloc(sizeof(tcelula));
    plistarocha->pultimo = plistarocha->pprimeiro;
    plistarocha->pprimeiro->pprox = NULL;
    plistarocha->contador = 0;
} // Cria compartimento vazio

int lehvaziarocha(tlistarocha* plistarocha) {
    return (plistarocha->pprimeiro == plistarocha->pultimo);
} // Confere se o compartimento está vazio
void linsererocha(tlistarocha *plistarocha, rochamineral *procha) {
    // Cria um novo nó para a rocha
    Apontador_c novaCelula = (Apontador_c)malloc(sizeof(tcelula));
    if (novaCelula == NULL) {
        printf("Erro: Falha ao alocar memória para nova rocha.\n");
        return;
    }

    // Copia os dados da rocha
    strcpy(novaCelula->rocha.categoria, procha->categoria);
    novaCelula->rocha.peso = procha->peso;
    novaCelula->rocha.localizacao = procha->localizacao;

    // Adiciona ao final da lista
    plistarocha->pultimo->pprox = novaCelula;
    novaCelula->pprox = NULL;
    plistarocha->pultimo = novaCelula;

    plistarocha->contador++;
}


int lretirarocha(tlistarocha* plistarocha, rochamineral* procha) {
    tcelula* paux;
    if (lehvaziarocha(plistarocha))
        return 0;

    *procha = plistarocha->pprimeiro->pprox->rocha;
    paux = plistarocha->pprimeiro;
    plistarocha->pprimeiro = plistarocha->pprimeiro->pprox;
    free(paux);
    plistarocha->contador--;
    return 1;
} // Confere se o compartimento está vazio e retira rocha

void limprimeRochaporCategoria(tlistarocha *plistarocha, const char *categoria) {
    Apontador_c paux = plistarocha->pprimeiro->pprox;
    int encontrou = 0; // Flag para verificar se encontrou a categoria

    printf("Rochas na categoria \"%s\":\n", categoria);
    while (paux != NULL) {
        if (strcmp(paux->rocha.categoria, categoria) == 0) {
            printf("- Rocha ID: %d | Peso: %.2f | Categoria: %s\n", 
                   paux->rocha.idrocha, paux->rocha.peso, paux->rocha.categoria);
            encontrou = 1;
        }
        paux = paux->pprox;
    }

    if (!encontrou) {
        printf("Nenhuma rocha encontrada na categoria \"%s\".\n", categoria);
    }
}
void limprimerocha(tlistarocha* plistarocha){
    Apontador_c paux;
    paux=plistarocha->pprimeiro->pprox;
    while(paux!=NULL){
        printf("%s %.2f\n",paux->rocha.categoria, paux->rocha.peso);
        paux=paux->pprox;
    }
}

void tamanho(tlistarocha* plistarocha) {
    printf("Tamanho atual: %d\n", plistarocha->contador);
} // Confere o tamanho do compartimento

void peso(tlistarocha* plistarocha) {
    float peso = 0;
    Apontador_c paux = plistarocha->pprimeiro->pprox;
    while (paux != NULL) {
        peso += paux->rocha.peso;
        paux = paux->pprox;
    }
    printf("Peso atual: %.2f\n", peso);
} // Confere o peso total do compartimento

void trocarocha(tlistarocha* plistarocha, rochamineral* procha) {
    Apontador_c paux = plistarocha->pprimeiro->pprox;
    while (paux != NULL) {
        if (strcmp(paux->rocha.categoria, procha->categoria) == 0 && procha->peso > paux->rocha.peso) {
            // Substitui pela nova rocha
            strcpy(paux->rocha.categoria, procha->categoria);
            paux->rocha.peso = procha->peso;
            return;
        }
        paux = paux->pprox;
    }
} // Substitui rocha existente por outra de maior peso

////////////
// tlistarocha.c

void RemoverRochas(tlistarocha *compartimento) {
    if (compartimento->pprimeiro->pprox == NULL) {
        return; // Lista vazia, nada a remover
    }

    tcelula *temp = compartimento->pprimeiro->pprox;
    compartimento->pprimeiro->pprox = temp->pprox;
    free(temp);

    // Atualiza o ponteiro "pultimo" se a lista ficar vazia
    if (compartimento->pprimeiro->pprox == NULL) {
        compartimento->pultimo = compartimento->pprimeiro;
    }
}

float PesoTotal(tlistarocha* compartimento) {
    float peso = 0.0;
    tcelula* atual = compartimento->pprimeiro->pprox; // Ignorar célula cabeça

    while (atual != NULL) {
        peso += atual->rocha.peso;
        atual = atual->pprox;
    }
    return peso;
}

void AjustarPeso(tlistarocha *compartimento, float peso_alvo) {
    float peso_atual = PesoTotal(compartimento);

    while (peso_atual > peso_alvo) {
        // Remove rochas até atingir o peso alvo
        RemoverRochas(compartimento);
        peso_atual = PesoTotal(compartimento);
    }
}
