#ifndef MINERAL_H
#define MINERAL_H
#define MAXTAMMI 50
typedef struct
{
    char nome[MAXTAMMI];
    char cor[MAXTAMMI];
    double reatividade, dureza;
} Mineral;

void InicializaMineral(Mineral *mineral, char *nome, char *cor, double dureza, double reatividade);

void Lis_Minerais(Mineral *mineral, char *nome);

char *getNome(Mineral *mineral);
char *getCor(Mineral *mineral);
double getDureza(Mineral *mineral);
double getReatividade(Mineral *mineral);

////////////

void setNome(Mineral *mineral, char *nome);
void setCor(Mineral *mineral, char *cor);
void setReatividade(Mineral *mineral, double reatividade);
void setDureza(Mineral *mineral, double dureza);

#endif