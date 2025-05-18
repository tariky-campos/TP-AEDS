#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mineral.h"
#define zero 0

void InicializaMineral(Mineral *mineral, char *nome, char *cor, double dureza, double reatividade)
{
    setNome(mineral, nome);
    setCor(mineral, cor);
    setDureza(mineral, reatividade);
    setReatividade(mineral, dureza);
}
void Lis_Minerais(Mineral *mineral, char *nome){
    if (strcmp(nome, "Ferrolita") == zero)
    {
        strcpy(mineral->nome, "Ferrolita");
        strcpy(mineral->cor, "Acinzentado");
        mineral->dureza = 0.5;
        mineral->reatividade = 0.7;
    }
    else if (strcmp(nome, "Solarium") == zero)
    {
        strcpy(mineral->nome, "Solarium");
        strcpy(mineral->cor, "Amarelo");
        mineral->dureza = 0.9;
        mineral->reatividade = 0.2;
    }
    else if (strcmp(nome, "Aquavitae") == zero)
    {
        strcpy(mineral->nome, "Aquavitae");
        strcpy(mineral->cor, "Azulado");
        mineral->dureza = 0.5;
        mineral->reatividade = 0.8;
    }
    else if (strcmp(nome, "Terranita") == zero)
    {
        strcpy(mineral->nome, "Terranita");
        strcpy(mineral->cor, "Marrom");
        mineral->dureza = 0.7;
        mineral->reatividade = 0.6;
    }
    else if (strcmp(nome, "Calaris") == zero)
    {
        strcpy(mineral->nome, "Calaris");
        strcpy(mineral->cor, "Vermelho");
        mineral->dureza = 0.6;
        mineral->reatividade = 0.5;
    }
    else
    {
        printf("Pedra invalida, digite novamente:");
    }
}

void setNome(Mineral *mineral, char *nome)
{
    strcpy(mineral->nome, nome);
}
void setCor(Mineral *mineral, char *cor)
{
    strcpy(mineral->cor, cor);
}
void setDureza(Mineral *mineral, double dureza)
{
    mineral->dureza = dureza;
}
void setReatividade(Mineral *mineral, double reatividade)
{
    mineral->reatividade = reatividade;
}

///////////

char *getNome(Mineral *mineral)
{
    return mineral->nome;
}
char *getCor(Mineral *mineral)
{
    return mineral->cor;
}
double getDureza(Mineral *mineral)
{
    return mineral->dureza;
}
double getReatividade(Mineral *mineral)
{
    return mineral->reatividade;
}