#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Rocha.h"
#define zero 0
#define um 1
#define dois 2
#define tres 3

void InicializaRocha(rochamineral *rocha, int id, float peso, char *categoria, char *dataColeta, double latitude, double longitude)
{
    setIdentificador(rocha, id);
    setPeso(rocha, peso);
    setCategoria(rocha, categoria);
    setDataColeta(rocha, dataColeta);
    setLocalizacao(rocha, latitude, longitude);
}

char *Categoria(rochamineral *rocha)
{
    int i;
    int qtdMinerais = rocha->L_Mineral.pUltimo;

    if (qtdMinerais == zero)
    {
        strcpy(rocha->categoria, "Sem Minerais");
        return rocha->categoria;
    }

    int temFerrolita = zero;
    int temSolarium = zero;
    int temAquavitae = zero;
    int temTerranita = zero;
    int temCalaris = zero;

    for (i = rocha->L_Mineral.pPrimeiro; i < rocha->L_Mineral.pUltimo; i++)
    {
        if (strcmp(rocha->L_Mineral.ListaMINERAIS[i].nome, "Ferrolita") == zero)
        {
            temFerrolita = um;
        }
        else if (strcmp(rocha->L_Mineral.ListaMINERAIS[i].nome, "Solarium") == zero)
        {
            temSolarium = um;
        }
        else if (strcmp(rocha->L_Mineral.ListaMINERAIS[i].nome, "Aquavitae") == zero)
        {
            temAquavitae = um;
        }
        else if (strcmp(rocha->L_Mineral.ListaMINERAIS[i].nome, "Terranita") == zero)
        {
            temTerranita = um;
        }
        else if (strcmp(rocha->L_Mineral.ListaMINERAIS[i].nome, "Calaris") == zero)
        {
            temCalaris = um;
        }
    }

    if (temFerrolita && qtdMinerais == um)
    {
        strcpy(rocha->categoria, "Ferrom");
    }
    else if (temSolarium && qtdMinerais == um)
    {
        strcpy(rocha->categoria, "Solaris");
    }
    else if (temFerrolita && temAquavitae && qtdMinerais == dois)
    {
        strcpy(rocha->categoria, "Aquaferro");
    }
    else if (temTerranita && temCalaris && qtdMinerais == dois)
    {
        strcpy(rocha->categoria, "Terrolis");
    }
    else if (temTerranita && temSolarium && qtdMinerais == dois)
    {
        strcpy(rocha->categoria, "Terrasol");
    }
    else if (temAquavitae && temTerranita && qtdMinerais == dois)
    {
        strcpy(rocha->categoria, "Aquaterra");
    }
    else if (temCalaris && temAquavitae && qtdMinerais == dois)
    {
        strcpy(rocha->categoria, "Calquer");
    }
    else if (temSolarium && temFerrolita && qtdMinerais == dois)
    {
        strcpy(rocha->categoria, "Solarisfer");
    }
    else if (temTerranita && temFerrolita && qtdMinerais == dois)
    {
        strcpy(rocha->categoria, "Terralis");
    }
    else if (temAquavitae && temCalaris && temFerrolita && qtdMinerais == tres)
    {
        strcpy(rocha->categoria, "Aquacalis");
    }
    else
    {
        strcpy(rocha->categoria, "Desconhecida");
    }

    return rocha->categoria;
}

void setIdentificador(rochamineral *rocha, int id)
{
    rocha->id = id;
}
void setPeso(rochamineral *rocha, float peso)
{
    rocha->peso = peso;
}
void setCategoria(rochamineral *rocha, char *categoria)
{
    strcpy(rocha->categoria, categoria);
}
void setDataColeta(rochamineral *rocha, char *dataColeta)
{
    strcpy(rocha->dataColeta, dataColeta);
}
void setLocalizacao(rochamineral *rocha, double latitude, double longitude)
{
    rocha->latitude = latitude;
    rocha->longitude = longitude;
}

int getIdentificador(rochamineral *rocha)
{
    return rocha->id;
}
float getPeso(rochamineral *rocha)
{
    return rocha->peso;
}
char *getCategoria(rochamineral *rocha)
{
    return rocha->categoria;
}
char *getDataColeta(rochamineral *rocha)
{
    return rocha->dataColeta;
}
double getLatitude(rochamineral *rocha)
{
    return rocha->latitude;
}
double getLongitude(rochamineral *rocha)
{
    return rocha->longitude;
}