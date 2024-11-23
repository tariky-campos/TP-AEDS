#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Rocha.h"

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

    if (qtdMinerais == 0)
    {
        strcpy(rocha->categoria, "Sem Minerais");
        return rocha->categoria;
    }

    int temFerrolita = 0;
    int temSolarium = 0;
    int temAquavitae = 0;
    int temTerranita = 0;
    int temCalaris = 0;

    for (i = rocha->L_Mineral.pPrimeiro; i < rocha->L_Mineral.pUltimo; i++)
    {
        if (strcmp(rocha->L_Mineral.ListaMINERAIS[i].nome, "Ferrolita") == 0)
        {
            temFerrolita = 1;
        }
        else if (strcmp(rocha->L_Mineral.ListaMINERAIS[i].nome, "Solarium") == 0)
        {
            temSolarium = 1;
        }
        else if (strcmp(rocha->L_Mineral.ListaMINERAIS[i].nome, "Aquavitae") == 0)
        {
            temAquavitae = 1;
        }
        else if (strcmp(rocha->L_Mineral.ListaMINERAIS[i].nome, "Terranita") == 0)
        {
            temTerranita = 1;
        }
        else if (strcmp(rocha->L_Mineral.ListaMINERAIS[i].nome, "Calaris") == 0)
        {
            temCalaris = 1;
        }
    }

    if (temFerrolita && qtdMinerais == 1)
    {
        strcpy(rocha->categoria, "Ferrom");
    }
    else if (temSolarium && qtdMinerais == 1)
    {
        strcpy(rocha->categoria, "Solaris");
    }
    else if (temFerrolita && temAquavitae && qtdMinerais == 2)
    {
        strcpy(rocha->categoria, "Aquaferro");
    }
    else if (temTerranita && temCalaris && qtdMinerais == 2)
    {
        strcpy(rocha->categoria, "Terrolis");
    }
    else if (temTerranita && temSolarium && qtdMinerais == 2)
    {
        strcpy(rocha->categoria, "Terrasol");
    }
    else if (temAquavitae && temTerranita && qtdMinerais == 2)
    {
        strcpy(rocha->categoria, "Aquaterra");
    }
    else if (temCalaris && temAquavitae && qtdMinerais == 2)
    {
        strcpy(rocha->categoria, "Calquer");
    }
    else if (temSolarium && temFerrolita && qtdMinerais == 2)
    {
        strcpy(rocha->categoria, "Solarisfer");
    }
    else if (temTerranita && temFerrolita && qtdMinerais == 2)
    {
        strcpy(rocha->categoria, "Terralis");
    }
    else if (temAquavitae && temCalaris && temFerrolita && qtdMinerais == 3)
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