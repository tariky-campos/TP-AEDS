#ifndef LISTASONDAS_H
#define LISTASONDAS_H
#include "Sonda.h"

typedef DadosSonda Tipo_Sonda;

typedef struct Celulas *Apontador_S;
typedef struct Celulas
{
    DadosSonda sonda;
    struct Celulas *pProx;
} Celula_S;

typedef struct
{
    Apontador_S pPrimeiro;
    Apontador_S pUltimo;
} L_Sondas;

void FLVazia_S(L_Sondas *ListaS);
int LInsere_S(L_Sondas *ListaS, DadosSonda *pSonda);
int LRetira_S(L_Sondas *ListaS, DadosSonda *pSonda);
void Insere_S(L_Sondas *ListaS, rochamineral *rocha);
void Imprime_S(L_Sondas *ListaS);

/////////////// Funções Adicionais /////////////

void MoverParaOrigem(L_Sondas *pLista_S);
rochamineral *RochaTEMP(rochamineral *rocha);
rochamineral *NovaListaTempRocha(L_Sondas *pLista_S, int *numRochas);
void Redistribuir(L_Sondas *pLista_S, rochamineral *rochas, int numRochas);
void OperacaoE(L_Sondas *ListaS);
void OperacaoI(L_Sondas *ListaSonda);
DadosSonda *CalcularEuclidiana(L_Sondas *ListaS, double lat_r, double long_r, rochamineral *rocha);
int OrdenarPorPeso(const void *a, const void *b);
#endif