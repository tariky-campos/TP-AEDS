#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compartimento.h"

void flvaziarocha(tlistarocha* plistarocha) {
    plistarocha->pprimeiro = (Apontador_c)malloc(sizeof(tcelula));
    plistarocha->pultimo = plistarocha->pprimeiro;
    plistarocha->pprimeiro->pprox = NULL;
    plistarocha->contador = 0;
} // faz lista fazia

int lehvaziarocha(tlistarocha* plistarocha) {
    return (plistarocha->pprimeiro == plistarocha->pultimo);
} // confere se a lista esta fazia
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
}// insere a rocha na lista

void limprimerocha(tlistarocha* plistarocha){
    Apontador_c paux;
    paux=plistarocha->pprimeiro->pprox;
    while(paux!=NULL){
        printf("%s %.2f\n",paux->rocha.categoria, paux->rocha.peso);
        paux=paux->pprox;
    }
}//imprime a rocha

float PesoTotal(tlistarocha* compartimento) {
    float peso = 0.0;
    tcelula* atual = compartimento->pprimeiro->pprox; 

    while (atual != NULL) {
        peso += atual->rocha.peso;
        atual = atual->pprox;
    }
    return peso;
}//calcula o peso compartimento

void OrdenarRochas(tlistarocha *lista) {
    if (lista->pprimeiro == NULL || lista->pprimeiro->pprox == NULL)
        return;

    tcelula *i, *j;
    for (i = lista->pprimeiro->pprox; i != NULL; i = i->pprox) {
        for (j = i->pprox; j != NULL; j = j->pprox) {
            if (i->rocha.idrocha > j->rocha.idrocha) { 
               
                rochamineral temp = i->rocha;
                i->rocha = j->rocha;
                j->rocha = temp;
            }
        }
    }
}//ordena rocha em ordem decrescente

void RemoverPrimeiraRocha(tlistarocha *lista, rochamineral *rocha) {
    if (lehvaziarocha(lista)) return; 

    tcelula *aux = lista->pprimeiro->pprox; 
    *rocha = aux->rocha;                           

    lista->pprimeiro->pprox = aux->pprox;        
    if (aux->pprox == NULL)                       
        lista->pultimo = lista->pprimeiro;       

    free(aux);                                  
}//remove rocha da lista