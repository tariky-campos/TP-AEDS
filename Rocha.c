#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Rocha.h"
#define zero 0
#define um 1
#define dois 2
#define tres 3

void InicializaRocha(rochamineral *rocha, int id, float peso, char *categoria, char *data, double latitude, double longitude)
{
    setIdentificador(rocha, id);
    setPeso(rocha, peso);
    setCategoria(rocha, categoria);
    setData(rocha, data);
    setLocalizacao(rocha, latitude, longitude);
}

char *Categoria(rochamineral *rocha)
{
    int NumMine = rocha->L_Mineral.pUltimo;
    if (NumMine == zero)
    {
        strcpy(rocha->categoria, "Sem Minerais");
        return rocha->categoria;
    }
    int ferrolita = zero, solarium = zero, aquavitae = zero, terranita = zero, calaris = zero;

    for (int i = rocha->L_Mineral.pPrimeiro; i < rocha->L_Mineral.pUltimo; i++)
    {
        if (strcmp(rocha->L_Mineral.ListaMINERAIS[i].nome, "Ferrolita") == zero)
        {
            ferrolita = um;
        }
        else if (strcmp(rocha->L_Mineral.ListaMINERAIS[i].nome, "Solarium") == zero)
        {
            solarium = um;
        }
        else if (strcmp(rocha->L_Mineral.ListaMINERAIS[i].nome, "Aquavitae") == zero)
        {
            aquavitae = um;
        }
        else if (strcmp(rocha->L_Mineral.ListaMINERAIS[i].nome, "Terranita") == zero)
        {
            terranita = um;
        }
        else if (strcmp(rocha->L_Mineral.ListaMINERAIS[i].nome, "Calaris") == zero)
        {
            calaris = um;
        }
    }

    if (ferrolita && NumMine == um)
    {
        strcpy(rocha->categoria, "Ferrom");
    }
    else if (solarium && NumMine == um)
    {
        strcpy(rocha->categoria, "Solaris");
    }
    else if (ferrolita && aquavitae && NumMine == dois)
    {
        strcpy(rocha->categoria, "Aquaferro");
    }
    else if (terranita && calaris && NumMine == dois)
    {
        strcpy(rocha->categoria, "Terrolis");
    }
    else if (terranita && solarium && NumMine == dois)
    {
        strcpy(rocha->categoria, "Terrasol");
    }
    else if (aquavitae && terranita && NumMine == dois)
    {
        strcpy(rocha->categoria, "Aquaterra");
    }
    else if (calaris && aquavitae && NumMine == dois)
    {
        strcpy(rocha->categoria, "Calquer");
    }
    else if (solarium && ferrolita && NumMine == dois)
    {
        strcpy(rocha->categoria, "Solarisfer");
    }
    else if (terranita && ferrolita && NumMine == dois)
    {
        strcpy(rocha->categoria, "Terralis");
    }
    else if (aquavitae && calaris && ferrolita && NumMine == tres)
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
void setData(rochamineral *rocha, char *data)
{
    strcpy(rocha->data, data);
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
char *getData(rochamineral *rocha)
{
    return rocha->data;
}
double getLatitude(rochamineral *rocha)
{
    return rocha->latitude;
}
double getLongitude(rochamineral *rocha)
{
    return rocha->longitude;
}