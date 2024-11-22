#include "ListaSondasEspaciais.h"
#include <stdio.h>
#include <stdlib.h>
#include <float.h>

void FLvazia(Tlista *lista) {
    lista->pPrimeiro = (Apontador)malloc(sizeof(TCelula));
    lista->pPrimeiro->pProx = NULL;
    lista->pUltimo = lista->pPrimeiro;
    lista->numSondas = 0;  
}// faz lista fazia

int LehVazia(Tlista *lista) {
    return (lista->pPrimeiro == lista->pUltimo);
}// confere se a lista esta vazia

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

void RemoverTodasRochas(tlistarocha *origem, tlistarocha *destino) {
    while (!lehvaziarocha(origem)) {              
        rochamineral rocha;
        RemoverPrimeiraRocha(origem, &rocha);     
        linsererocha(destino, &rocha);          
    }
}
float CalcularDistancia(float lat1, float lon1, float lat2, float lon2) {
    return sqrt(pow(lat2 - lat1, 2) + pow(lon2 - lon1, 2));//calcula a distância euclidiana entre dois pontos geográficos
}

void MoverSondasParaOrigem(Tlista *listasondas) {//move todas as sondas para (0,0) 
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
    if (LehVazia(listasondas)) { //confere  se a lista esta vazia
        printf("A lista de sondas esta vazia.\n");
        return NULL;
    }
    
    TCelula *atual = listasondas->pPrimeiro->pProx; 
    // cria variáveis para armazenar a sonda mais próxima e a menor distância
    DadosSonda *sondaMaisProxima = NULL;
    float menorDistancia = FLT_MAX; //inicializa com o valor máximo possível

   
    while (atual != NULL) {//percorre a lista de sondas
        DadosSonda *sonda = &atual->sonda;//trata da sonda atual

        float distancia = CalcularDistancia(latitude, longitude, sonda->Latitude, sonda->Longitude);

       //confere e atualiza a menor distancia e a sonda mais proxima
        if (distancia < menorDistancia) {
            menorDistancia = distancia;
            sondaMaisProxima = sonda;
        }

        atual = atual->pProx;
    }

    return sondaMaisProxima; //retorna a sonda mais proxima
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

        //calcula a distancia entre a localização da rocha e a sonda atual.
        float distancia = CalcularDistancia(
            novaRocha->localizacao.latituderocha,
            novaRocha->localizacao.longituderocha,
            sonda->Latitude,
            sonda->Longitude
        );

        //calcula o peso atual no compartimento da sonda
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
        );//move a sonda para a localizacao da rocha

        //insere a rocha no compartimento da sonda.
        linsererocha(&sondaMaisProxima->compartimento, novaRocha);

        printf("Rocha adicionada a sonda %d (Peso Atual: %.2f, Capacidade Maxima: %.2f)\n\n", 
               sondaMaisProxima->Identificador, 
               PesoTotal(&sondaMaisProxima->compartimento),
               sondaMaisProxima->Capacidade);
    } else {
        printf("Nenhuma sonda disponivel ou com capacidade suficiente para adicionar a rocha.\n");
    }
}
int ContarRochas(tlistarocha *listaRochas) {
    if (lehvaziarocha(listaRochas)) {
        return 0; // Se a lista de rochas está vazia, retorna 0
    }

    int contador = 0;
    Apontador_c atual = listaRochas->pprimeiro->pprox;

    while (atual != NULL) {
        contador++;
        atual = atual->pprox;
    }

    return contador;
}//conta a quantidade de rochas

void OperacaoI(Tlista *listasondas) {
    if (LehVazia(listasondas)) {
        printf("A lista de sondas esta vazia.\n");
    } else {
        TCelula *atual = listasondas->pPrimeiro->pProx;
        while (atual != NULL) {//percorre as sondas
            DadosSonda *sonda = &atual->sonda;
            printf("\n%d\n", sonda->Identificador);
            if (lehvaziarocha(&sonda->compartimento)) {
                printf("compartimento vazio!\n");
            } else {
                limprimerocha(&sonda->compartimento);//imprime o compartimento da sonda
            }
            atual = atual->pProx;
        }
        printf("\n");
    }
}
void OperacaoE(Tlista *listasondas) {
    if (LehVazia(listasondas)) {
        printf("A lista de sondas está vazia.\n");
        return;
    }

    printf("Executando redistribuicao equilibrada de rochas...\n");

    int houveRedistribuicao = 1; // Variável para acompanhar se redistribuições ocorrem

    while (houveRedistribuicao) {
        houveRedistribuicao = 0; // Reseta a flag

        TCelula *atualCheia = listasondas->pPrimeiro->pProx;

        // Encontra uma sonda cheia (com 2 ou mais rochas)
        while (atualCheia != NULL) {
            DadosSonda *sondaCheia = &atualCheia->sonda;
            int totalRochasCheia = ContarRochas(&sondaCheia->compartimento);

            if (totalRochasCheia >= 2) {
                // Encontra uma sonda livre (com 0 rochas)
                TCelula *atualLivre = listasondas->pPrimeiro->pProx;
                while (atualLivre != NULL) {
                    DadosSonda *sondaLivre = &atualLivre->sonda;
                    int totalRochasLivre = ContarRochas(&sondaLivre->compartimento);

                    if (totalRochasLivre == 0) {
                        // Remove uma rocha da sonda cheia
                        rochamineral rochaTransferida;
                        RemoverPrimeiraRocha(&sondaCheia->compartimento, &rochaTransferida);

                        // Insere a rocha na sonda livre
                        linsererocha(&sondaLivre->compartimento, &rochaTransferida);
                        MoverSonda(
                            sondaLivre,
                            rochaTransferida.localizacao.latituderocha,
                            rochaTransferida.localizacao.longituderocha
                        );

                        printf("Rocha transferida da sonda %d para a sonda %d.\n",
                               sondaCheia->Identificador,
                               sondaLivre->Identificador);

                        houveRedistribuicao = 1; // Indica que uma redistribuição ocorreu
                        break;
                    }
                    atualLivre = atualLivre->pProx;
                }
            }

            // Se houve redistribuição, reinicia o loop para reavaliar
            if (houveRedistribuicao) {
                break;
            }

            atualCheia = atualCheia->pProx;
        }
    }

    // Exibe o estado final das sondas
    printf("Redistribuicao equilibrada concluida. Estado atualizado das sondas:\n");
    TCelula *atual = listasondas->pPrimeiro->pProx;
    while (atual != NULL) {
        DadosSonda *sonda = &atual->sonda;
        int totalRochas = ContarRochas(&sonda->compartimento);
        printf("Sonda %d: %d rochas\n", sonda->Identificador, totalRochas);
        limprimerocha(&sonda->compartimento); // Exibe as rochas
        atual = atual->pProx;
    }
}
