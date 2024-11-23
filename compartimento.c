#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Compartimento.h"

<<<<<<< HEAD
void FLVazia_R(L_Compart *pLista)
{
    pLista->pPrimeiro = (Apontador_R)malloc(sizeof(Celula_R));
    pLista->pUltimo = pLista->pPrimeiro;
    pLista->pPrimeiro->pProx = NULL;
}

int LTamanho_R(L_Compart *pLista)
{
    int cont = 0;
    Apontador_R pAux = pLista->pPrimeiro->pProx;
    while (pAux != NULL)
    {
        cont += 1;
        pAux = pAux->pProx;
    }
    return cont;
}

int LEhVazia_R(L_Compart *pLista)
{
    return (pLista->pPrimeiro == pLista->pUltimo);
}

int LInsere_R(L_Compart *pLista, rochamineral *pRocha)
{
    pLista->pUltimo->pProx = (Apontador_R)malloc(sizeof(Celula_R));
    pLista->pUltimo = pLista->pUltimo->pProx;
    pLista->pUltimo->rocha = *pRocha;
    pLista->pUltimo->pProx = NULL;
    return 1;
}

void LImprime_R(L_Compart *pLista)
{
    int cont = 1;
    Apontador_R pAux= NULL;
    pAux = pLista->pPrimeiro->pProx;
    while (pAux != NULL)
    {
        printf("Rocha %d\n", cont++);
        printf("ID: %d\n", pAux->rocha.id);
        printf("Peso: %.2f\n", pAux->rocha.peso);
        printf("Localizacao; %.5lf %.5lf\n", pAux->rocha.latitude, pAux->rocha.longitude);
        printf("Categoria: %s\n", pAux->rocha.categoria);
        
        pAux = pAux->pProx;
    }
}

int LRetira_R(L_Compart *pLista, rochamineral *pRocha)
{
    if (LEhVazia_R(pLista))
    {
        return 0;
    }

    Apontador_R pAnterior = NULL;
    Apontador_R pAtual = pLista->pPrimeiro;

    while (pAtual != NULL)
    {
        if (strcmp(pAtual->rocha.categoria, pRocha->categoria) == 0)
        {
            if (pAnterior == NULL)
            {
                pLista->pPrimeiro = pAtual->pProx;
                if (pLista->pPrimeiro == NULL)
                {
                    pLista->pUltimo = NULL;
                }
            }
            else
            {
                pAnterior->pProx = pAtual->pProx;
                if (pAtual == pLista->pUltimo)
                {
                    pLista->pUltimo = pAnterior;
                }
            }
            free(pAtual);
            return 1;
        }
        pAnterior = pAtual;
        pAtual = pAtual->pProx;
    }
    return 0;
}

