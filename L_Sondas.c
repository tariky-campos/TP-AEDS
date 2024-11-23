#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "L_Sondas.h"

// Inicializa a lista de sondas vazia
void FLVazia_S(L_Sondas *L_Sondas) {
    L_Sondas->pPrimeiro = (Apontador_S)malloc(sizeof(Celula_S)); // Aloca a célula cabeça
    L_Sondas->pUltimo = L_Sondas->pPrimeiro; // Inicializa o último apontando para o primeiro
    L_Sondas->pPrimeiro->pProx = NULL; // Define o próximo da célula cabeça como NULL
}

// Insere uma nova sonda no final da lista
int LInsere_S(L_Sondas *L_Sondas, DadosSonda *pSonda) {
    L_Sondas->pUltimo->pProx = (Apontador_S)malloc(sizeof(Celula_S)); // Aloca nova célula
    L_Sondas->pUltimo = L_Sondas->pUltimo->pProx; // Move o ponteiro do último
    L_Sondas->pUltimo->sonda = *pSonda; // Copia os dados da sonda para a nova célula
    L_Sondas->pUltimo->pProx = NULL; // Define o próximo como NULL
    return 1; // Retorna sucesso
}

// Remove uma sonda com base no ID
int LRetira_S(L_Sondas *L_Sondas, DadosSonda *pSonda) {
    if (L_Sondas == NULL || L_Sondas->pPrimeiro == NULL) {
        return 0; // Retorna falha se a lista for nula ou vazia
    }

    Apontador_S pAnterior = NULL, pAtual = L_Sondas->pPrimeiro;

    // Percorre a lista em busca da sonda a ser removida
    while (pAtual != NULL) {
        if (pAtual->sonda.idSonda == pSonda->idSonda) {
            if (pAnterior == NULL) {
                L_Sondas->pPrimeiro = pAtual->pProx; // Caso seja a primeira célula
            } else {
                pAnterior->pProx = pAtual->pProx; // Atualiza o ponteiro anterior
            }

            if (pAtual == L_Sondas->pUltimo) {
                L_Sondas->pUltimo = pAnterior; // Atualiza o último, se necessário
            }

            free(pAtual); // Libera a memória
            return 1; // Retorna sucesso
        }
        pAnterior = pAtual;
        pAtual = pAtual->pProx;
    }
    return 0; // Retorna falha caso não encontre a sonda
}

// Imprime os dados de todas as sondas na lista
void Imprime_S(L_Sondas *L_Sondas) {
    Apontador_S pAux = L_Sondas->pPrimeiro->pProx; // Começa após a célula cabeça
    while (pAux != NULL) {
        printf("ID: %d\n", pAux->sonda.idSonda);
        printf("Rocha(s): %s\n", pAux->sonda.Compar_Rocha.pPrimeiro->rocha.categoria);
        printf("Latitude e longitude: %.6f %.6f\n", pAux->sonda.latitude, pAux->sonda.longitude);
        printf("Capacidade: %.2f\n", pAux->sonda.capacidade);
        printf("Status da sonda: %s\n\n", pAux->sonda.EstaLigada);
        pAux = pAux->pProx;
    }
}

// Calcula a distância euclidiana para encontrar a sonda mais próxima de uma rocha
DadosSonda *CalcularEuclidiana(L_Sondas *ListaS, double lat_r, double long_r, rochamineral *rocha) {
    Apontador_S pAux = ListaS->pPrimeiro->pProx;
    DadosSonda *primeiraSonda = NULL, *segundaSonda = NULL;
    double menorDist = INFINITY, segundaMenorDist = INFINITY;
    double lat_i, long_i, distSonda;

    while (pAux != NULL) {
        lat_i = pAux->sonda.latitude;
        long_i = pAux->sonda.longitude;
        distSonda = sqrt(pow(lat_r - lat_i, 2) + pow(long_r - long_i, 2)); // Distância euclidiana

        if (distSonda < menorDist) {
            segundaMenorDist = menorDist; // Atualiza a segunda menor distância
            segundaSonda = primeiraSonda;
            menorDist = distSonda;
            primeiraSonda = &pAux->sonda;
        } else if (distSonda < segundaMenorDist) {
            segundaMenorDist = distSonda;
            segundaSonda = &pAux->sonda;
        }
        pAux = pAux->pProx;
    }

    if (primeiraSonda != NULL && PesoSonda(primeiraSonda) + rocha->peso <= primeiraSonda->capacidade) {
        return primeiraSonda; // Retorna a primeira sonda, se houver capacidade
    } else if (segundaSonda != NULL && PesoSonda(segundaSonda) + rocha->peso <= segundaSonda->capacidade) {
        return segundaSonda; // Retorna a segunda sonda
    }
    return primeiraSonda; // Retorna a sonda mais próxima, caso contrário
}

