#ifndef COMPARTIMENTO_H
#define COMPARTIMENTO_H
#include "rochamineral.h"

typedef struct celula* Apontador_c;
typedef struct celula{
    rochamineral rocha;
    struct celula* pprox;
}tcelula;

typedef struct{
    Apontador_c pprimeiro;
    Apontador_c pultimo;
    int contador;
}tlistarocha;

void flvaziarocha(tlistarocha* plistarocha);
int lehvaziarocha(tlistarocha* plistarocha);
void linsererocha(tlistarocha* plistarocha, rochamineral *procha);
int lretirarocha(tlistarocha* plistarocha, rochamineral *procha);
void limprimerocha(tlistarocha* plistarocha);
void tamanho(tlistarocha* plistarocha);
void peso(tlistarocha* plistarocha);
void trocarocha(tlistarocha* plistarocha, rochamineral *procha);
////////
void RemoverRochas(tlistarocha *compartimento);
float PesoTotal(tlistarocha *compartimento);
void AjustarPeso(tlistarocha *compartimento, float peso_alvo);



#endif