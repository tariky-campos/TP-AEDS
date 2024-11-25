#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "L_Mineral.h"

void FLVazia_L(L_Minerais *ListaMi)
{
    ListaMi->pPrimeiro = 0;
    ListaMi->pUltimo = ListaMi->pPrimeiro;
}

int LEhVazia_L(L_Minerais *ListaMi)
{
    return (ListaMi->pUltimo == ListaMi->pPrimeiro);
}

int LInsere_L(L_Minerais *ListaMi, Mineral item)
{
    if (ListaMi->pUltimo == MAXTAM)
        return 0; // Lista cheia
    ListaMi->ListaMINERAIS[ListaMi->pUltimo++] = item;
    return 1;
}

int LRetira_L(L_Minerais *ListaMi, char *nome, Mineral *pX)
{
    int i, cont;
    for (i = 0; i < ListaMi->pUltimo; i++)
    {
        if (strcmp(ListaMi->ListaMINERAIS[i].nome, nome) == 0)
        {
            *pX = ListaMi->ListaMINERAIS[i];
            ListaMi->pUltimo--;

            for (cont = i + 1; cont <= ListaMi->pUltimo; cont++)
            {
                ListaMi->ListaMINERAIS[cont - 1] = ListaMi->ListaMINERAIS[cont];
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
        printf("Nome: %s\n", L_mineral->ListaMINERAIS[i].nome);
        printf("Cor: %s\n", L_mineral->ListaMINERAIS[i].cor);
        printf("Dureza: %.3lf\n", L_mineral->ListaMINERAIS[i].dureza);
        printf("Reatividade: %.3lf\n\n", L_mineral->ListaMINERAIS[i].reatividade);
    }
}