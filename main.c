#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "L_Sondas.h"
#include <math.h>

// Função principal
int main() {
    int N_Sondas, Escolha = 0; // Número de sondas e escolha do método de entrada
    double lat_i, long_i; // Coordenadas iniciais da sonda
    float c_i, v_i, nc_i; // Capacidade, velocidade, e combustível inicial das sondas
    char linha[255]; // Buffer para leitura de strings
    L_Sondas ListaSonda; // Lista de sondas
    rochamineral rocha; // Estrutura que representa uma rocha mineral
    Mineral minel; // Estrutura que representa um mineral
    DadosSonda sondai; // Estrutura que representa uma sonda

    // Solicita ao usuário o método de entrada de dados (1 - Terminal, 2 - Arquivo)
    while (Escolha != 1 && Escolha != 2) {
        printf("Arquivo de entrada 1-Terminal, 2-Arquivo: \n");
        scanf("%d", &Escolha);
    }

    // Entrada de dados via terminal
    if (Escolha == 1) {
        FLVazia_S(&ListaSonda); // Inicializa a lista de sondas como vazia

        // Solicita o número de sondas e seus dados
        printf("Digite o numero de sondas: ");
        scanf("%d", &N_Sondas);
        printf("Digite os dados das sondas: (latitude, longitude, capacidade maxima, velocidade e combustivel)\n");
        for (int i = 0; i < N_Sondas; i++) {
            scanf("%lf %lf %f %f %f", &lat_i, &long_i, &c_i, &v_i, &nc_i);
            InicializaSonda(&sondai, (i + 1), lat_i, long_i, c_i, "Sim"); // Inicializa uma nova sonda
            LInsere_S(&ListaSonda, &sondai); // Insere a sonda na lista
        }

        int N_op; // Número de operações
        printf("Digite o numero de operacoes: ");
        scanf("%d", &N_op);
        for (int i = 0; i < N_op; i++) {
            char operacao;
            printf("Digite a operacao: ");
            scanf(" %c", &operacao);

            // Processa a operação escolhida
            switch (operacao) {
                case 'R': { // Adicionar rochas a partir das coordenadas e minerais
                    double lat_r, long_r;
                    float p_r;
                    char minerais_str[100];

                    // Recebe os dados da rocha
                    printf("\nDigite a latitude, longitude, peso e os minerais:\n");
                    scanf("%lf %lf %f", &lat_r, &long_r, &p_r);
                    getchar(); // Remove o caractere de nova linha do buffer
                    fgets(minerais_str, sizeof(minerais_str), stdin);
                    minerais_str[strcspn(minerais_str, "\n")] = '\0'; // Remove a quebra de linha

                    const char delim[2] = " ";
                    char *buffer = strtok(minerais_str, delim);

                    FLVazia_L(&rocha.L_Mineral); // Inicializa a lista de minerais da rocha como vazia

                    // Adiciona os minerais à lista da rocha
                    while (buffer != NULL) {
                        Lis_Minerais(&minel, buffer);
                        LInsere_L(&rocha.L_Mineral, minel);
                        buffer = strtok(NULL, delim);
                    }

                    int cont = 0;

                    // Inicializa e insere a rocha na lista
                    InicializaRocha(&rocha, ++cont, p_r, Categoria(&rocha), "", lat_r, long_r);
                    Insere_S(&ListaSonda, &rocha);

                    break;
                }
                case 'I': { // Executa a operação 'I'
                    OperacaoI(&ListaSonda);
                    break;
                }
                case 'E': { // Executa a operação 'E'
                    OperacaoE(&ListaSonda);
                    break;
                }
            }
        }
    }
    // Entrada de dados via arquivo
    else if (Escolha == 2) {
        printf("Nome do arquivo de entrada: ");
        char nomearq[33];

        FILE *arq;
        scanf("%32s", nomearq);
        arq = fopen(nomearq, "r"); // Abre o arquivo em modo leitura

        // Lê o número de sondas
        fscanf(arq, "%d", &N_Sondas);
        FLVazia_S(&ListaSonda); // Inicializa a lista de sondas como vazia

        // Lê e adiciona cada sonda à lista
        for (int i = 0; i < N_Sondas; i++) {
            fscanf(arq, "%lf %lf %f %f %f", &lat_i, &long_i, &c_i, &v_i, &nc_i);
            InicializaSonda(&sondai, (i + 1), lat_i, long_i, c_i, "Sim");
            LInsere_S(&ListaSonda, &sondai);
        }

        int N_op; // Número de operações
        fscanf(arq, "%d", &N_op);

        // Processa cada operação no arquivo
        for (int i = 0; i < N_op; i++) {
            char opcao;
            fscanf(arq, " %c", &opcao);

            switch (opcao) {
                case 'R': { // Adicionar rochas
                    int c;
                    while ((c = fgetc(arq)) != '\n' && c != EOF);

                    FLVazia_L(&rocha.L_Mineral); // Inicializa a lista de minerais da rocha como vazia
                    double lat_r, long_r;
                    float p_r;

                    // Lê a linha com os dados da rocha
                    fgets(linha, sizeof(linha), arq);
                    linha[strcspn(linha, "\n")] = '\0';
                    // Cada chamada a strtok retorna o próximo token, que é processado (convertido em valores numéricos ou strings) e armazenado em variáveis apropriadas.
                    char *buffer = strtok(linha, " ");
                    lat_r = atof(buffer);
                    buffer = strtok(NULL, " ");
                    long_r = atof(buffer);
                    buffer = strtok(NULL, " ");
                    p_r = atof(buffer);
                    buffer = strtok(NULL, " ");

                    // Adiciona os minerais à rocha
                    while (buffer != NULL) {
                        Mineral mineral;
                        buffer[strcspn(buffer, "\n")] = '\0';
                        Lis_Minerais(&mineral, buffer);
                        LInsere_L(&rocha.L_Mineral, mineral);
                        buffer = strtok(NULL, " ");
                    }

                    int cont = 0;

                    // Inicializa e insere a rocha na lista
                    InicializaRocha(&rocha, ++cont, p_r, Categoria(&rocha), "", lat_r, long_r);
                    Insere_S(&ListaSonda, &rocha);

                    break;
                }
                case 'I': { // Executa a operação 'I'
                    OperacaoI(&ListaSonda);
                    break;
                }
                case 'E': { // Executa a operação 'E'
                    OperacaoE(&ListaSonda);
                    break;
                }
            }
        }
        fclose(arq); // Fecha o arquivo
    }
    return 0; // Fim do programa
}