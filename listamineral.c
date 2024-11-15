#include "listamineral.h"
#include <stdlib.h>
#include <stdio.h>

void FLVaziamineral(tlistamineral* plistamineral)
{
 plistamineral->Primeiro = InicioArranjo;
 plistamineral->Ultimo = plistamineral->Primeiro;
} // faz lista fazia

int LEhVaziamineral(tlistamineral* plistamineral)
{
 return (plistamineral->Ultimo == plistamineral->Primeiro);
} //confere se a lista esta vazia

int LInseremineral(tlistamineral* plistamineral, TItem x)
{
 if (plistamineral->Ultimo == MaxTam)
 return 0; // confere se a lista esta cheia
 plistamineral->Item[plistamineral->Ultimo++] = x;
 return 1;
} // insere novo mineral na lista

int LRetiramineral(tlistamineral* plistamineral, apontador_m p, TItem *pX)
{
 int cont;
 if (LEhVaziamineral(plistamineral) || p >= plistamineral->Ultimo || p < 0)
 return 0;
 *pX = plistamineral->Item[p];
 plistamineral->Ultimo--;
 for (cont = p+1; cont <= plistamineral->Ultimo; cont++)
 plistamineral->Item[cont - 1] = plistamineral->Item[cont];
 return 1;
} //retira mineral da lista

void LImprimemineral(tlistamineral* plistamineral)
{
    int i;
    for (i = plistamineral->Primeiro; i < plistamineral->Ultimo; i++){
        printf("%s\n", plistamineral->Item[i].mineral.nome);
        printf("%f\n", plistamineral->Item[i].mineral.dureza);
        printf("%f\n", plistamineral->Item[i].mineral.reatividade);
        printf("%s\n", plistamineral->Item[i].mineral.cor);
    }
} //imprime a lista