#ifndef LISTASONDASESPACIAIS_H
#define LISTASONDASESPACIAIS_H
#include "DadosSonda.h"

typedef struct Celula* Apontador;

typedef struct Celula{
    DadosSonda sonda;
    struct Celula* pProx;
    
}TCelula;

typedef struct{
    Apontador pPrimeiro;
    Apontador pUltimo;
    int numSondas;
}Tlista;

void FLvazia(Tlista *lista);
int LehVazia(Tlista *lista);
int Linsere(Tlista *lista, DadosSonda *pGuardar);
int Retira(Tlista *lista, DadosSonda *pGuardar);
void Imprime(Tlista *lista);
#endif