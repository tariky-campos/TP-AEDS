#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compartimento.h"
 

void flvaziarocha(tlistarocha* plistarocha){
    plistarocha->pprimeiro=(Apontador_c) malloc(sizeof(tcelula));
    plistarocha->pultimo=plistarocha->pprimeiro;
    plistarocha->pprimeiro->pprox=NULL;
    plistarocha->contador=0;
} //cria compartimento vazio

int lehvaziarocha(tlistarocha* plistarocha){
    return(plistarocha->pprimeiro==plistarocha->pultimo);
} //confere se o compartimento esta vazio

void linsererocha(tlistarocha *plistarocha, rochamineral* procha) {
    Apontador_c paux = plistarocha->pprimeiro->pprox;
    while (paux != NULL) {
        if (strcmp(paux->rocha.categoria, procha->categoria) == 0) {
            trocarocha(plistarocha, procha);
            return; 
        }
        paux = paux->pprox;
    }

    plistarocha->pultimo->pprox = (Apontador_c) malloc(sizeof(tcelula));
    plistarocha->pultimo = plistarocha->pultimo->pprox;
    plistarocha->pultimo->rocha = *procha;
    plistarocha->pultimo->pprox = NULL;
    plistarocha->contador++;
} // insere rocha, e se ja tiver uma rocha da mesma categoria e peso maior ao de rocha que será inserida,
  //troca a rocha ja inserida pela nova que esta sendo inserida

int lretirarocha(tlistarocha* plistarocha, rochamineral* procha){
    tcelula* paux;
    if(lehvaziarocha(plistarocha))
        return 0;
    *procha=plistarocha->pprimeiro->pprox->rocha;
    paux=plistarocha->pprimeiro;
    plistarocha->pprimeiro=plistarocha->pprimeiro->pprox;
    free(paux);
    plistarocha->contador--;
    return 1;
}//confere se o compartimento esta vazio e retira rocha

void limprimerocha(tlistarocha *compartimento) {
    if (lehvaziarocha(compartimento)) {
        printf("Compartimento vazio!\n");
        return;
    }

    tcelula *atual = compartimento->pprimeiro->pprox;
    while (atual != NULL) {
        rochamineral *rocha = &atual->rocha;
        printf("Rocha ID: %d\n", rocha->idrocha);
        printf("%s %2f \n", rocha->categoria, rocha->peso);
        
        for (int i = rocha->listamineral.Primeiro; i < rocha->listamineral.Ultimo; i++) {
            printf("%s ", rocha->listamineral.Item[i].mineral.nome);
        }
        printf("\n");
        
        atual = atual->pprox;
    }
} // imprime compartimento

void tamanho(tlistarocha* plistarocha){
    printf("tamanho atual: %d\n",plistarocha->contador);
}// confere tamanho do compartimento

void peso(tlistarocha* plistarocha){
    float peso=0;
    Apontador_c paux;
    paux=plistarocha->pprimeiro->pprox;
    while(paux!=NULL){
        peso+=paux->rocha.peso;
        paux=paux->pprox;
    }
    printf("peso atual: %f",peso);
}//confere o peso do compartimento

void trocarocha(tlistarocha* plistarocha, rochamineral* procha) {
    Apontador_c paux = plistarocha->pprimeiro->pprox;
    while (paux != NULL) {
        if (strcmp(paux->rocha.categoria, procha->categoria) == 0 && procha->peso < paux->rocha.peso){
            paux->rocha = *procha; 
        }
        paux = paux->pprox;
    }
}//troca a rocha se ja tiver uma de mesma categoria pela com o menor peso


////////////
// tlistarocha.c

// Função para remover uma rocha do início da lista
void RemoverRochas(tlistarocha *compartimento) {
    if (compartimento->pprimeiro == NULL) {
        return; // Lista vazia, nada a remover
    }

    tcelula *temp = compartimento->pprimeiro;
    compartimento->pprimeiro = compartimento->pprimeiro->pprox;
    free(temp); // Libera a memória da célula removida

    // Se a lista ficou vazia, atualize o último ponteiro
    if (compartimento->pprimeiro == NULL) {
        compartimento->pprimeiro = NULL;
    }
}

// Calcula o peso total das rochas no compartimento
float PesoTotal(tlistarocha *compartimento) {
    float peso = 0.0;
    tcelula *atual = compartimento->pprimeiro;

    while (atual != NULL) {
        peso += atual->rocha.peso;
        atual = atual->pprox;
    }
    return peso;
}

// Ajusta o peso das rochas no compartimento para um valor alvo
void AjustarPeso(tlistarocha *compartimento, float peso_alvo) {
    float peso_atual = PesoTotal(compartimento);

    while (peso_atual > peso_alvo) {
        // Remova rochas até atingir o peso alvo
        RemoverRochas(compartimento);
        peso_atual = PesoTotal(compartimento);
    }
}
