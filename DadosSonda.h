#ifndef DADOSSONDA_H
#define DADOSSONDA_H
#include "compartimento.h"


typedef struct {
    int Identificador;
    tlistarocha compartimento;
    float Latitude;
    float Longitude;
    int EstaLigada;
    float Capacidade;
    float Velocidade;
    float Combustivel;
}DadosSonda;


void InicializarSonda(DadosSonda *sonda, int id, tlistarocha compartimento, float lat,
float lon,float capacidade, float velocidade, float combustivel);
void LigarSonda(DadosSonda *sonda);
void DesligarSonda(DadosSonda *sonda);
void MoverSonda(DadosSonda *sonda, float latitude, float longitude);
void ExibirStatusSonda(DadosSonda *sonda);
tlistarocha get_compartimento(DadosSonda *sonda);


#endif