#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include "ListaSondasEspaciais.h"
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