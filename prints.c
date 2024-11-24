#include "prints.h"
#include <stdio.h>

void printInicio(){
    printf("\n===================================================================================================================================\n");
    printf("Ola, somos a equipe de desenvolvimento que fara o sistema de controle de sondas e catalogacao de rochas minerais.\nMembros do grupo: Tariky, Erich e Bernado.\n");
    printf("===================================================================================================================================\n\n");
    printf("Primeiro insira a opcao de entrada.\n");
}
void printEntrada(){
    printf("Arquivo de entrada 1-Terminal, 2-Arquivo: \n");
}
void printNumOper(){
    printf("A Sonda ja esta disponivel para realizar as operacoes.\nAgora insira o numero de operacoes: ");

}
void printDadosSonda(){
    printf("Insira os dados das sondas: Latitude, longitude, capacidade maxima, velocidade e combustivel\n");
}
void printNumSondas(){
    printf("Agora insira o numero de sondas: ");
}
void printSucesDados(){
    printf("Dados da sonda(s) inseridos com sucesso!! Elas ja estao prontas para irem para Marte.\n\n");
}
void printOper(){
    printf("Digite a operacao (R/I/E)\nR: Coleta de uma nova rocha. I: Imprime o status da sonda. E: Redistribuir rochas e voltar para a Terra.\n");

}
void printDadosRoch(){
    printf("\nDigite a latitude, longitude, peso e ate 3 tipos de minerais:\n");

}
void printNomearq(){
    printf("Insira o nome do arquivo: ");
}