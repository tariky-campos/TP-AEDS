#ifndef DADOSSONDA_H
#define DADOSSONDA_H
#include "Compartimento.h"

typedef struct
{
    int idSonda;
    double latitude, longitude;
    L_Compart Compar_Rocha;
    float capacidade;
    char EstaLigada[3];
    
} DadosSonda;

void InicializaSonda(DadosSonda *sonda, int idSonda, double latitude, double longitude, float capacidade, char *EstaLigada);
void LigarSonda(DadosSonda *sonda);
void DesligarSonda(DadosSonda *sonda);
void MoveSonda(DadosSonda *sonda, double latitude, double longitude);
float PesoSonda(DadosSonda *sonda);

int getId(DadosSonda *sonda);
double get_Latitude(DadosSonda *sonda);
double get_Longitude(DadosSonda *sonda);
float getCapacidade(DadosSonda *sonda);
char *getEstaLigada(DadosSonda *sonda);

void setId(DadosSonda *sonda, int id);
void set_Latitude(DadosSonda *sonda, double latitude);
void set_Longitude(DadosSonda *sonda, double longitude);
void setCapacidade(DadosSonda *sonda, float capacidade);
void setEstaLigada(DadosSonda *sonda, char *EstaLigada);

#endif