// Insere uma rocha em uma sonda próxima
void Insere_S(L_Sondas *ListaS, rochamineral *rocha) {
    DadosSonda *sondaTemp = CalcularEuclidiana(ListaS, rocha->latitude, rocha->longitude, rocha);

    if (sondaTemp == NULL) {
        printf("Nao ha sonda perto!\n");
        return; // Sai se nenhuma sonda próxima for encontrada
    }

    if (PesoSonda(sondaTemp) + rocha->peso > sondaTemp->capacidade) {
        // Lida com o caso de capacidade insuficiente
        Apontador_R pAux = sondaTemp->Compar_Rocha.pPrimeiro->pProx;
        Apontador_R rochaMaisPesada = NULL;
        float maiorPeso = 0;

        while (pAux != NULL) {
            if (strcmp(pAux->rocha.categoria, rocha->categoria) == 0 && pAux->rocha.peso > maiorPeso) {
                maiorPeso = pAux->rocha.peso;
                rochaMaisPesada = pAux;
            }
            pAux = pAux->pProx;
        }

        if (rochaMaisPesada != NULL && rochaMaisPesada->rocha.peso > rocha->peso) {
            rochaMaisPesada->rocha = *rocha; // Substitui pela rocha mais pesada
            printf("Rocha coletada pela sonda %d (troca por rocha mais pesada).\n", sondaTemp->idSonda);
        } else {
            printf("Impossivel coletar ou trocar rochas. Rocha descartada.\n");
        }
    } else {
        // Insere a rocha normalmente
        sondaTemp->latitude = rocha->latitude;
        sondaTemp->longitude = rocha->longitude;
        if (!LInsere_R(&sondaTemp->Compar_Rocha, rocha)) {
            printf("\nErro ao inserir rocha na sonda %d.\n", sondaTemp->idSonda);
        }
    }
}

// Função para mover todas as sondas para a posição de origem (0,0)
void MoveOrigem(L_Sondas *ListaS) {
    Apontador_S pAux = NULL; // Ponteiro auxiliar para percorrer a lista
    pAux = ListaS->pPrimeiro; // Começa na primeira sonda da lista
    while (pAux != NULL) {
        pAux->sonda.latitude = 0.0;  // Define a latitude como 0
        pAux->sonda.longitude = 0.0; // Define a longitude como 0
        pAux = pAux->pProx;          // Avança para a próxima sonda
    }
}

// Função para criar uma cópia profunda de uma estrutura de rocha mineral
rochamineral *copiaRocha(rochamineral *rocha) {
    // Aloca memória para a nova estrutura de rocha
    rochamineral *copiaRocha = (rochamineral *)malloc(sizeof(rochamineral));
    if (copiaRocha == NULL) { // Verifica se a memória foi alocada
        perror("Erro ao alocar memória para cópia da rocha");
        return NULL;
    }
    *copiaRocha = *rocha; // Copia os dados primários da estrutura original

    // Inicializa a lista de minerais da nova rocha
    FLVazia_L(&copiaRocha->L_Mineral);

    // Copia cada mineral da lista original para a nova rocha
    for (int i = rocha->L_Mineral.pPrimeiro; i < rocha->L_Mineral.pUltimo; i++) {
        LInsere_L(&copiaRocha->L_Mineral, rocha->L_Mineral.ListaMINERAIS[i]);
    }

    return copiaRocha; // Retorna a nova cópia
}

// Função para extrair todas as rochas de uma lista de sondas e colocá-las em um array
rochamineral *extraiRochas(L_Sondas *ListaS, int *numRochas) {
    *numRochas = 0; // Inicializa o contador de rochas
    Apontador_S pAuxSonda = ListaS->pPrimeiro->pProx; // Ponteiro para percorrer as sondas

    // Conta o número total de rochas em todas as sondas
    while (pAuxSonda != NULL) {
        Apontador_R pAuxRocha = pAuxSonda->sonda.Compar_Rocha.pPrimeiro->pProx; // Ponteiro para as rochas
        while (pAuxRocha != NULL) {
            (*numRochas)++;   // Incrementa o contador de rochas
            pAuxRocha = pAuxRocha->pProx; // Avança para a próxima rocha
        }
        pAuxSonda = pAuxSonda->pProx; // Avança para a próxima sonda
    }

    if (*numRochas == 0) {
        return NULL; // Retorna NULL se não houver rochas
    }

    // Aloca memória para armazenar as rochas extraídas
    rochamineral *rochas = (rochamineral *)malloc(*numRochas * sizeof(rochamineral));
    if (rochas == NULL) { // Verifica se a alocação foi bem-sucedida
        perror("Erro ao alocar memória para rochas");
        return NULL;
    }

    int indiceRocha = 0; // Índice do array de rochas
    pAuxSonda = ListaS->pPrimeiro->pProx; // Reinicia o ponteiro para sondas

    // Percorre novamente as sondas para extrair as rochas
    while (pAuxSonda != NULL) {
        Apontador_R pAuxRocha = pAuxSonda->sonda.Compar_Rocha.pPrimeiro->pProx;
        while (pAuxRocha != NULL) {
            // Faz uma cópia da rocha atual e armazena no array
            rochas[indiceRocha] = *copiaRocha(&pAuxRocha->rocha);

            Apontador_R temp = pAuxRocha;  // Salva a referência à rocha atual
            pAuxRocha = pAuxRocha->pProx; // Avança para a próxima rocha
            free(temp);                   // Libera a memória da rocha extraída
            indiceRocha++;                // Incrementa o índice do array
        }

        FLVazia_R(&pAuxSonda->sonda.Compar_Rocha); // Limpa a lista de rochas da sonda
        pAuxSonda = pAuxSonda->pProx; // Avança para a próxima sonda
    }

    return rochas; // Retorna o array de rochas extraídas
}

