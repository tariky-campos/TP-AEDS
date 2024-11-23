#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "L_Mineral.h"

void FLVazia_L(L_Minerais *LMinerais)
{
    LMinerais->pPrimeiro = 0;
    LMinerais->pUltimo = LMinerais->pPrimeiro;
}

int LEhVazia_L(L_Minerais *LMinerais)
{
    return (LMinerais->pUltimo == LMinerais->pPrimeiro);
}

int LInsere_L(L_Minerais *LMinerais, Mineral x)
{
    if (LMinerais->pUltimo == MaxTam)
        return 0; // Lista cheia
    LMinerais->ListaM[LMinerais->pUltimo++] = x;
    return 1;
}

int LRetira_L(L_Minerais *LMinerais, char *nome, Mineral *pX)
{
    int i, cont;
    for (i = 0; i < LMinerais->pUltimo; i++)
    {
        if (strcmp(LMinerais->ListaM[i].nome, nome) == 0)
        {
            *pX = LMinerais->ListaM[i];
            LMinerais->pUltimo--;

            for (cont = i + 1; cont <= LMinerais->pUltimo; cont++)
            {
                LMinerais->ListaM[cont - 1] = LMinerais->ListaM[cont];
            }
            return 1;
        }
    }
    return 0;
}

void LImprime_L(L_Minerais *L_mineral)
{
    int i;

    printf("minerais:\n");
    for (i = L_mineral->pPrimeiro; i < L_mineral->pUltimo; i++)
    {
        printf("Nome: %s\n", L_mineral->ListaM[i].nome);
        printf("Cor: %s\n", L_mineral->ListaM[i].cor);
        printf("Dureza: %.3lf\n", L_mineral->ListaM[i].dureza);
        printf("Reatividade: %.3lf\n\n", L_mineral->ListaM[i].reatividade);
    }
}