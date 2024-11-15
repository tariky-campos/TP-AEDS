#ifndef MINERAL_H
#define MINERAL_H

typedef struct{
    char nome[100];
    float dureza;
    float reatividade;
    char cor[50];
}Minerais; 

char* get_nome(Minerais *min);
float get_dureza(Minerais *min);
float get_reatividade(Minerais *min);
char* get_cor(Minerais *min);

void set_nome(Minerais *min, char* nome);
void set_dureza(Minerais *min, float dureza);
void set_reatividade(Minerais *min, float reatividade);
void set_cor(Minerais *min, char* cor);
void inicializar(Minerais *min, char* nome, float dureza, float reatividade, char* cor);
void RetornaMineral(Minerais* min,char* nome);
#endif
