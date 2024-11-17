#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include "ListaSondasEspaciais.h"
int main() {
    Tlista listasondas;
    int n_sondas;
    FLvazia(&listasondas); //cria uma lista de sondas vazia

    printf("Numero de sondas: ");
    scanf("%d", &n_sondas);

    for (int i = 0; i < n_sondas; i++) {
        DadosSonda novaSonda;

        printf("Digite os dados da sonda %d (Latitude Longitude Capacidade Velocidade Combustivel): ", i + 1);
        scanf("%f %f %f %f %f",
              &novaSonda.Latitude,
              &novaSonda.Longitude,
              &novaSonda.Capacidade,
              &novaSonda.Velocidade,
              &novaSonda.Combustivel); //recebe todos os dados da sonda pelo usuario

        InicializarSonda(&novaSonda, i + 1,
                         novaSonda.Latitude,
                         novaSonda.Longitude,
                         novaSonda.Capacidade,
                         novaSonda.Velocidade,
                         novaSonda.Combustivel);// inicializa sonda

        if (Linsere(&listasondas, &novaSonda)) {
            printf("Sonda %d inserida com sucesso!\n", novaSonda.Identificador);//insere a sonda criada na lista de sondas
        } else {
            printf("Falha ao inserir a sonda %d.\n", novaSonda.Identificador);
        }
        LigarSonda(&novaSonda); 
        ExibirStatusSonda(&novaSonda);
    }

    printf("Sistema inicializado com %d sondas.\n", n_sondas);

    printf("Digite o numero de acoes: ");
    int n_acoes;
    scanf("%d", &n_acoes);//recebe o numero de operacoes que o usuario vai fazer

    for (int i = 0; i < n_acoes; i++) {
        char comando;
        printf("\nDigite o comando (R/I/E): ");
        scanf(" %c", &comando);
        while(getchar() != '\n');

        if (comando == 'R') {
            char linha[250];
            float latitude, longitude, peso;
            char mineral1[50], mineral2[50], mineral3[50];

            fgets(linha, sizeof(linha), stdin);//le a linha completa que o usuario insere
            linha[strcspn(linha, "\n")] = '\0'; //remover o caractere da nova linha (\n) 
            printf("\nEntrada recebida: %s\n", linha);

   
            char *token = strtok(linha, " "); //divide a linha em tokens delimitados por um espaco " "

   
            latitude = atof(token); //converte o token para um float e armazena na variavel latitude
            token = strtok(NULL, " "); //procura o proximo token na string usando o delimitador espaco " "

            longitude = atof(token); 
            token = strtok(NULL, " ");  

            peso = atof(token); 
            token = strtok(NULL, " "); 
   
            if (token != NULL) { //verifica se o token contem um valor,  retorna NULL quando não encontra mais tokens na string
                strcpy(mineral1, token); //copia o conteudo do token para a variavel mineral1
            } else {
                strcpy(mineral1, ""); //se nao tiver token faz com que a mineral1 fique fazia ""
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
                novaRocha.localizacao.longituderocha = longitude; //inicializa os dados de uma nova rocha

                DadosSonda *sondamaisprox = EncontrarSondaMaisProxima(&listasondas, latitude, longitude);
                if (sondamaisprox != NULL) { //confere se foi encontrada uma sonda mais próxima da rocha
                    MoverSonda(sondamaisprox, latitude, longitude);//move a sonda para a posicao da rocha
                    printf("Sonda %d movida para a posicao da rocha em (%f, %f).\n", 
                    sondamaisprox->Identificador, 
                    latitude, 
                    longitude);

       
                DefinirCategoriaPorMinerais(&novaRocha, mineral1, mineral2, mineral3);//recebe om minerais e retorna a categoria
                AdicionarRochaNaSondaMaisProxima(&listasondas, &novaRocha);
    }
}

        else if (comando == 'I') {//imprime os status atual das sondas
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
            printf("...Executando redistribuicao...\n");
            RedistribuirRochas(&listasondas);//redistribui as rochas
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