// Função de comparação para ordenar rochas por peso (usada em qsort)
int comparaRochas(const void *a, const void *b) {
    rochamineral *rocha1 = (rochamineral *)a;
    rochamineral *rocha2 = (rochamineral *)b;
    // Compara os pesos das rochas em ordem decrescente
    return (rocha2->peso > rocha1->peso) - (rocha2->peso < rocha1->peso);
}

// Função para redistribuir as rochas entre as sondas
void distribuirRochas(L_Sondas *ListaS, rochamineral *rochas, int numRochas) {
    if (rochas == NULL || numRochas == 0) {
        return; // Retorna se não há rochas para distribuir
    }

    // Ordena as rochas por peso decrescente
    qsort(rochas, numRochas, sizeof(rochamineral), comparaRochas);

    int numSondas = 0; // Contador de sondas
    Apontador_S pAux = ListaS->pPrimeiro->pProx;

    // Conta o número de sondas
    while (pAux != NULL) {
        numSondas++;
        pAux = pAux->pProx;
    }

    // Aloca memória para rastrear o peso atual de cada sonda
    float *pesosSondas = (float *)calloc(numSondas, sizeof(float));
    if (pesosSondas == NULL) { // Verifica a alocação
        perror("Erro ao alocar memória para pesos das sondas");
        return;
    }

    // Distribui as rochas entre as sondas
    for (int i = 0; i < numRochas; i++) {
        int sondaEscolhida = -1;

        // Procura a sonda com menor peso que possa receber a rocha
        for (int j = 0; j < numSondas; j++) {
            pAux = ListaS->pPrimeiro->pProx;
            float menorPeso = -1;
            int indiceMenorPeso = -1;
            
            for (int k = 0; k < numSondas; k++) {
                if ((indiceMenorPeso == -1 || pesosSondas[k] < menorPeso) &&
                    pAux->sonda.capacidade >= pesosSondas[k] + rochas[i].peso) {
                    indiceMenorPeso = k;
                    menorPeso = pesosSondas[k];
                }
                pAux = pAux->pProx;
            }

            if (indiceMenorPeso != -1) {
                sondaEscolhida = indiceMenorPeso;
                pAux = ListaS->pPrimeiro->pProx;
                for (int k = 0; k < sondaEscolhida; k++) {
                    pAux = pAux->pProx;
                }

                if (!LInsere_R(&pAux->sonda.Compar_Rocha, &rochas[i])) {
                    printf("Erro ao inserir rocha na lista\n");
                }
                pesosSondas[sondaEscolhida] += rochas[i].peso;
                break; // Sai após inserir a rocha
            }
        }

        // Caso nenhuma sonda possa receber a rocha
        if (sondaEscolhida == -1) {
            printf("A rocha %d foi descartada (sem capacidade nas sondas).\n", rochas[i].id);
        }
    }

    free(pesosSondas); // Libera memória dos pesos
}

// Função principal para redistribuir rochas e mover sondas para a origem
void OperacaoE(L_Sondas *ListaS) {
    int numRochas = 0;
    // Extrai as rochas de todas as sondas
    rochamineral *rochas = extraiRochas(ListaS, &numRochas);

    if (rochas != NULL) {
        // Redistribui as rochas entre as sondas
        distribuirRochas(ListaS, rochas, numRochas);
        free(rochas); // Libera a memória do array de rochas
    } else {
        printf("Nenhuma rocha para redistribuir.\n");
    }

    // Move todas as sondas para a origem
    MoveOrigem(ListaS);
    printf("\nRochas redistribuidas com sucesso!!\n");
}
void OperacaoI(L_Sondas *ListaSonda) {
    Apontador_S pAux = ListaSonda->pPrimeiro->pProx;

    while (pAux != NULL)
    {
        DadosSonda *pSonda = &pAux->sonda;
        printf("%d\n", pSonda->idSonda);

        if (LEhVazia_R(&pSonda->Compar_Rocha))
        {
            printf("Compartimento vazio!\n");
            /* Se o compartimento estiver vazio, imprime o id da sonda e
            'compartimento vazio!' */
        }
        else
        {
            Apontador_R rAux = pSonda->Compar_Rocha.pPrimeiro->pProx;

            while (rAux != NULL)
            {
                printf("%s %.2f\n", rAux->rocha.categoria, rAux->rocha.peso);
                rAux = rAux->pProx;
            }
        }
        pAux = pAux->pProx;
    }
}