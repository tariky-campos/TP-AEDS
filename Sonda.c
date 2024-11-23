#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Sonda.h"

void InicializaSonda(DadosSonda *sonda, int id, double latitude, double longitude, float capacidade, char *EstaLigada)
{
    setId(sonda, id);
    set_Latitude(sonda, latitude);
    set_Longitude(sonda, longitude);
    setCapacidade(sonda, capacidade);
    setEstaLigada(sonda, EstaLigada);
    FLVazia_R(&sonda->Compar_Rocha);
}
void LigarSonda(DadosSonda *sonda)
{
    strcpy((*sonda).EstaLigada, "Sim");
}
void DesligarSonda(DadosSonda *sonda)
{
    strcpy((*sonda).EstaLigada, "Nao");
}
void MoveSonda(DadosSonda *sonda, double latitude, double longitude)
{
    set_Latitude(sonda, latitude);
    set_Longitude(sonda, longitude);
}
float PesoSonda(DadosSonda *sonda)
{
    float pesoTotal = 0;
    if (sonda == NULL || sonda->Compar_Rocha.pPrimeiro->pProx == NULL) {
        return 0;
    }
    
    Apontador_R pAux = sonda->Compar_Rocha.pPrimeiro->pProx;
    while (pAux != NULL)
    {
        pesoTotal += pAux->rocha.peso;
        pAux = pAux->pProx;
    }
    return pesoTotal;
}

int getId(DadosSonda *sonda)
{
    return sonda->idSonda;
}
double get_Latitude(DadosSonda *sonda)
{
    return sonda->latitude;
}
double get_Longitude(DadosSonda *sonda)
{
    return sonda->longitude;
}
float getCapacidade(DadosSonda *sonda)
{
    return sonda->capacidade;
}
char *getEstaLigada(DadosSonda *sonda)
{
    return sonda->EstaLigada;
}

void setId(DadosSonda *sonda, int id)
{
    sonda->idSonda = id;
}
void set_Latitude(DadosSonda *sonda, double latitude)
{
    sonda->latitude = latitude;
}
void set_Longitude(DadosSonda *sonda, double longitude)
{
    sonda->longitude = longitude;
}
void setCapacidade(DadosSonda *sonda, float capacidade)
{
    sonda->capacidade = capacidade;
}
void setEstaLigada(DadosSonda *sonda, char *EstaLigada)
{
    strcpy(sonda->EstaLigada, EstaLigada);
}