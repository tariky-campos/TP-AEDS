#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prints.h"
#include <math.h>
#define Maxtam 255
#define miner 50

// Função principal
int main() {
    int N_Sondas, comando = 0; // Número de sondas e comando do método de entrada
    double lat_i, long_i; // Coordenadas iniciais da sonda
    float c_i, v_i, nc_i; // Capacidade, velocidade, e combustível inicial das sondas
    char linha[Maxtam]; // Buffer para leitura de strings
    L_Sondas LISTASONDA; // Lista de sondas
    rochamineral ROCHA; // Estrutura que representa uma rocha mineral
    Mineral MINEL; // Estrutura que representa um mineral
    DadosSonda SONDA; // Estrutura que representa uma sonda

  
    printInicio();
    while (comando != 1 && comando != 2) {
        printEntrada();
        scanf("%d", &comando);
    }
    // Entrada de dados via terminal
    if (comando == 1) {
        FLVazia_S(&LISTASONDA); // Inicializa a lista de sondas como vazia

        // Solicita o número de sondas e seus dados
        printNumSondas();
        scanf("%d", &N_Sondas);

        printDadosSonda();
        for (int i = 0; i < N_Sondas; i++) {
            scanf("%lf %lf %f %f %f", &lat_i, &long_i, &c_i, &v_i, &nc_i);
            InicializaSonda(&SONDA, (i + 1), lat_i, long_i, c_i, "Sim"); // Inicializa uma nova sonda
            LInsere_S(&LISTASONDA, &SONDA); // Insere a sonda na lista
        }
        printSucesDados();

        int numOperacoes; // Número de operações
        printNumOper();
        scanf("%d", &numOperacoes);
        for (int i = 0; i < numOperacoes; i++) {
            char operacao;
            printOper();
            scanf(" %c", &operacao);

            // Processa a operação escolhida
            switch (operacao) {
                case 'R': { // Adicionar rochas a partir das coordenadas e minerais
                    double latitude, longitude;
                    float pesoRcha;
                    char minerais[miner];

                    // Recebe os dados da rocha
                    printDadosRoch();
                    scanf("%lf %lf %f", &latitude, &longitude, &pesoRcha);
                    getchar(); // Remove o caractere de nova linha do buffer
                    fgets(minerais, sizeof(minerais), stdin);
                    minerais[strcspn(minerais, "\n")] = '\0'; // Remove a quebra de linha

                    const char delimitador[2] = " ";
                    char *buffer = strtok(minerais, delimitador);

                    FLVazia_L(&ROCHA.L_Mineral); // Inicializa a lista de minerais da rocha como vazia

                    // Adiciona os minerais à lista da rocha
                    while (buffer != NULL) {
                        Lis_Minerais(&MINEL, buffer);
                        LInsere_L(&ROCHA.L_Mineral, MINEL);
                        buffer = strtok(NULL, delimitador);
                    }

                    int cont = 0;

                    // Inicializa e insere a rocha na lista
                    InicializaRocha(&ROCHA, ++cont, pesoRcha, Categoria(&ROCHA), "", latitude, longitude);
                    Insere_S(&LISTASONDA, &ROCHA);

                    break;
                }
                case 'I': { // Executa a operação 'I'
                    OperacaoI(&LISTASONDA);
                    break;
                }
                case 'E': { // Executa a operação 'E'
                    OperacaoE(&LISTASONDA);
                    break;
                }
            }
        }
    }
    // Entrada de dados via arquivo
    else if (comando == 2) {
        printNomearq();
        char nomearq[miner];

        FILE *arq;
        scanf("%49s", nomearq);
        arq = fopen(nomearq, "r"); // Abre o arquivo em modo leitura

        // Lê o número de sondas
        fscanf(arq, "%d", &N_Sondas);
        FLVazia_S(&LISTASONDA); // Inicializa a lista de sondas como vazia

        // Lê e adiciona cada sonda à lista
        for (int i = 0; i < N_Sondas; i++) {
            fscanf(arq, "%lf %lf %f %f %f", &lat_i, &long_i, &c_i, &v_i, &nc_i);
            InicializaSonda(&SONDA, (i + 1), lat_i, long_i, c_i, "Sim");
            LInsere_S(&LISTASONDA, &SONDA);
        }

        int numOperacoes; // Número de operações
        fscanf(arq, "%d", &numOperacoes);

        // Processa cada operação no arquivo
        for (int i = 0; i < numOperacoes; i++) {
            char opcao;
            fscanf(arq, " %c", &opcao);

            switch (opcao) {
                case 'R': { // Adicionar rochas
                    int contador = 0;
                    int c;
                    double latitude, longitude;
                    float pesoRcha;

                    while ((c = fgetc(arq)) != '\n' && c != EOF);
                    FLVazia_L(&ROCHA.L_Mineral); // Inicializa a lista de minerais da rocha como vazia

                    // Lê a linha com os dados da rocha
                    fgets(linha, sizeof(linha), arq);
                    linha[strcspn(linha, "\n")] = '\0';
                    // Cada chamada a strtok retorna o próximo token, que é processado (convertido em valores numéricos ou strings) e armazenado em variáveis apropriadas.
                    char *buffer = strtok(linha, " ");
                    latitude = atof(buffer);
                    buffer = strtok(NULL, " ");
                    longitude = atof(buffer);
                    buffer = strtok(NULL, " ");
                    pesoRcha = atof(buffer);
                    buffer = strtok(NULL, " ");

                    // Adiciona os minerais à rocha
                    while (buffer != NULL) {
                        Mineral mineral;
                        buffer[strcspn(buffer, "\n")] = '\0';
                        Lis_Minerais(&mineral, buffer);
                        LInsere_L(&ROCHA.L_Mineral, mineral);
                        buffer = strtok(NULL, " ");
                    }

                    // Inicializa e insere a rocha na lista
                    InicializaRocha(&ROCHA, ++contador, pesoRcha, Categoria(&ROCHA), "", latitude, longitude);
                    Insere_S(&LISTASONDA, &ROCHA);

                    break;
                }
                case 'I': { // Executa a operação 'I'
                    OperacaoI(&LISTASONDA);
                    break;
                }
                case 'E': { // Executa a operação 'E'
                    OperacaoE(&LISTASONDA);
                    break;
                }
            }
        }
        fclose(arq); // Fecha o arquivo
    }
    return 0; // Fim do programa
}
