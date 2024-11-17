#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include "ListaSondasEspaciais.h"
#include "rochamineral.h"

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



void AtualizarLocalizacaoSonda(DadosSonda *sonda, float novaLatitude, float novaLongitude) {
    sonda->Latitude = novaLatitude;
    sonda->Longitude = novaLongitude;
    printf("Sonda %d atualizada para nova localizacao: (%.6f, %.6f)\n", 
           sonda->Identificador, novaLatitude, novaLongitude);
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


float CalcularDistancia(float lat1, float lon1, float lat2, float lon2);

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


void RedistribuirRochasDinamicamente(Tlista *listasondas) {
    if (LehVazia(listasondas)) {
        printf("A lista de sondas está vazia.\n");
        return;
    }

    // Lista temporária para armazenar todas as rochas
    tlistarocha lista_temp;
    flvaziarocha(&lista_temp);

    // Remover todas as rochas das sondas para redistribuir
    TCelula *atual = listasondas->pPrimeiro->pProx;
    while (atual != NULL) {
        DadosSonda *sonda = &atual->sonda;
        RemoverTodasRochas(&sonda->compartimento, &lista_temp);
        atual = atual->pProx;
    }

    // Redistribuir rochas dinamicamente
    while (!lehvaziarocha(&lista_temp)) {
        rochamineral rocha;
        RemoverPrimeiraRocha(&lista_temp, &rocha);

        DadosSonda *sondaMaisApropriada = NULL;
        float menorDistancia = FLT_MAX;
        float menorCarga = FLT_MAX;

        // Encontrar a melhor sonda para essa rocha
        atual = listasondas->pPrimeiro->pProx;
        while (atual != NULL) {
            DadosSonda *sonda = &atual->sonda;

            // Verificar se a sonda tem capacidade suficiente
            float pesoAtual = PesoTotal(&sonda->compartimento);
            if (pesoAtual + rocha.peso <= sonda->Capacidade) {
                // Calcular a distância entre a sonda e a rocha
                float distancia = CalcularDistancia(
                    rocha.localizacao.latituderocha,
                    rocha.localizacao.longituderocha,
                    sonda->Latitude,
                    sonda->Longitude
                );

                // Escolher a sonda com base em distância e carga mais equilibrada
                if (distancia < menorDistancia || 
                   (distancia == menorDistancia && pesoAtual < menorCarga)) {
                    menorDistancia = distancia;
                    menorCarga = pesoAtual;
                    sondaMaisApropriada = sonda;
                }
            }

            atual = atual->pProx;
        }

        // Alocar a rocha na melhor sonda encontrada
        if (sondaMaisApropriada != NULL) {
            linsererocha(&sondaMaisApropriada->compartimento, &rocha);
            AtualizarLocalizacaoSonda(
                sondaMaisApropriada,
                rocha.localizacao.latituderocha,
                rocha.localizacao.longituderocha
            );
        } else {
            printf("Nenhuma sonda disponível para receber a rocha (peso: %.2f).\n", rocha.peso);
        }
    }

    // Ordenar as rochas em cada sonda
    atual = listasondas->pPrimeiro->pProx;
    while (atual != NULL) {
        DadosSonda *sonda = &atual->sonda;
        OrdenarRochas(&sonda->compartimento); // Ordenação opcional
        atual = atual->pProx;
    }

    printf("Redistribuição dinâmica concluída.\n");
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



int main() {
    Tlista listasondas;
    int n_sondas;
    FLvazia(&listasondas);

    printf("Numero de sondas: ");
    fflush(stdout);
    scanf("%d", &n_sondas);

    for (int i = 0; i < n_sondas; i++) {
        DadosSonda novaSonda;

        printf("Digite os dados da sonda %d (Latitude Longitude Capacidade Velocidade Combustivel): ", i + 1);
        fflush(stdout);
        scanf("%f %f %f %f %f",
              &novaSonda.Latitude,
              &novaSonda.Longitude,
              &novaSonda.Capacidade,
              &novaSonda.Velocidade,
              &novaSonda.Combustivel);

        InicializarSonda(&novaSonda, i + 1,
                         novaSonda.Latitude,
                         novaSonda.Longitude,
                         novaSonda.Capacidade,
                         novaSonda.Velocidade,
                         novaSonda.Combustivel);

        if (Linsere(&listasondas, &novaSonda)) {
            printf("Sonda %d inserida com sucesso!\n", novaSonda.Identificador);
        } else {
            printf("Falha ao inserir a sonda %d.\n", novaSonda.Identificador);
        }
        LigarSonda(&novaSonda);
        ExibirStatusSonda(&novaSonda);
    }

    ///printf("\nLista de Sondas:\n");
    //////
    printf("Sistema inicializado com %d sondas.\n", n_sondas);

    printf("Digite o numero de acoes: ");
    fflush(stdout);
    int n_acoes;
    scanf("%d", &n_acoes);

    for (int i = 0; i < n_acoes; i++) {
        char comando;
        printf("\nDigite o comando (R/I/E): ");
        fflush(stdout);
        scanf(" %c", &comando);
        while(getchar() != '\n');

        if (comando == 'R') {
            char linha[250];
            float latitude, longitude, peso;
            char mineral1[50], mineral2[50], mineral3[50];

            fgets(linha, sizeof(linha), stdin);
            linha[strcspn(linha, "\n")] = '\0'; 
            printf("\nEntrada recebida: %s\n", linha);

   
            char *token = strtok(linha, " "); 

   
            latitude = atof(token); 
            token = strtok(NULL, " ");

            longitude = atof(token); 
            token = strtok(NULL, " "); 

            peso = atof(token); 
            token = strtok(NULL, " ");
   
            if (token != NULL) {
                strcpy(mineral1, token); 
            } else {
                strcpy(mineral1, ""); 
            }

   
            token = strtok(NULL, " ");
            if (token != NULL) {
                strcpy(mineral2, token); 
                } else {
                    strcpy(mineral2, ""); 
                }

  
                token = strtok(NULL, " "); 
                if (token != NULL) {
                    strcpy(mineral3, token); 
                } else {
                    strcpy(mineral3, "");
                }

                rochamineral novaRocha;
                strcpy(novaRocha.categoria, "");
                novaRocha.peso = peso;
                novaRocha.localizacao.latituderocha = latitude;
                novaRocha.localizacao.longituderocha = longitude;

                DadosSonda *sondamaisprox = EncontrarSondaMaisProxima(&listasondas, latitude, longitude);
                if (sondamaisprox != NULL) {
                    MoverSonda(sondamaisprox, latitude, longitude);
                    printf("Sonda %d movida para a posicao da rocha em (%f, %f).\n", 
                    sondamaisprox->Identificador, 
                    latitude, 
                    longitude);

       
                DefinirCategoriaPorMinerais(&novaRocha, mineral1, mineral2, mineral3);
                AdicionarRochaNaSondaMaisProxima(&listasondas, &novaRocha);
    }
}

        else if (comando == 'I') {
            if (LehVazia(&listasondas)) {
                printf("A lista de sondas esta vazia.\n");
            } else {
                
                TCelula *atual = listasondas.pPrimeiro->pProx;
                while (atual != NULL) {
                    DadosSonda *sonda = &atual->sonda;
                    printf("\n%d\n", sonda->Identificador);
                    if (lehvaziarocha(&sonda->compartimento)) {
                        printf("compartimento vazio!\n");
                    } else {
                        limprimerocha(&sonda->compartimento);
                    }
                    atual = atual->pProx;
                }
                printf("\n");
            }

        }else if (comando == 'E') {
            printf("Executando redistribuicao...\n");
            RedistribuirRochasDinamicamente(&listasondas);
            printf("Estado atualizado apos redistribuicao:\n");
            TCelula *atual = listasondas.pPrimeiro->pProx;
            while (atual != NULL){
                DadosSonda *sonda = &atual->sonda;
                printf("%d\n", sonda->Identificador);
                limprimerocha(&sonda->compartimento);
                atual = atual->pProx;
            }
            break;
        
        
        } else {
            printf("Comando desconhecido: %c\n", comando);
        }
    }
}