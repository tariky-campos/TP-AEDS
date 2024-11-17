#include "DadosSonda.h"
#include <stdio.h>
#include <stdlib.h>

void InicializarSonda(DadosSonda *sonda, int id,float lat, float lon, float capacidade, float velocidade, float combustivel) {
    sonda->Identificador = id;
    sonda->Latitude = lat;
    sonda->Longitude = lon;
    sonda->EstaLigada = 0;
    sonda->Capacidade = capacidade;
    sonda->Velocidade = velocidade;
    sonda->Combustivel = combustivel;
    flvaziarocha(&sonda->compartimento);
}
tlistarocha get_compartimento(DadosSonda *sonda){
    return (sonda->compartimento);
}

void LigarSonda(DadosSonda *sonda) {
    sonda->EstaLigada = 1;
}


void DesligarSonda(DadosSonda *sonda) {
    sonda->EstaLigada = 0;
}


void MoverSonda(DadosSonda *sonda, float novaLat, float novaLon) {
        sonda->Latitude = novaLat;
        sonda->Longitude = novaLon;
}

void ExibirStatusSonda(DadosSonda *sonda) {
    printf("ID: %d\n", sonda->Identificador);
    printf("Latitude: %.2f\n", sonda->Latitude);
    printf("Longitude: %.2f\n", sonda->Longitude);
    printf("Estado: %s\n", sonda->EstaLigada ? "LIGADA" : "DESLIGADA");
    printf("Capacidade: %.2f kg\n", sonda->Capacidade);
    printf("Velocidade: %.2f\n", sonda->Velocidade);
    printf("Combustivel: %.2f\n", sonda->Combustivel);
}

