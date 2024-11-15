#ifndef LISTAMINERAL_H
#define LISTAMINERAL_H

#include <stdio.h>
#include <stdlib.h>
#include "mineral.h"

#define InicioArranjo 0
#define MaxTam 1000
typedef int apontador_m;
typedef struct {
 Minerais mineral;
} TItem;

typedef struct {
 TItem Item[MaxTam];
 apontador_m
 Primeiro, Ultimo;
} tlistamineral;

void FLVaziamineral(tlistamineral* plistamineral);
int LEhVaziamineral(tlistamineral* plistamineral);
int LInseremineral(tlistamineral* plistamineral, TItem x);
int LRetiramineral(tlistamineral* plistamineral, apontador_m p, TItem *pX);
void LImprimemineral(tlistamineral* plistamineral);
#endif