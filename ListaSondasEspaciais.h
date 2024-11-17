#ifndef LISTASONDASESPACIAIS_H
#define LISTASONDASESPACIAIS_H
#include "DadosSonda.h"
#include <math.h>

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
void RedistribuirRochas(Tlista *listasondas);

void RemoverTodasRochas(tlistarocha *origem, tlistarocha *destino);
float CalcularDistancia(float lat1, float lon1, float lat2, float lon2);
void MoverSondasParaOrigem(Tlista *listasondas);
void AdicionarRochaNaSondaMaisProxima(Tlista *listasondas, rochamineral *novaRocha);
DadosSonda* EncontrarSondaMaisProxima(Tlista *listasondas, float latitude, float longitude);

#endif