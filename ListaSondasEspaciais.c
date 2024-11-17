#include "ListaSondasEspaciais.h"
#include <stdio.h>
#include <stdlib.h>
#include <float.h>

void FLvazia(Tlista *lista) {
    lista->pPrimeiro = (Apontador)malloc(sizeof(TCelula));
    lista->pPrimeiro->pProx = NULL;
    lista->pUltimo = lista->pPrimeiro;
    lista->numSondas = 0;  
}

int LehVazia(Tlista *lista) {
    return (lista->pPrimeiro == lista->pUltimo);
}

int Linsere(Tlista *lista, DadosSonda *sonda) {
    lista->pUltimo->pProx = (Apontador)malloc(sizeof(TCelula));
    if (lista->pUltimo->pProx == NULL) return 0;
    lista->pUltimo = lista->pUltimo->pProx;
    lista->pUltimo->sonda = *sonda;
    lista->pUltimo->pProx = NULL;
    lista->numSondas++; 
    return 1; 
}

int Retira(Tlista *lista, DadosSonda *pGuardar) {
    if (LehVazia(lista))
        return 0; 

    TCelula *pAux = lista->pPrimeiro->pProx;
    *pGuardar = pAux->sonda;
    lista->pPrimeiro->pProx = pAux->pProx;
    
    if (pAux == lista->pUltimo)
        lista->pUltimo = lista->pPrimeiro;
    
    lista->numSondas--; 
    free(pAux);
    return 1; 
}

void Imprime(Tlista *lista) {
    Apontador pAux = lista->pPrimeiro->pProx;
    while (pAux != NULL) {
        printf("\nID: %d\n", pAux->sonda.Identificador);
        printf("Latitude: %.2f\n", pAux->sonda.Latitude);
        printf("Longitude: %.2f\n", pAux->sonda.Longitude);
        printf("Estado: %s\n", pAux->sonda.EstaLigada ? "LIGADA" : "DESLIGADA");
        pAux = pAux->pProx;
    }
}
void RedistribuirRochasDinamicamente(Tlista *listasondas) {
    if (LehVazia(listasondas)) {
        printf("A lista de sondas está vazia.\n");
        return;
    }

    tlistarocha lista_temp;
    flvaziarocha(&lista_temp);

    TCelula *atual = listasondas->pPrimeiro->pProx;
    while (atual != NULL) {
        DadosSonda *sonda = &atual->sonda;
        RemoverTodasRochas(&sonda->compartimento, &lista_temp);
        atual = atual->pProx;
    }

    while (!lehvaziarocha(&lista_temp)) {
        rochamineral rocha;
        RemoverPrimeiraRocha(&lista_temp, &rocha);

        DadosSonda *sondaMaisApropriada = NULL;
        float menorDistancia = FLT_MAX;
        float menorCarga = FLT_MAX;

        atual = listasondas->pPrimeiro->pProx;
        while (atual != NULL) {
            DadosSonda *sonda = &atual->sonda;


            float pesoAtual = PesoTotal(&sonda->compartimento);
            if (pesoAtual + rocha.peso <= sonda->Capacidade) {
    
                float distancia = CalcularDistancia(
                    rocha.localizacao.latituderocha,
                    rocha.localizacao.longituderocha,
                    sonda->Latitude,
                    sonda->Longitude
                );

             
                if (distancia < menorDistancia || 
                   (distancia == menorDistancia && pesoAtual < menorCarga)) {
                    menorDistancia = distancia;
                    menorCarga = pesoAtual;
                    sondaMaisApropriada = sonda;
                }
            }

            atual = atual->pProx;
        }

   
        if (sondaMaisApropriada != NULL) {
            linsererocha(&sondaMaisApropriada->compartimento, &rocha);
            MoverSonda(
                sondaMaisApropriada,
                rocha.localizacao.latituderocha,
                rocha.localizacao.longituderocha
            );
        } else {
            printf("Nenhuma sonda disponível para receber a rocha (peso: %.2f).\n", rocha.peso);
        }
    }

  
    atual = listasondas->pPrimeiro->pProx;
    while (atual != NULL) {
        DadosSonda *sonda = &atual->sonda;
        OrdenarRochas(&sonda->compartimento);
        atual = atual->pProx;
    }

    printf("Redistribuicao dinamica concluida.\n");
}
void OrdenarRochas(tlistarocha *lista) {
    if (lista->pprimeiro == NULL || lista->pprimeiro->pprox == NULL)
        return;

    tcelula *i, *j;
    for (i = lista->pprimeiro->pprox; i != NULL; i = i->pprox) {
        for (j = i->pprox; j != NULL; j = j->pprox) {
            if (i->rocha.idrocha > j->rocha.idrocha) { 
               
                rochamineral temp = i->rocha;
                i->rocha = j->rocha;
                j->rocha = temp;
            }
        }
    }
}

