#ifndef COMPARTIMENTO_H
#define COMPARTIMENTO_H
#include "rochamineral.h"

typedef struct celula* Apontador_c;
typedef struct celula{
    rochamineral rocha;
    struct celula* pprox;
}tcelula, *Apontador_I;

typedef struct{
    Apontador_c pprimeiro;
    Apontador_c pultimo;
    int contador;
}tlistarocha;

void flvaziarocha(tlistarocha* plistarocha);
int lehvaziarocha(tlistarocha* plistarocha);
void linsererocha(tlistarocha* plistarocha, rochamineral *procha);
float PesoTotal(tlistarocha *compartimento);
void limprimerocha(tlistarocha* plistarocha);
void OrdenarRochas(tlistarocha *lista);
void RemoverPrimeiraRocha(tlistarocha *lista, rochamineral *rocha);

#endif