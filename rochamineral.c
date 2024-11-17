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

void DefinirCategoriaPorMinerais(rochamineral *rocha, const char *mineral1, const char *mineral2, const char *mineral3) {
    if ((mineral2 == NULL || strcmp(mineral2, "") == 0) && (mineral3 == NULL || strcmp(mineral3, "") == 0)) {
        // Caso apenas um mineral seja fornecido
        if (strcmp(mineral1, "Aquavitae") == 0) {
            strcpy(rocha->categoria, "Aqua Pura");
        } else if (strcmp(mineral1, "Ferrolita") == 0) {
            strcpy(rocha->categoria, "Ferrom");
        } else if (strcmp(mineral1, "Terranita") == 0) {
            strcpy(rocha->categoria, "Terra Pura");
        } else if (strcmp(mineral1, "Solarium") == 0) {
            strcpy(rocha->categoria, "Solaris");
        } else if (strcmp(mineral1, "Calaris") == 0) {
            strcpy(rocha->categoria, "Calaris");
        } else {
            strcpy(rocha->categoria, "Sem Categoria");
        }
    } else if (mineral3 == NULL || strcmp(mineral3, "") == 0) {
        // Caso dois minerais sejam fornecidos
        if ((strcmp(mineral1, "Aquavitae") == 0 && strcmp(mineral2, "Terranita") == 0) ||
            (strcmp(mineral2, "Aquavitae") == 0 && strcmp(mineral1, "Terranita") == 0)) {
            strcpy(rocha->categoria, "Aquaterra");
        } else if ((strcmp(mineral1, "Aquavitae") == 0 && strcmp(mineral2, "Ferrolita") == 0) ||
                   (strcmp(mineral2, "Aquavitae") == 0 && strcmp(mineral1, "Ferrolita") == 0)) {
            strcpy(rocha->categoria, "Aquaferro");
        } else if ((strcmp(mineral1, "Ferrolita") == 0 && strcmp(mineral2, "Solarium") == 0) ||
                   (strcmp(mineral2, "Ferrolita") == 0 && strcmp(mineral1, "Solarium") == 0)) {
            strcpy(rocha->categoria, "Terrasol");
        } else if ((strcmp(mineral1, "Calaris") == 0 && strcmp(mineral2, "Terranita") == 0) ||
                   (strcmp(mineral2, "Calaris") == 0 && strcmp(mineral1, "Terranita") == 0)) {
            strcpy(rocha->categoria, "Terrolis");
        } else if ((strcmp(mineral1, "Ferrolita") == 0) && (strcmp(mineral2, "Ferrolita") == 0)) {
            strcpy(rocha->categoria, "Ferrom");
        } else if ((strcmp(mineral1, "Solarium") == 0) && (strcmp(mineral2, "Solarium") == 0)) {
            strcpy(rocha->categoria, "Solaris");
        } else if ((strcmp(mineral1, "Aquavitae") == 0 && strcmp(mineral2, "Calaris") == 0) ||
                   (strcmp(mineral2, "Aquavitae") == 0 && strcmp(mineral1, "Calaris") == 0)) {
            strcpy(rocha->categoria, "Calquer");
        } else if ((strcmp(mineral1, "Solarium") == 0 && strcmp(mineral2, "Ferrolita") == 0) ||
                   (strcmp(mineral2, "Solarium") == 0 && strcmp(mineral1, "Ferrolita") == 0)) {
            strcpy(rocha->categoria, "Solarisfer");
        } else if ((strcmp(mineral1, "Terranita") == 0 && strcmp(mineral2, "Ferrolita") == 0) ||
                   (strcmp(mineral2, "Terranita") == 0 && strcmp(mineral1, "Ferrolita") == 0)) {
            strcpy(rocha->categoria, "Terralis");
        } else {
            strcpy(rocha->categoria, "Sem Categoria");
        }
    } else {
        // Caso três minerais sejam fornecidos
        int temAquavitae = (strcmp(mineral1, "Aquavitae") == 0 || strcmp(mineral2, "Aquavitae") == 0 || strcmp(mineral3, "Aquavitae") == 0);
        int temCalaris = (strcmp(mineral1, "Calaris") == 0 || strcmp(mineral2, "Calaris") == 0 || strcmp(mineral3, "Calaris") == 0);
        int temFerrolita = (strcmp(mineral1, "Ferrolita") == 0 || strcmp(mineral2, "Ferrolita") == 0 || strcmp(mineral3, "Ferrolita") == 0);

        if (temAquavitae && temCalaris && temFerrolita) {
            strcpy(rocha->categoria, "Aquacalis");
        } else {
            strcpy(rocha->categoria, "Sem Categoria");
        }
    }

    printf("Mineral 1: %s, Mineral 2: %s, Mineral 3: %s\n", mineral1,
           (mineral2 && strcmp(mineral2, "") != 0) ? mineral2 : "Nenhum",
           (mineral3 && strcmp(mineral3, "") != 0) ? mineral3 : "Nenhum");
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