void RemoverPrimeiraRocha(tlistarocha *lista, rochamineral *rocha) {
    if (lehvaziarocha(lista)) return; 

    tcelula *aux = lista->pprimeiro->pprox; 
    *rocha = aux->rocha;                           

    lista->pprimeiro->pprox = aux->pprox;        
    if (aux->pprox == NULL)                       
        lista->pultimo = lista->pprimeiro;       

    free(aux);                                  
}
void RemoverTodasRochas(tlistarocha *origem, tlistarocha *destino) {
    while (!lehvaziarocha(origem)) {              
        rochamineral rocha;
        RemoverPrimeiraRocha(origem, &rocha);     
        linsererocha(destino, &rocha);          
    }
}
float CalcularDistancia(float lat1, float lon1, float lat2, float lon2) {
    return sqrt(pow(lat2 - lat1, 2) + pow(lon2 - lon1, 2));
}

void MoverSondasParaOrigem(Tlista *listasondas) {
    if (LehVazia(listasondas)) {
        printf("A lista de sondas esta vazia.\n");
        return;
    }

    TCelula *atual = listasondas->pPrimeiro->pProx;
    while (atual != NULL) {
        DadosSonda *sonda = &atual->sonda;
        float distancia = sqrt(pow(sonda->Latitude, 2) + pow(sonda->Longitude, 2));
        float consumo = distancia / sonda->Velocidade;

        if (sonda->Combustivel >= consumo) {
            sonda->Latitude = 0.0;
            sonda->Longitude = 0.0;
            sonda->Combustivel -= consumo;
            printf("Sonda %d movida para a origem (0,0). Combustivel restante: %.2f\n", 
                   sonda->Identificador, sonda->Combustivel);
        } else {
            printf("Sonda %d não possui combustivel suficiente para se mover para a origem.\n", 
                   sonda->Identificador);
        }
        atual = atual->pProx;
    }
}
DadosSonda* EncontrarSondaMaisProxima(Tlista *listasondas, float latitude, float longitude) {
    if (LehVazia(listasondas)) {
        printf("A lista de sondas esta vazia.\n");
        return NULL;
    }

    TCelula *atual = listasondas->pPrimeiro->pProx; 
    DadosSonda *sondaMaisProxima = NULL;
    float menorDistancia = FLT_MAX;

   
    while (atual != NULL) {
        DadosSonda *sonda = &atual->sonda;

        float distancia = CalcularDistancia(latitude, longitude, sonda->Latitude, sonda->Longitude);

       
        if (distancia < menorDistancia) {
            menorDistancia = distancia;
            sondaMaisProxima = sonda;
        }

        atual = atual->pProx;
    }

    return sondaMaisProxima;
}

void AdicionarRochaNaSondaMaisProxima(Tlista *listasondas, rochamineral *novaRocha) {
    if (LehVazia(listasondas)) {
        printf("A lista de sondas esta vazia.\n");
        return;
    }

    TCelula *atual = listasondas->pPrimeiro->pProx;
    DadosSonda *sondaMaisProxima = NULL;
    float menorDistancia = FLT_MAX;

    while (atual != NULL) {
        DadosSonda *sonda = &atual->sonda;

       
        float distancia = CalcularDistancia(
            novaRocha->localizacao.latituderocha,
            novaRocha->localizacao.longituderocha,
            sonda->Latitude,
            sonda->Longitude
        );

    
        float pesoAtual = PesoTotal(&sonda->compartimento);
        if (pesoAtual + novaRocha->peso <= sonda->Capacidade && distancia < menorDistancia) {
            menorDistancia = distancia;
            sondaMaisProxima = sonda;
        }

        atual = atual->pProx;
    }

    if (sondaMaisProxima != NULL) {
     
        MoverSonda(
            sondaMaisProxima,
            novaRocha->localizacao.latituderocha,
            novaRocha->localizacao.longituderocha
        );

  
        linsererocha(&sondaMaisProxima->compartimento, novaRocha);

        printf("Rocha adicionada a sonda %d (Peso Atual: %.2f, Capacidade Maxima: %.2f)\n\n", 
               sondaMaisProxima->Identificador, 
               PesoTotal(&sondaMaisProxima->compartimento),
               sondaMaisProxima->Capacidade);
    } else {
        printf("Nenhuma sonda disponivel ou com capacidade suficiente para adicionar a rocha.\n");
    }
}

