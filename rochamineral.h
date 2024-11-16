#ifndef ROCHAMINERAL_H
#define ROCHAMINERAL_H
#include "listamineral.h"

typedef struct{
    int dia, mes, ano;
}data;
typedef struct{
    float latituderocha, longituderocha;
}localizacao;

typedef struct{
    int idrocha;
    float peso;
    char categoria[50];
    data data;
    localizacao localizacao;
    tlistamineral listamineral;
}rochamineral;


void inicializarocha(rochamineral *rocha, int idrocha,float peso,char *categoria,data *data, localizacao *localizacao, tlistamineral *listamineral);
 void set_idrocha(rochamineral *rocha, int idrocha);
 void set_peso(rochamineral *rocha, float peso);
 void set_categoria(rochamineral *rocha, char* categoria);
 void set_data(rochamineral *rocha, data *data);
 void set_localizacao(rochamineral *rocha, localizacao *localizacao);
 void set_listamineral(rochamineral *rocha, tlistamineral *listamineral);

int get_idrocha(rochamineral *rocha);
float get_peso(rochamineral *rocha);
char* get_categoria(rochamineral *rocha);
data get_data(rochamineral *rocha);
localizacao get_localizacao(rochamineral *rocha);
tlistamineral get_listamineral(rochamineral *rocha);
void classifica_categoria(rochamineral* rocha, int qtdMinerais, tlistamineral* lista_m);



#endif