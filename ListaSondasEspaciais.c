#include "ListaSondasEspaciais.h"
#include <stdio.h>
#include <stdlib.h>

void FLvazia(Tlista *lista) {
    lista->pPrimeiro = (Apontador)malloc(sizeof(TCelula));
    lista->pPrimeiro->pProx = NULL;
    lista->pUltimo = lista->pPrimeiro;
    lista->numSondas = 0;  // Inicializa o contador de sondas
}

int LehVazia(Tlista *lista) {
    return (lista->pPrimeiro == lista->pUltimo);
}

int Linsere(Tlista *lista, DadosSonda *sonda) {
    lista->pUltimo->pProx = (Apontador)malloc(sizeof(TCelula));
    if (lista->pUltimo->pProx == NULL) return 0;
    lista->pUltimo = lista->pUltimo->pProx;
    lista->pUltimo->sonda = *sonda;
    lista->pUltimo->pProx = NULL;
    lista->numSondas++;  // Atualiza o número de sondas
    return 1; 
}

int Retira(Tlista *lista, DadosSonda *pGuardar) {
    if (LehVazia(lista))
        return 0; 

    TCelula *pAux = lista->pPrimeiro->pProx;
    *pGuardar = pAux->sonda;
    lista->pPrimeiro->pProx = pAux->pProx;
    
    if (pAux == lista->pUltimo)
        lista->pUltimo = lista->pPrimeiro;
    
    lista->numSondas--;  // Atualiza o número de sondas
    free(pAux);
    return 1; 
}

void Imprime(Tlista *lista) {
    Apontador pAux = lista->pPrimeiro->pProx;
    while (pAux != NULL) {
        printf("\nID: %d\n", pAux->sonda.Identificador);
        printf("Latitude: %.2f\n", pAux->sonda.Latitude);
        printf("Longitude: %.2f\n", pAux->sonda.Longitude);
        printf("Estado: %s\n", pAux->sonda.EstaLigada ? "LIGADA" : "DESLIGADA");
        pAux = pAux->pProx;
    }
}
