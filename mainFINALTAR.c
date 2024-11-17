#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include "ListaSondasEspaciais.h"

void DefinirCategoriaPorMinerais(rochamineral *rocha, const char *mineral1, const char *mineral2) {
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
        strcpy(rocha->categoria, "Sem Categoria"); // Categoria padrão caso não corresponda
    }
    printf("Mineral 1: %s, Mineral 2: %s\n", mineral1, mineral2);
}

float CalcularDistancia(float lat1, float lon1, float lat2, float lon2);

float CalcularDistancia(float lat1, float lon1, float lat2, float lon2) {
    return sqrt(pow(lat2 - lat1, 2) + pow(lon2 - lon1, 2));
}

// Função para mover todas as sondas para o ponto (0,0)
void MoverSondasParaOrigem(Tlista *listasondas) {
    if (LehVazia(listasondas)) {
        printf("A lista de sondas está vazia.\n");
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
            printf("Sonda %d movida para a origem (0,0). Combustível restante: %.2f\n", sonda->Identificador, sonda->Combustivel);
        } else {
            printf("Sonda %d não possui combustível suficiente para se mover para a origem.\n", sonda->Identificador);
        }
        atual = atual->pProx;
    }
}

// Função para redistribuir o peso das rochas entre as sondas
void RedistribuirRochas(Tlista *listasondas) {
    if (LehVazia(listasondas)) {
        printf("A lista de sondas está vazia.\n");
        return;
    }

    float peso_total = 0;
    int total_sondas = 0;

    TCelula *atual = listasondas->pPrimeiro->pProx;
    while (atual != NULL) {
        DadosSonda *sonda = &atual->sonda;
        peso_total += PesoTotal(&sonda->compartimento);
        total_sondas++;
        atual = atual->pProx;
    }

    if (total_sondas == 0) {
        printf("Nenhuma sonda disponível para redistribuir rochas.\n");
        return;
    }

    float peso_por_sonda = peso_total / total_sondas;

    atual = listasondas->pPrimeiro->pProx;
    while (atual != NULL) {
        DadosSonda *sonda = &atual->sonda;
        AjustarPeso(&sonda->compartimento, peso_por_sonda);
        printf("Sonda %d ajustada para peso aproximado de %.2f\n", sonda->Identificador, peso_por_sonda);
        atual = atual->pProx;
    }
}
float CalcularDistancia(float lat1, float lon1, float lat2, float lon2);

// Função para adicionar a rocha na sonda mais próxima
void AdicionarRochaNaSondaMaisProxima(Tlista *listasondas, rochamineral *novaRocha) {
    if (LehVazia(listasondas)) {
        printf("A lista de sondas está vazia.\n");
        return;
    }

    TCelula *atual = listasondas->pPrimeiro->pProx;
    DadosSonda *sondaMaisProxima = NULL;
    float menorDistancia = FLT_MAX;

    while (atual != NULL) {
        DadosSonda *sonda = &atual->sonda;
        float distancia = CalcularDistancia(novaRocha->localizacao.latituderocha, novaRocha->localizacao.longituderocha, sonda->Latitude, sonda->Longitude);
        
        if (distancia < menorDistancia) {
            menorDistancia = distancia;
            sondaMaisProxima = sonda;
        }

        atual = atual->pProx;
    }

    if (sondaMaisProxima != NULL) {
        linsererocha(&sondaMaisProxima->compartimento, novaRocha);
        printf("Rocha adicionada à sonda %d (Distância: %.2f)\n", sondaMaisProxima->Identificador, menorDistancia);
    } else {
        printf("Nenhuma sonda disponível para adicionar a rocha.\n");
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
    }

    printf("\nLista de Sondas:\n");
    Imprime(&listasondas);
    printf("Sistema inicializado com %d sondas.\n", n_sondas);

    printf("Digite o número de acoes: ");
    fflush(stdout);
    int n_acoes;
    scanf("%d", &n_acoes);

    for (int i = 0; i < n_acoes; i++) {
        char comando;
        printf("Digite o comando (R/I/E): ");
        fflush(stdout);
        scanf(" %c", &comando);

        if (comando == 'R') {
            char linha[250];
            float latitude, longitude, peso;
            char mineral1[50], mineral2[50];

            fgets(linha, sizeof(linha), stdin);
            linha[strcspn(linha, "\n")] = '\0'; // Remove o caractere de nova linha
            printf("Entrada recebida: %s\n", linha);

            // Usa strtok para separar os tokens
            char *token = strtok(linha, " "); // O delimitador é o espaço

            // Converte os três primeiros tokens para float
            latitude = atof(token); // Converte o primeiro valor para float
            token = strtok(NULL, " "); // Avança para o próximo token

            longitude = atof(token); // Converte o segundo valor para float
            token = strtok(NULL, " "); // Avança para o próximo token

            peso = atof(token); // Converte o terceiro valor para float
            token = strtok(NULL, " "); // Avança para o próximo token

            // O próximo token é o primeiro mineral
            strcpy(mineral1, token); // Copia o quarto valor para a string1
            token = strtok(NULL, " "); // Avança para o próximo token

            // Se houver um segundo mineral, copie-o
            if (token != NULL) {
                strcpy(mineral2, token); // Copia o quinto valor para a string2
            } else {
                strcpy(mineral2, ""); // Se não houver, define como string vazia
            }

            rochamineral novaRocha;
            strcpy(novaRocha.categoria, "");
            novaRocha.peso = peso;
            novaRocha.localizacao.latituderocha = latitude;
            novaRocha.localizacao.longituderocha = longitude;

            
            DefinirCategoriaPorMinerais(&novaRocha, mineral1, mineral2);
            AdicionarRochaNaSondaMaisProxima(&listasondas, &novaRocha);
        } 
        else if (comando == 'I') {
            if (LehVazia(&listasondas)) {
                printf("A lista de sondas está vazia.\n");
            } else {
                
                TCelula *atual = listasondas.pPrimeiro->pProx;
                while (atual != NULL) {
                    DadosSonda *sonda = &atual->sonda;
                    printf("%d\n", sonda->Identificador);
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
            MoverSondasParaOrigem(&listasondas);
            RedistribuirRochas(&listasondas);
            printf("Estado atualizado após redistribuicao:\n");
            TCelula *atual = listasondas.pPrimeiro->pProx;
            while (atual != NULL) {
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