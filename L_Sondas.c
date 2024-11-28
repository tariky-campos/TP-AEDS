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
// Função que calcula a distância euclidiana entre um ponto (lat_r, long_r)
// e as sondas na lista, retornando a sonda mais próxima ou a segunda mais próxima
// que tenha capacidade suficiente para transportar a rocha.
DadosSonda *CalcularEuclidiana(L_Sondas *pLista_S, double lat_r, double long_r, rochamineral *rocha) {
    // Inicializa um ponteiro auxiliar para percorrer a lista de sondas
    Apontador_S pAux = pLista_S->pPrimeiro->pProx;
    
    // Ponteiros para armazenar a sonda mais próxima e a segunda mais próxima
    DadosSonda *primeiraSonda = NULL, *segundaSonda = NULL;
    
    // Variáveis para armazenar as menores distâncias encontradas
    double menorDist = 9999999, segundaMenorDist = 9999999;
    
    // Variáveis temporárias para latitude, longitude e distância da sonda atual
    double lat_i, long_i, distSonda;

    // Percorre a lista de sondas
    while (pAux != NULL) {
        // Obtém a latitude e longitude da sonda atual
        lat_i = pAux->sonda.latitude;
        long_i = pAux->sonda.longitude;
        
        // Calcula a distância euclidiana entre o ponto de referência e a sonda
        distSonda = sqrt(pow(lat_r - lat_i, 2) + pow(long_r - long_i, 2));

        // Verifica se essa distância é menor que a menor distância registrada
        if (distSonda < menorDist) {
            // Atualiza a segunda menor distância e a segunda sonda
            segundaMenorDist = menorDist;
            segundaSonda = primeiraSonda;
            
            // Atualiza a menor distância e a sonda mais próxima
            menorDist = distSonda;
            primeiraSonda = &pAux->sonda;
        }
        // Verifica se a distância é menor que a segunda menor distância, mas maior que a menor
        else if (distSonda < segundaMenorDist) {
            segundaMenorDist = distSonda;
            segundaSonda = &pAux->sonda;
        }
        
        // Avança para o próximo nó na lista
        pAux = pAux->pProx;
    }

    // Verifica se a sonda mais próxima tem capacidade para carregar a rocha
    if (primeiraSonda != NULL && PesoSonda(primeiraSonda) + rocha->peso <= primeiraSonda->capacidade) {
        return primeiraSonda; // Retorna a sonda mais próxima
    }
    // Verifica se a segunda sonda mais próxima tem capacidade para carregar a rocha
    else if (segundaSonda != NULL && PesoSonda(segundaSonda) + rocha->peso <= segundaSonda->capacidade) {
        return segundaSonda; // Retorna a segunda sonda mais próxima
    }

    // Retorna a sonda mais próxima como fallback, mesmo sem verificar capacidade
    return primeiraSonda;
}


