#include <stdio.h>
#include <string.h>
#include "mineral.h"
void inicializar(Minerais *min, char *nome, float dureza, float reatividade, char *cor){
    strcpy(min->nome, nome);
    min->dureza=dureza;
    min->reatividade=reatividade; 
    strcpy(min->cor, cor);
}

void RetornaMineral(Minerais* min, char* nome){
    int x=1;
    while (x)
    {
        if (strcmp(nome, "Ferrolita") == 0) {
        strcpy(min->nome, "Ferrolita");
        strcpy(min->cor, "Acinzentado");
        min->dureza = 0.5;
        min->reatividade = 0.7;  
        x=0;
    }
    else if (strcmp(nome, "Solarium") == 0) {
        strcpy(min->nome, "Solarium");
        strcpy(min->cor,"Amarelo");
        min->dureza = 0.9;
        min->reatividade = 0.2;
        x=0;
    }
    else if (strcmp(nome, "Aquavitae") == 0) {
        strcpy(min->nome, "Aquavitae");
        strcpy(min->cor,"Azulado");
        min->dureza = 0.5;
        min->reatividade = 0.8;
        x=0;
    }
    else if (strcmp(nome, "Terranita") == 0) {
        strcpy(min->nome, "Terranita");
        strcpy(min->cor,"Marrom");
        min->dureza = 0.7;
        min->reatividade = 0.6;
        x=0;
    }
    else if(strcmp(nome, "Calaris") == 0) {
        strcpy(min->nome, "Calaris");
        strcpy(min->cor, "Vermelho");
        min->dureza = 0.6;
        min->reatividade = 0.5;
        x=0;
    }
    else{
        printf("Pedra inválida, digite novamente:");
        scanf("%s",nome);  
    }   
    }
}
char* get_nome(Minerais *min) {
    return min->nome;
}
float get_dureza(Minerais *min) {
    return min->dureza;
}
float get_reatividade(Minerais *min) {
    return min->reatividade;
}
char* get_cor(Minerais *min) {
    return min->cor;
}
void set_nome(Minerais *min, char* nome){
    strcpy(min->nome, nome);
}
void set_dureza(Minerais *min, float dureza){
    min->dureza = dureza;
}
void set_reatividade(Minerais *min, float reatividade){
    min->reatividade = reatividade;
}
void set_cor(Minerais *min, char* cor){
    strcpy(min->cor, cor);
}