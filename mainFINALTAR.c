#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include "menu.h"
int main()
{

    int tipo;

    char linha[500];
    float latitude, longitude, peso;
    char mineral1[50], mineral2[50], mineral3[50];
    printf("1-Arquivo de teste  2-Terminal\n");
    scanf("%d", &tipo);
    if (tipo == 1)//executa pelo arquivo de teste
    {
        Tlista listasondas;
        int n_sondas;
        FLvazia(&listasondas); // cria uma lista de sondas vazia

        printf("Insira o nome do arquivo de teste: ");
        fflush(stdout);

        char nomearq[50];

        FILE *arq; // declara um ponteiro para manipular um arquivo
        scanf("%49s",nomearq);
        arq = fopen(nomearq, "r");// abre o arquivo no modo de leitura
        fscanf(arq, "%d", &n_sondas);
        printf("%d", n_sondas);

        for (int i = 0; i < n_sondas; i++)
        {
            DadosSonda novaSonda;

            fflush(stdout);
            fscanf(arq, "%f %f %f %f %f",
                   &novaSonda.Latitude,
                   &novaSonda.Longitude,
                   &novaSonda.Capacidade,
                   &novaSonda.Velocidade,
                   &novaSonda.Combustivel);// recebe todos os dados das sondas

            InicializarSonda(&novaSonda, i + 1,
                             novaSonda.Latitude,
                             novaSonda.Longitude,
                             novaSonda.Capacidade,
                             novaSonda.Velocidade,
                             novaSonda.Combustivel);// inicializa as sondas

            if (Linsere(&listasondas, &novaSonda))
            {
                printf("Sonda %d inserida com sucesso!\n", novaSonda.Identificador);
            }
            else
            {
                printf("Falha ao inserir a sonda %d.\n", novaSonda.Identificador);
            }// insere as sondas no lista de sondas
            LigarSonda(&novaSonda);
            ExibirStatusSonda(&novaSonda);
        }

        printf("Sistema inicializado com %d sondas.\n", n_sondas);


        fflush(stdout);
        int n_acoes;
        fscanf(arq, "%d", &n_acoes);

        for (int i = 0; i < n_acoes; i++)
        {
            char comando;
            fflush(stdout);
            fscanf(arq, " %c", &comando);

            if (comando == 'R')
            {
                int ch;
                while ((ch = fgetc(arq)) != '\n' && ch != EOF);
                // le os caracteres linha atual ate encontrar uma nova linha (\n)
                
                fgets(linha, sizeof(linha), arq);// le até a linha ate encontrar um \n.
                linha[strcspn(linha, "\n")] = '\0';
                // remover o caractere da nova linha (\n)
                printf("\nEntrada recebida: %s\n", linha);

                char *token = strtok(linha, " ");// divide a linha em tokens delimitados por um espaco " "

                latitude = atof(token);// converte o token para um float e armazena na variavel latitude
                token = strtok(NULL, " ");// procura o proximo token na string usando o delimitador espaco " "

                longitude = atof(token);
                token = strtok(NULL, " ");

                peso = atof(token);
                token = strtok(NULL, " ");

                if (token != NULL)
                {// verifica se o token contem um valor,  retorna NULL quando não encontra mais tokens na string
                    strcpy(mineral1, token);// copia o conteudo do token para a variavel mineral1
                }
                else
                {
                    strcpy(mineral1, "");// se nao tiver token faz com que a mineral1 fique fazia ""
                }

                token = strtok(NULL, " ");
                if (token != NULL)
                {
                    strcpy(mineral2, token);
                }
                else
                {
                    strcpy(mineral2, "");
                }

                token = strtok(NULL, " ");
                if (token != NULL)
                {
                    strcpy(mineral3, token);
                }
                else
                {
                    strcpy(mineral3, "");
                }

                rochamineral novaRocha;
                strcpy(novaRocha.categoria, "");// inicializa o campo categoria da rocha com uma string vazia.
                novaRocha.peso = peso;
                novaRocha.localizacao.latituderocha = latitude;
                novaRocha.localizacao.longituderocha = longitude; // inicializa os dados de uma nova rocha

                DadosSonda *sondamaisprox = EncontrarSondaMaisProxima(&listasondas, latitude, longitude);
                if (sondamaisprox != NULL)
                {// confere se foi encontrada uma sonda mais próxima da rocha
                    MoverSonda(sondamaisprox, latitude, longitude);// move a sonda para a posicao da rocha
                    printf("Sonda %d movida para a posicao da rocha em (%f, %f).\n",
                           sondamaisprox->Identificador,
                           latitude,
                           longitude);

                    DefinirCategoriaPorMinerais(&novaRocha, mineral1, mineral2, mineral3);// recebe om minerais e retorna a categoria
                    AdicionarRochaNaSondaMaisProxima(&listasondas, &novaRocha);//adiciona a rocha na sonda mais proxima
                }
            }

            else if (comando == 'I')
            {
                if (LehVazia(&listasondas))
                printf("A lista de sondas esta vazia.\n");
                else OperacaoI(&listasondas);// imprime os status atual das sondas
            }
            else if (comando == 'E') 
            OperacaoE(&listasondas);
            // redistribui as rochas entre as sondas para que fiquem com peso o mais semelhante possivel
            else printf("Comando desconhecido: %c\n", comando);
        }
        fclose(arq);//fecha o arquivo
    }
    else// executa pelo terminal
    {
        Tlista listasondas;
        int n_sondas;
        FLvazia(&listasondas); // cria uma lista de sondas vazia

        printquntdsondas();
        scanf("%d", &n_sondas);

        for (int i = 0; i < n_sondas; i++)
        {
            DadosSonda novaSonda;

            printsonda(n_sondas);
            scanf("%f %f %f %f %f",
                  &novaSonda.Latitude,
                  &novaSonda.Longitude,
                  &novaSonda.Capacidade,
                  &novaSonda.Velocidade,
                  &novaSonda.Combustivel); // recebe todos os dados da sonda pelo usuario

            InicializarSonda(&novaSonda, i + 1,
                             novaSonda.Latitude,
                             novaSonda.Longitude,
                             novaSonda.Capacidade,
                             novaSonda.Velocidade,
                             novaSonda.Combustivel); // inicializa sonda

            if (Linsere(&listasondas, &novaSonda))
            {
                printf("Sonda %d inserida com sucesso!\n", novaSonda.Identificador); // insere a sonda criada na lista de sondas
            }
            else
            {
                printf("Falha ao inserir a sonda %d.\n", novaSonda.Identificador);
            }
            LigarSonda(&novaSonda);
            ExibirStatusSonda(&novaSonda);
        }

        printf("Sistema inicializado com %d sondas.\n", n_sondas);

        printquntdoperacoes();
        int n_acoes;
        scanf("%d", &n_acoes); // recebe o numero de operacoes que o usuario vai fazer

        for (int i = 0; i < n_acoes; i++)
        {
            char comando;
            printmenu();
            scanf(" %c", &comando);
            while (getchar() != '\n');// limpa o buffer do teclado

            if (comando == 'R')
            {
                char linha[250];
                float latitude, longitude, peso;
                char mineral1[50], mineral2[50], mineral3[50];
                printRochanova();

                fgets(linha, sizeof(linha), stdin); // le a linha completa que o usuario insere
                linha[strcspn(linha, "\n")] = '\0'; // remover o caractere da nova linha (\n)
                printf("\nEntrada recebida: %s\n", linha);

                char *token = strtok(linha, " "); // divide a linha em tokens delimitados por um espaco " "

                latitude = atof(token);    // converte o token para um float e armazena na variavel latitude
                token = strtok(NULL, " "); // procura o proximo token na string usando o delimitador espaco " "

                longitude = atof(token);
                token = strtok(NULL, " ");

                peso = atof(token);
                token = strtok(NULL, " ");

                if (token != NULL)
                {                            // verifica se o token contem um valor,  retorna NULL quando não encontra mais tokens na string
                    strcpy(mineral1, token); // copia o conteudo do token para a variavel mineral1
                }
                else
                {
                    strcpy(mineral1, ""); // se nao tiver token faz com que a mineral1 fique fazia ""
                }

                token = strtok(NULL, " ");
                if (token != NULL)
                {
                    strcpy(mineral2, token);
                }
                else
                {
                    strcpy(mineral2, "");
                }

                token = strtok(NULL, " ");
                if (token != NULL)
                {
                    strcpy(mineral3, token);
                }
                else
                {
                    strcpy(mineral3, "");
                }

                rochamineral novaRocha;
                strcpy(novaRocha.categoria, "");// inicializa o campo categoria da rocha com uma string vazia.
                novaRocha.peso = peso;
                novaRocha.localizacao.latituderocha = latitude;
                novaRocha.localizacao.longituderocha = longitude; // inicializa os dados de uma nova rocha

                DadosSonda *sondamaisprox = EncontrarSondaMaisProxima(&listasondas, latitude, longitude);
                if (sondamaisprox != NULL)
                {// confere se foi encontrada uma sonda mais próxima da rocha
                    MoverSonda(sondamaisprox, latitude, longitude); // move a sonda para a posicao da rocha
                    printf("Sonda %d movida para a posicao da rocha em (%f, %f).\n",
                           sondamaisprox->Identificador,
                           latitude,
                           longitude);

                    DefinirCategoriaPorMinerais(&novaRocha, mineral1, mineral2, mineral3); // recebe om minerais e retorna a categoria
                    AdicionarRochaNaSondaMaisProxima(&listasondas, &novaRocha);// adiciona a rocha na sonda mais proxima
                }
            }

            else if (comando == 'I') 
            { 
                if (LehVazia(&listasondas))
                printf("A lista de sondas esta vazia.\n");
                
                else
                 OperacaoI(&listasondas);// imprime os status atual das sondas
            }
            else if (comando == 'E')
                OperacaoE(&listasondas);
                // redistribui as rochas entre as sondas para que fiquem com peso o mais semelhante possivel
            else
            {
                printf("Comando desconhecido: %c\n", comando);
            }
        }
    }
}
