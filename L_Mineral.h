#ifndef LISTAMINERAIS_H
#define LISTAMINERAIS_H
#define MaxTam 1000
#include "Mineral.h"

typedef int Apontador_L;

typedef struct
{
    Mineral ListaM[MaxTam];
    Apontador_L pPrimeiro, pUltimo;
} L_Minerais;

void FLVazia_L(L_Minerais *LMinerais);
int LEhVazia_L(L_Minerais *LMinerais);
int LInsere_L(L_Minerais *LMinerais, Mineral x);
int LRetira_L(L_Minerais *LMinerais, char *nome, Mineral *pX);
void LImprime_L(L_Minerais *LMinerais);

#endif