void LTroca_R(L_Compart *pLista)
{
    // Verifica se a lista está vazia ou tem apenas um elemento. Se sim, não faz nada.
    if (LEhVazia_R(pLista) || pLista->pPrimeiro->pProx == NULL)
    {
=======
void flvaziarocha(tlistarocha* plistarocha) {
    plistarocha->pprimeiro = (Apontador_c)malloc(sizeof(tcelula));
    plistarocha->pultimo = plistarocha->pprimeiro;
    plistarocha->pprimeiro->pprox = NULL;
    plistarocha->contador = 0;
} // faz lista fazia

int lehvaziarocha(tlistarocha* plistarocha) {
    return (plistarocha->pprimeiro == plistarocha->pultimo);
} // confere se a lista esta fazia
void linsererocha(tlistarocha *plistarocha, rochamineral *procha) {
  
    Apontador_c novaCelula = (Apontador_c)malloc(sizeof(tcelula));
    if (novaCelula == NULL) {
        printf("Erro: Falha ao alocar memória para nova rocha.\n");
>>>>>>> efca30ad209a78f56b444e4f2500c2576c8f6b39
        return;
    }

    // Apontador para percorrer a lista
    Apontador_R pAux = pLista->pPrimeiro->pProx;
    // Apontador para a rocha mais pesada
    Apontador_R maisPesada = NULL;
    // Variável para armazenar o peso da rocha mais pesada
    float maiorPeso = 0;

<<<<<<< HEAD
    // Loop para percorrer a lista e encontrar a rocha mais pesada
    while (pAux != NULL)
    {
        // Verifica se a rocha atual tem um peso maior que o maiorPeso registrado
        if (pAux->rocha.peso > maiorPeso)
        {
            maiorPeso = pAux->rocha.peso;
            maisPesada = pAux;
        }
        pAux = pAux->pProx;  // Move para o próximo elemento da lista
    }

    // Se não encontrou nenhuma rocha mais pesada, retorna
    if (maisPesada == NULL)
    {
=======
    plistarocha->pultimo->pprox = novaCelula;
    novaCelula->pprox = NULL;
    plistarocha->pultimo = novaCelula;

    plistarocha->contador++;
}// insere a rocha na lista

void limprimerocha(tlistarocha* plistarocha){
    Apontador_c paux;
    paux=plistarocha->pprimeiro->pprox;
    while(paux!=NULL){
        printf("%s %.2f\n",paux->rocha.categoria, paux->rocha.peso);
        paux=paux->pprox;
    }
}//imprime a rocha

float PesoTotal(tlistarocha* compartimento) {
    float peso = 0.0;
    tcelula* atual = compartimento->pprimeiro->pprox; 

    while (atual != NULL) {
        peso += atual->rocha.peso;
        atual = atual->pprox;
    }
    return peso;
}//calcula o peso compartimento

void OrdenarRochas(tlistarocha *lista) {
    if (lista->pprimeiro == NULL || lista->pprimeiro->pprox == NULL)
>>>>>>> efca30ad209a78f56b444e4f2500c2576c8f6b39
        return;
    }

    // Armazena a categoria da rocha mais pesada
    char categoriaMaisPesada[40];
    strcpy(categoriaMaisPesada, maisPesada->rocha.categoria);

    // Inicializa as variáveis para a rocha mais leve
    Apontador_R maisLeve = NULL;
    Apontador_R anteriorMaisLeve = NULL;
    float menorPeso = -1;  // Inicializa com valor inválido

    // Loop para percorrer a lista novamente e encontrar a rocha mais leve com a mesma categoria
    pAux = pLista->pPrimeiro->pProx;
    Apontador_R pAnt = pLista->pPrimeiro;
    while (pAux != NULL)
    {
        // Verifica se a rocha tem a mesma categoria da rocha mais pesada
        if (strcmp(pAux->rocha.categoria, categoriaMaisPesada) == 0)
        {
            // Se for a primeira rocha ou a rocha atual for mais leve que a mais leve anterior
            if (menorPeso == -1 || pAux->rocha.peso < menorPeso)
            {
                menorPeso = pAux->rocha.peso;
                maisLeve = pAux;
                anteriorMaisLeve = pAnt;
            }
        }
        pAnt = pAux;  // Guarda o anterior
        pAux = pAux->pProx;  // Move para o próximo elemento
    }

    // Se não encontrou uma rocha mais leve com a mesma categoria, retorna
    if (maisLeve == NULL)
    {
        return;
    }

    // Se encontrou uma rocha mais leve e ela é diferente da rocha mais pesada, faz a troca
    if (maisLeve != NULL && maisLeve != maisPesada && maisLeve->rocha.peso < maisPesada->rocha.peso)
    {
        // Troca as rochas entre a mais pesada e a mais leve
        rochamineral temp = maisPesada->rocha;
        maisPesada->rocha = maisLeve->rocha;
        maisLeve->rocha = temp;

        // Atualiza os ponteiros da lista para remover a rocha mais leve
        if (anteriorMaisLeve == NULL)
        {
            pLista->pPrimeiro = maisLeve->pProx;  // Se a rocha mais leve for o primeiro elemento
        }
        else
        {
            anteriorMaisLeve->pProx = maisLeve->pProx;  // Se não for o primeiro, apenas remove
        }

        // Atualiza o ponteiro do último elemento da lista se necessário
        if (maisLeve == pLista->pUltimo)
        {
            pLista->pUltimo = anteriorMaisLeve;
        }

        // Libera a memória alocada para a rocha mais leve
        free(maisLeve);
    }
<<<<<<< HEAD
}
=======
}//ordena rocha em ordem decrescente

void RemoverPrimeiraRocha(tlistarocha *lista, rochamineral *rocha) {
    if (lehvaziarocha(lista)) return; 

    tcelula *aux = lista->pprimeiro->pprox; 
    *rocha = aux->rocha;                           

    lista->pprimeiro->pprox = aux->pprox;        
    if (aux->pprox == NULL)                       
        lista->pultimo = lista->pprimeiro;       

    free(aux);                                  
}//remove rocha da lista
>>>>>>> efca30ad209a78f56b444e4f2500c2576c8f6b39
