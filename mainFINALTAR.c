#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "ListaSondasEspaciais.h"
#include <float.h>

// Função para mover todas as sondas para o ponto (0,0)
void MoverSondasParaOrigem(Tlista *listasondas) {
    if (LehVazia(listasondas)) {
        printf("A lista de sondas está vazia.\n");
        return;
    }

    TCelula *atual = listasondas->pPrimeiro->pProx;

    while (atual != NULL) {
        DadosSonda *sonda = &atual->sonda; // Acessa corretamente a sonda na célula
        float distancia = sqrt(pow(sonda->Latitude, 2) + pow(sonda->Longitude, 2));
        float consumo = distancia / sonda->Velocidade;

        // Verifica se há combustível suficiente
        if (sonda->Combustivel >= consumo) {
            sonda->Latitude = 0.0;
            sonda->Longitude = 0.0;
            sonda->Combustivel -= consumo;
            printf("Sonda %d movida para a origem (0,0). Combustível restante: %.2f\n",
                   sonda->Identificador, sonda->Combustivel);
        } else {
            printf("Sonda %d não possui combustível suficiente para se mover para a origem.\n",
                   sonda->Identificador);
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

    // Calcula o peso total das rochas e conta as sondas
    while (atual != NULL) {
        DadosSonda *sonda = &atual->sonda; // Acessa corretamente a sonda na célula
        peso_total += PesoTotal(&sonda->compartimento); // Função que retorna o peso total de rochas
        total_sondas++;
        atual = atual->pProx;
    }

    // Verifica se há sondas disponíveis
    if (total_sondas == 0) {
        printf("Nenhuma sonda disponível para redistribuir rochas.\n");
        return;
    }

    // Calcula a distribuição ideal
    float peso_por_sonda = peso_total / total_sondas;

    atual = listasondas->pPrimeiro->pProx;

    while (atual != NULL) {
        DadosSonda *sonda = &atual->sonda;
        AjustarPeso(&sonda->compartimento, peso_por_sonda); // Função que redistribui rochas
        printf("Sonda %d ajustada para peso aproximado de %.2f\n",
               sonda->Identificador, peso_por_sonda);
        atual = atual->pProx;
    }
}
    // Função para calcular a distância entre duas sondas (baseada em latitude e longitude)
float CalcularDistancia(float lat1, float lon1, float lat2, float lon2) {
    // Usando a fórmula de distância euclidiana simples (aproximação para pequenas distâncias)
    return sqrt(pow(lat2 - lat1, 2) + pow(lon2 - lon1, 2));
}

// Função para adicionar a rocha na sonda mais próxima
void AdicionarRochaNaSondaMaisProxima(Tlista *listasondas, rochamineral *novaRocha) {
    if (LehVazia(listasondas)) {
        printf("A lista de sondas está vazia.\n");
        return;
    }

    TCelula *atual = listasondas->pPrimeiro->pProx;
    DadosSonda *sondaMaisProxima = NULL;
    float menorDistancia = FLT_MAX; // Começa com a maior distância possível

    // Encontra a sonda mais próxima
    while (atual != NULL) {
        DadosSonda *sonda = &atual->sonda;
        float distancia = CalcularDistancia(novaRocha->localizacao.latituderocha, novaRocha->localizacao.longituderocha, sonda->Latitude, sonda->Longitude);
        
        if (distancia < menorDistancia) {
            menorDistancia = distancia;
            sondaMaisProxima = sonda;
        }

        atual = atual->pProx;
    }

    // Adiciona a rocha à sonda mais próxima
    if (sondaMaisProxima != NULL) {
        linsererocha(&sondaMaisProxima->compartimento, novaRocha); // Adiciona a rocha ao compartimento da sonda
        printf("Rocha adicionada à sonda %d (Distância: %.2f)\n", sondaMaisProxima->Identificador, menorDistancia);
    } else {
        printf("Nenhuma sonda disponível para adicionar a rocha.\n");
    }
}



int main() {
    Tlista listasondas;
    int n_sondas;
    tlistarocha compartimento;

    FLvazia(&listasondas);

    printf("Numero de sondas: ");
    fflush(stdout);
    scanf("%d", &n_sondas);

    for (int i = 0; i < n_sondas; i++) {
        DadosSonda novaSonda;
        
        flvaziarocha(&compartimento);

        printf("Digite os dados da sonda %d (Latitude Longitude Capacidade Velocidade Combustivel): ", i + 1);
        fflush(stdout);
        scanf("%f %f %f %f %f",
              &novaSonda.Latitude,
              &novaSonda.Longitude,
              &novaSonda.Capacidade,
              &novaSonda.Velocidade,
              &novaSonda.Combustivel);

        InicializarSonda(&novaSonda, i + 1, compartimento,
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

    // Processar ações
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
            float latitude, longitude, peso;
            char mineral1[50], mineral2[50];
            //printf("Digite os dados da rocha (Latitude Longitude Peso Mineral1 Mineral2): ");
            fflush(stdout);
            scanf("%f %f %f %s %s", &latitude, &longitude, &peso, mineral1, mineral2);

            //printf("Registrar Rocha: Latitude %.2f, Longitude %.2f, Peso %.2f, Minerais %s e %s\n",
            //       latitude, longitude, peso, mineral1, mineral2);
            // Adicione aqui a lógica para registrar a rocha
            rochamineral novaRocha;
            strcpy(novaRocha.categoria, mineral1);  // Aqui, categoria está sendo usada como mineral1
            novaRocha.peso = peso;
            linsererocha(&compartimento, &novaRocha); 

        } 
        else if (comando == 'I') {
            if (LehVazia(&listasondas)) {
            printf("A lista de sondas está vazia.\n");
            } else {
            printf("Imprimindo status atual das sondas:\n");
            TCelula *atual = listasondas.pPrimeiro->pProx;
            while (atual != NULL) {
            DadosSonda *sonda = &atual->sonda;
            printf("Sonda %d:\n", sonda->Identificador);
            limprimerocha(&sonda->compartimento); // Supondo que essa função imprime as rochas no compartimento
            atual = atual->pProx;
        }
    }
    printf("\n");
        } else if (comando == 'E') {
            printf("Executando redistribuicao...\n");
            MoverSondasParaOrigem(&listasondas);
            RedistribuirRochas(&listasondas);
            printf("Estado atualizado após redistribuicao:\n");
            limprimerocha(&compartimento);
            break;
        } else {
            printf("Comando desconhecido: %c\n", comando);
        }
    }

    printf("Programa finalizado com sucesso.\n");
    return 0;
}
