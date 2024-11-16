#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include "ListaSondasEspaciais.h"

#include <stdio.h>
#include "rochamineral.h"


void ImprimirRochas(tlistarocha *compartimento) {
    if (lehvaziarocha(compartimento)) {
        printf("compartimento vazio!\n");
        return;
    }

    tcelula *atual = compartimento->pprimeiro->pprox;
    while (atual != NULL) {
        rochamineral *rocha = &atual->rocha;
        printf("%s %.1f\n", rocha->categoria, rocha->peso);
        atual = atual->pprox;
    }
}

void ExecutarComandoI(Tlista *listasondas) {
    if (LehVazia(listasondas)) {
        printf("A lista de sondas esta vazia.\n");
        return;
    }

    TCelula *atual = listasondas->pPrimeiro->pProx;
    while (atual != NULL) {
        DadosSonda *sonda = &atual->sonda;
        printf("%d\n", sonda->Identificador);
        if (lehvaziarocha(&sonda->compartimento)) {
            printf("compartimento vazio!\n");
        } else {
            ImprimirRochas(&sonda->compartimento);
        }
        atual = atual->pProx;
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
            printf("Sonda %d movida para a origem (0,0). Combustivel restante: %.2f\n", sonda->Identificador, sonda->Combustivel);
        } else {
            printf("Sonda %d não possui combustivel suficiente para se mover para a origem.\n", sonda->Identificador);
        }
        atual = atual->pProx;
    }
}


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
        printf("Nenhuma sonda disponivel para redistribuir rochas.\n");
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
        printf("Rocha adicionada a sonda %d (Distancia: %.2f)\n", sondaMaisProxima->Identificador, menorDistancia);
    } else {
        printf("Nenhuma sonda disponível para adicionar a rocha.\n");
    }
}

// Processa o comando para adicionar uma nova rocha
void ProcessarComandoAdicionarRocha(Tlista *listasondas) {
    float latitude, longitude, peso;
    char mineral1[50], mineral2[50];
    scanf("%f %f %f %s %s", &latitude, &longitude, &peso, mineral1, mineral2);

    rochamineral novaRocha;
    tlistamineral listaMinerais;
    flvaziamineral(&listaMinerais);

    if (strcmp(mineral1, "-") != 0) {
        Minerais m1;
        RetornaMineral(&m1, mineral1);
        linsereMineral(&listaMinerais, &m1);
    }
    if (strcmp(mineral2, "-") != 0) {
        Minerais m2;
        RetornaMineral(&m2, mineral2);
        linsereMineral(&listaMinerais, &m2);
    }

    set_idrocha(&novaRocha, GeraIdUnico());
    set_peso(&novaRocha, peso);
    set_localizacao(&novaRocha, &(localizacao){latitude, longitude});
    set_listamineral(&novaRocha, &listaMinerais);
    DefCategoria(&novaRocha);

    AdicionarRochaNaSondaMaisProxima(listasondas, &novaRocha);
}

// Função principal
int main() {
    Tlista listasondas;
    FLvazia(&listasondas);

    int n_sondas;
    printf("Numero de sondas: ");
    scanf("%d", &n_sondas);

    for (int i = 0; i < n_sondas; i++) {
        DadosSonda novaSonda;
        tlistarocha compartimento;
        flvaziarocha(&compartimento);

        printf("Digite os dados da sonda %d: ", i + 1);
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

    printf("Digite o numero de acoes: ");
    int n_acoes;
    scanf("%d", &n_acoes);

    for (int i = 0; i < n_acoes; i++) {

        char comando;
        printf("Digite o comando (R/I/E): ");
        scanf(" %c", &comando); // Adicionei um espaço antes do %c para ignorar qualquer newline pendente

        if (comando == 'R') {
            float latitude, longitude, peso;
            char mineral1[50], mineral2[50];
            scanf("%f %f %f %s %s", &latitude, &longitude, &peso, mineral1, mineral2);

            rochamineral novaRocha;
            strcpy(novaRocha.categoria, mineral1);
            novaRocha.peso = peso;
            novaRocha.localizacao.latituderocha = latitude;
            novaRocha.localizacao.longituderocha = longitude;

            AdicionarRochaNaSondaMaisProxima(&listasondas, &novaRocha);
            printf("Rocha de categoria %s (%.1f kg) adicionada na sonda mais próxima.\n", 
           novaRocha.categoria, novaRocha.peso);
        } 
        else if (comando == 'I') {
            ExecutarComandoI(&listasondas);
                  
        } else if (comando == 'E') {
            printf("Executando redistribuição...\n");
            MoverSondasParaOrigem(&listasondas);
            RedistribuirRochas(&listasondas);
        } else {
            printf("Comando desconhecido: %c\n", comando);
        }
    }

    printf("Programa finalizado com sucesso.\n");
    return 0;
}
