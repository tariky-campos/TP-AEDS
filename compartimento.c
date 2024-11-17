#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compartimento.h"

void flvaziarocha(tlistarocha* plistarocha) {
    plistarocha->pprimeiro = (Apontador_c)malloc(sizeof(tcelula));
    plistarocha->pultimo = plistarocha->pprimeiro;
    plistarocha->pprimeiro->pprox = NULL;
    plistarocha->contador = 0;
} 

int lehvaziarocha(tlistarocha* plistarocha) {
    return (plistarocha->pprimeiro == plistarocha->pultimo);
} 
void linsererocha(tlistarocha *plistarocha, rochamineral *procha) {
  
    Apontador_c novaCelula = (Apontador_c)malloc(sizeof(tcelula));
    if (novaCelula == NULL) {
        printf("Erro: Falha ao alocar memória para nova rocha.\n");
        return;
    }

   
    strcpy(novaCelula->rocha.categoria, procha->categoria);
    novaCelula->rocha.peso = procha->peso;
    novaCelula->rocha.localizacao = procha->localizacao;

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
} 

void limprimeRochaporCategoria(tlistarocha *plistarocha, const char *categoria) {
    Apontador_c paux = plistarocha->pprimeiro->pprox;
    int encontrou = 0;

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
} 

void peso(tlistarocha* plistarocha) {
    float peso = 0;
    Apontador_c paux = plistarocha->pprimeiro->pprox;
    while (paux != NULL) {
        peso += paux->rocha.peso;
        paux = paux->pprox;
    }
    printf("Peso atual: %.2f\n", peso);
} 

void trocarocha(tlistarocha* plistarocha, rochamineral* procha) {
    Apontador_c paux = plistarocha->pprimeiro->pprox;
    while (paux != NULL) {
        if (strcmp(paux->rocha.categoria, procha->categoria) == 0 && procha->peso > paux->rocha.peso) {
           
            strcpy(paux->rocha.categoria, procha->categoria);
            paux->rocha.peso = procha->peso;
            return;
        }
        paux = paux->pprox;
    }
} 


void RemoverRochas(tlistarocha *compartimento) {
    if (compartimento->pprimeiro->pprox == NULL) {
        return; 
    }

    tcelula *temp = compartimento->pprimeiro->pprox;
    compartimento->pprimeiro->pprox = temp->pprox;
    free(temp);

   
    if (compartimento->pprimeiro->pprox == NULL) {
        compartimento->pultimo = compartimento->pprimeiro;
    }
}

float PesoTotal(tlistarocha* compartimento) {
    float peso = 0.0;
    tcelula* atual = compartimento->pprimeiro->pprox; 

    while (atual != NULL) {
        peso += atual->rocha.peso;
        atual = atual->pprox;
    }
    return peso;
}

void AjustarPeso(tlistarocha *compartimento, float peso_alvo) {
    float peso_atual = PesoTotal(compartimento);

    while (peso_atual > peso_alvo) {
       
        RemoverRochas(compartimento);
        peso_atual = PesoTotal(compartimento);
    }
}