// Insere uma rocha em uma sonda próxima
void Insere_S(L_Sondas *pLista_S, rochamineral *rocha) {
    DadosSonda *sondaTemp = CalcularEuclidiana(pLista_S, rocha->latitude, rocha->longitude, rocha);

    if (sondaTemp == NULL) {
        printf("Nao ha sonda perto!\n");
        return; // Sai se nenhuma sonda próxima for encontrada
    }

    if (PesoSonda(sondaTemp) + rocha->peso > sondaTemp->capacidade) {
        // Lida com o caso de capacidade insuficiente
        Apontador_R pAux = sondaTemp->Compar_Rocha.pPrimeiro->pProx;
        Apontador_R rochaMaisPesada = NULL;
        float maiorPeso = 0;

        while (pAux != NULL) {// Verfica se a um rocha maior da mesma categoria
            if (strcmp(pAux->rocha.categoria, rocha->categoria) == 0 && pAux->rocha.peso > maiorPeso) {
                maiorPeso = pAux->rocha.peso;
                rochaMaisPesada = pAux;
            }
            pAux = pAux->pProx;
        }

        if (rochaMaisPesada != NULL && rochaMaisPesada->rocha.peso < rocha->peso) {
            rochaMaisPesada->rocha = *rocha; // Substitui pela rocha mais leve
            printf("Rocha coletada pela sonda %d TROCADA PELA MAIS LEVE.\n", sondaTemp->idSonda);
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
void MoverParaOrigem(L_Sondas *pLista_S) {
    Apontador_S pAux = NULL; // Ponteiro auxiliar para percorrer a lista
    pAux = pLista_S->pPrimeiro; // Começa na primeira sonda da lista
    while (pAux != NULL) {
        pAux->sonda.latitude = 0.0;  // Define a latitude como 0
        pAux->sonda.longitude = 0.0; // Define a longitude como 0
        pAux = pAux->pProx;          // Avança para a próxima sonda
    }
}

// Função para criar uma cópia profunda de uma estrutura de rocha mineral
rochamineral *RochaTEMP(rochamineral *rocha) {
    // Aloca memória para a nova estrutura de rocha
    rochamineral *RochaTEMP = (rochamineral *)malloc(sizeof(rochamineral));
    if (RochaTEMP == NULL) { // Verifica se a memória foi alocada
        perror("Erro ao alocar memória para cópia da rocha");
        return NULL;
    }
    *RochaTEMP = *rocha; // Copia os dados primários da estrutura original

    // Inicializa a lista de minerais da nova rocha
    FLVazia_L(&RochaTEMP->L_Mineral);

    // Copia cada mineral da lista original para a nova rocha
    for (int i = rocha->L_Mineral.pPrimeiro; i < rocha->L_Mineral.pUltimo; i++) {
        LInsere_L(&RochaTEMP->L_Mineral, rocha->L_Mineral.ListaMINERAIS[i]);
    }

    return RochaTEMP; // Retorna a nova cópia
}

// Função para extrair todas as rochas de uma lista de sondas e colocá-las em um array
rochamineral *NovaListaTempRocha(L_Sondas *pLista_S, int *numRochas) {
    *numRochas = 0; // Inicializa o contador de rochas
    Apontador_S pAuxSonda = pLista_S->pPrimeiro->pProx; // Ponteiro para percorrer as sondas

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
    pAuxSonda = pLista_S->pPrimeiro->pProx; // Reinicia o ponteiro para sondas

    // Percorre novamente as sondas para extrair as rochas
    while (pAuxSonda != NULL) {
        Apontador_R pAuxRocha = pAuxSonda->sonda.Compar_Rocha.pPrimeiro->pProx;
        while (pAuxRocha != NULL) {
            // Faz uma cópia da rocha atual e armazena no array
            rochas[indiceRocha] = *RochaTEMP(&pAuxRocha->rocha);

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
int OrdenarPorPeso(const void *a, const void *b) {

    rochamineral *rocha1 = (rochamineral *)a;
    rochamineral *rocha2 = (rochamineral *)b;
    // Compara os pesos das rochas em ordem decrescente
    return (rocha2->peso > rocha1->peso) - (rocha2->peso < rocha1->peso);
}

// Função para redistribuir as rochas entre as sondas
void Redistribuir(L_Sondas *pLista_S, rochamineral *rochas, int numRochas) {
    if (rochas == NULL || numRochas == 0) {
        return; // Retorna se não há rochas para distribuir
    }

/////// ordena as rochas em ordem decrescente de peso, priorizando as mais pesadas
    qsort(rochas, numRochas, sizeof(rochamineral), OrdenarPorPeso);


    int numSondas = 0; // Contador de sondas
    Apontador_S pAux = pLista_S->pPrimeiro->pProx;

    // Conta o número de sondas
    while (pAux != NULL) {
        numSondas++;
        pAux = pAux->pProx;
    }

    // Aloca memória para rastrear o peso acumulado de cada sonda
    float *PesoSondass = (float *)calloc(numSondas, sizeof(float));
    if (PesoSondass == NULL) { // Verifica a alocação
        perror("Erro ao alocar memória para pesos das sondas");
        return;
    }

    // Distribui as rochas entre as sondas
    for (int i = 0; i < numRochas; i++) {
        int sondaEscolhida = -1;

        // Procura a sonda com menor peso que possa receber a rocha
        for (int j = 0; j < numSondas; j++) {
            pAux = pLista_S->pPrimeiro->pProx;
            float menorPeso = -1;
            int indiceMenorPeso = -1;
            
            for (int k = 0; k < numSondas; k++) {
            // Verifica se a sonda atual possui o menor peso acumulado até agora 
            // e se tem capacidade suficiente para suportar o peso da rocha.
                if ((indiceMenorPeso == -1 || PesoSondass[k] < menorPeso) &&
                    pAux->sonda.capacidade >= PesoSondass[k] + rochas[i].peso) {
                    indiceMenorPeso = k;
                    menorPeso = PesoSondass[k];
                    // Atualiza o índice da sonda selecionada e o menor peso acumulado
                }
                pAux = pAux->pProx;
            }

            if (indiceMenorPeso != -1) {
                // Verifica se foi encontrada uma sonda válida para alocar a rocha.
                sondaEscolhida = indiceMenorPeso;
                pAux = pLista_S->pPrimeiro->pProx;
                // Reinicializa o ponteiro auxiliar para percorrer novamente a lista.
                for (int k = 0; k < sondaEscolhida; k++) {
                    pAux = pAux->pProx;
                }

                if (!LInsere_R(&pAux->sonda.Compar_Rocha, &rochas[i])) {
                    printf("Erro ao inserir rocha na lista\n");
                }
                PesoSondass[sondaEscolhida] += rochas[i].peso;
                // Atualiza o peso acumulado da sonda escolhida, adicionando o peso da nova rocha.
                break; // Sai após inserir a rocha
            }
        }

        // Caso nenhuma sonda possa receber a rocha
        if (sondaEscolhida == -1) {
            printf("A rocha %d foi descartada (sem capacidade nas sondas).\n", rochas[i].id);
        }
    }

    free(PesoSondass); // Libera memória dos pesos
}

// Função principal para redistribuir rochas e mover sondas para a origem
void OperacaoE(L_Sondas *pLista_S) {
    int numRochas = 0;
    // Extrai as rochas de todas as sondas
    rochamineral *rochas = NovaListaTempRocha(pLista_S, &numRochas);

    if (rochas != NULL) {
        // Redistribui as rochas entre as sondas
        Redistribuir(pLista_S, rochas, numRochas);
        free(rochas); // Libera a memória do array de rochas
    } else {
        printf("Nenhuma rocha para redistribuir.\n");
    }

    // Move todas as sondas para a origem
    MoverParaOrigem(pLista_S);
    printf("\nRochas redistribuidas com sucesso!!\n");

}
void OperacaoI(L_Sondas *pLista_Sonda) {
    Apontador_S pAux = pLista_Sonda->pPrimeiro->pProx;

    while (pAux != NULL)
    {
        DadosSonda *pSonda = &pAux->sonda;
        printf("\nSonda: %d\n", pSonda->idSonda);

        if (LEhVazia_R(&pSonda->Compar_Rocha)){
            printf("Compartimento vazio!\n");
        }
        else{
            Apontador_R rAux = pSonda->Compar_Rocha.pPrimeiro->pProx;
            while (rAux != NULL){
                printf("%s %.2f\n", rAux->rocha.categoria, rAux->rocha.peso);
                rAux = rAux->pProx;
            }
        }
        pAux = pAux->pProx;
    }
}