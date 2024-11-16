#include <stdio.h>
#include <stdlib.h>
#include "rochamineral.h"
#include <string.h>

void inicializarocha(rochamineral *rocha, int idrocha,float peso,char *categoria,data *data, localizacao *localizacao, tlistamineral *mineral){
    (void)mineral;
    set_idrocha(rocha, idrocha);
    set_peso(rocha, peso);
    set_categoria(rocha, categoria);
    set_data(rocha, data);
    set_localizacao(rocha, localizacao);
}

char* DefCategoria(rochamineral* rocha){
    int i;
    int qtdMinerais = rocha->listamineral.Ultimo - rocha->listamineral.Primeiro;
    if(qtdMinerais == 0){
        strcpy(rocha->categoria, "Sem Minerais");
        return rocha->categoria;
    }

    int temFerrolita = 0;
    int temSolarium = 0;
    int temAquavitae = 0;
    int temTerranita = 0;
    int temCalaris = 0;

    for(i = rocha->listamineral.Primeiro; i < rocha->listamineral.Ultimo; i++){
       if(strcmp(rocha->listamineral.Item[i].mineral.nome, "Ferrolita") == 0) {temFerrolita = 1;}
       else if(strcmp(rocha->listamineral.Item[i].mineral.nome, "Solarium") == 0) {temSolarium = 1;}
       else if(strcmp(rocha->listamineral.Item[i].mineral.nome, "Aquavitae") == 0) {temAquavitae = 1;}
       else if(strcmp(rocha->listamineral.Item[i].mineral.nome, "Terranita") == 0) {temTerranita = 1;}
       else if(strcmp(rocha->listamineral.Item[i].mineral.nome, "Calaris") == 0) {temCalaris = 1;}
    }

    if(temFerrolita && qtdMinerais == 1) {strcpy(rocha->categoria, "Ferrom");}
    else if(temSolarium && qtdMinerais == 1) {strcpy(rocha->categoria, "Solaris");}
    else if(temFerrolita && temAquavitae && qtdMinerais == 2) {strcpy(rocha->categoria, "Aquaferro");}
    else if(temCalaris && temTerranita && qtdMinerais == 2) {strcpy(rocha->categoria, "Terrolis");}
    else if(temFerrolita && temSolarium && qtdMinerais == 2) {strcpy(rocha->categoria, "Terrasol");}
    else if(temAquavitae && temTerranita && qtdMinerais == 2) {strcpy(rocha->categoria, "Aquaterra");}
    else if(temCalaris && temAquavitae && qtdMinerais == 2) {strcpy(rocha->categoria, "Calquer");}
    else if(temSolarium && temFerrolita && qtdMinerais == 2) {strcpy(rocha->categoria, "Solarisfer");}
    else if(temTerranita && temFerrolita && qtdMinerais == 2) {strcpy(rocha->categoria, "Terralis");}
    else if(temAquavitae && temCalaris && temFerrolita && qtdMinerais == 3) {strcpy(rocha->categoria, "Aquacalis");}
    return rocha->categoria;
}


void set_idrocha(rochamineral *rocha, int idrocha){
    rocha->idrocha=idrocha;
}
 void set_peso(rochamineral *rocha, float peso){
    rocha->peso=peso;
 }
 void set_categoria(rochamineral *rocha, char* categoria){
    strcpy(rocha->categoria, categoria);
 }
 void set_data(rochamineral *rocha, data *data){
    rocha->data= *data;
 }
 void set_localizacao(rochamineral *rocha, localizacao *localizacao){
    rocha->localizacao= *localizacao;
 }
 void set_listamineral(rochamineral *rocha, tlistamineral *listamineral){
    rocha->listamineral= *listamineral;
 }

 int get_idrocha(rochamineral *rocha){
    return rocha->idrocha;
 }
float get_peso(rochamineral *rocha){
    return rocha->peso;
}
char* get_categoria(rochamineral *rocha){
    return rocha->categoria;
}
data get_data(rochamineral *rocha){
    return rocha->data;
}
localizacao get_localizacao(rochamineral *rocha){
    return rocha->localizacao;
}
tlistamineral get_listamineral(rochamineral *rocha){
    return rocha->listamineral;
}