#ifndef ROCHAMINERAL_H
#define ROCHAMINERAL_H
#include "L_Mineral.h"

typedef struct
{
    int id;
    float peso;
    char categoria[40];
    char dataColeta[20];
    double latitude;
    double longitude;
    L_Minerais L_Mineral;

} rochamineral;

void InicializaRocha(rochamineral *rocha, int id, float peso, char *categoria, char *dataColeta, double latitude, double longitude);
char *DefCategoria(rochamineral *rocha);

int getIdentificador(rochamineral *rocha);
float getPeso(rochamineral *rocha);
char *getCategoria(rochamineral *rocha);
char *getDataColeta(rochamineral *rocha);
double getLatitude(rochamineral *rocha);
double getLongitude(rochamineral *rocha);

void setIdentificador(rochamineral *rocha, int id);
void setPeso(rochamineral *rocha, float peso);
void setCategoria(rochamineral *rocha, char *categoria);
void setDataColeta(rochamineral *rocha, char *dataColeta);
void setLocalizacao(rochamineral *rocha, double latitude, double longitude);

#endif