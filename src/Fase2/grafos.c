/**
 * @file grafos.c
 * @author Rodrigo Lopes Ferreira Nº 31525 
 * @brief Implementação das operações de grafos para antenas.
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "grafos.h"


#pragma region | Inserir | Remover | Adjacências e Vértices

#pragma region Criar e inserir Adjacências e Vértices

/**
 * @brief Cria e insere uma nova adjacência na lista de adjacências de um vértice.
 * @param vertice Vértice onde a adjacência será inserida.
 * @param destino Vértice de destino da adjacência.
 * @return 0 se o grafo foi guardado com sucesso, 1 caso contrário.
 */
int criarInserirAdj(Vertice *vertice, Vertice *destino) {
    Adj* novaAdj = (Adj*)malloc(sizeof(Adj));
    if (novaAdj == NULL) {
        return -1;
    }
    novaAdj->destino = destino;
    novaAdj->proxima = vertice->adj;
    vertice->adj     = novaAdj;
    return 0;
}

/**
 * @brief Cria e insere um novo vértice com os dados de 'info'.
 * @param info Estrutura Antena com frequência e coords.
 * @return Ponteiro para o vértice (visitado inicializado a 0, adj = NULL).
 */
Vertice* criarInserirVert(Vertice *grafo, Antena info) {
    // Aloca memória para o novo vértice
    Vertice* novoVertice = (Vertice*)malloc(sizeof(Vertice));
    if (novoVertice == NULL) {
        return grafo; // Se der erro, devolve o grafo como estava
    }

    // Inicializa os campos do novo vértice
    novoVertice->info = info;
    novoVertice->visitado = 0; // Inicializa como não visitado
    novoVertice->adj = NULL;   // Lista de adjacências vazia

    // Insere o novo vértice no início da lista de vértices
    novoVertice->proximo = grafo;
    grafo = novoVertice;

    return grafo; // Retorna o novo início da lista de vértices
}

#pragma endregion

#pragma region Remover Adjacências e Vértices

#pragma region Funções auxiliares para arestas removidas

// Lista global de arestas removidas
ArestaRemovida *arestasRemovidas = NULL;

/**
 * @brief Regista uma aresta removida na lista de arestas removidas.
 * @param origem Vértice de origem da aresta removida.
 * @param destino Vértice de destino da aresta removida.
 * @return 0 se o grafo foi guardado com sucesso, 1 caso contrário.
 */
int registrarArestaRemovida(Vertice *origem, Vertice *destino) {
    ArestaRemovida *nova = (ArestaRemovida*)malloc(sizeof(ArestaRemovida));
    if (nova == NULL) return -1;
    nova->origem  = origem;
    nova->destino = destino;
    nova->proxima = arestasRemovidas;
    arestasRemovidas = nova;
    return 0;
}

/**
 * @brief Verifica se uma aresta foi removida.
 * @param origem Vértice de origem da aresta.
 * @param destino Vértice de destino da aresta.
 * @return 1 se a aresta foi removida, 0 caso contrário.
 */
int isArestaRemovida(Vertice *origem, Vertice *destino) {
    for (ArestaRemovida *a = arestasRemovidas; a != NULL; a = a->proxima) {
        if (a->origem == origem && a->destino == destino) {
            return 1;
        }
    }
    return 0;
}

#pragma endregion

/**
 * @brief Remove uma adjacência da lista de adjacências do vértice.
 * @param vertice Vértice onde a adjacência será removida.
 * @param destino Ponteiro para a adjacência a ser removida.
 * @return 0 se o grafo foi guardado com sucesso, 1 caso contrário.
 */
int removerAdj(Vertice *vertice, Vertice *destino) {
    Adj *atual = vertice->adj, *anterior = NULL;
    while (atual) {
        if (atual->destino == destino) {
            if (anterior) anterior->proxima = atual->proxima;
            else          vertice->adj     = atual->proxima;
            registrarArestaRemovida(vertice, destino);
            free(atual);
            return 0;
        }
        anterior = atual;
        atual    = atual->proxima;
    }
    return 1;
}

/**
 * @brief Remove um vértice da lista de vértices do grafo e elimina as arestas associadas.
 * @param grafo Ponteiro para a cabeça da lista de vértices.
 * @param x Coordenada x do vértice a remover.
 * @param y Coordenada y do vértice a remover.
 * @return Novo ponteiro para a cabeça da lista de vértices.
 */
Vertice* removerVertice(Vertice *grafo, int x, int y) {
    Vertice *anterior = NULL;
    Vertice *atual = grafo;

    // procurar o vértice a remover
    while (atual != NULL) {
        if (atual->info.x == x && atual->info.y == y) {
            break;
        }
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        return grafo; // nao encontrado
    }

    for (Vertice *v = grafo; v != NULL; v = v->proximo) {
        Adj *prev = NULL;
        Adj *adj = v->adj;
        while (adj != NULL) {
            if (adj->destino == atual) {
                // Remover a adjacência
                if (prev == NULL) {
                    v->adj = adj->proxima;
                } else {
                    prev->proxima = adj->proxima;
                }
                Adj *aRemover = adj;
                adj = adj->proxima;
                free(aRemover);
            } else {
                prev = adj;
                adj = adj->proxima;
            }
        }
    }

    Adj *a = atual->adj;
    while (a != NULL) {
        Adj *seguinte = a->proxima;
        free(a);
        a = seguinte;
    }

    if (anterior == NULL) {
        grafo = atual->proximo; // era o primeiro
    } else {
        anterior->proximo = atual->proximo;
    }

    free(atual);
    return grafo;
}

#pragma endregion

#pragma endregion


#pragma region Carregar Grafo

/**
 * @brief Constrói o grafo de antenas a partir de ficheiro.
 * @param filename Caminho para o ficheiro de antenas.
 * @return Cabeça da lista de vértices (grafo).
 * @note Este algoritmo foi adaptado da fase 1.
 */
Vertice* carregarGrafo(const char *filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        return NULL; // se não abrir o ficheiro, devolve NULL
    }
 
    Vertice *grafo = NULL;
    int numLinha = 0;
    char texto[50];
 
    while (fgets(texto, 50, file)) {
        //tal cena do \0
        for (int pos = 0; texto[pos] != '\0' && texto[pos] != '\n'; pos++) {
            if (texto[pos] != '.') {
                // insere cada cada letra como um vértice
                grafo = criarInserirVert(grafo, (Antena){texto[pos], pos, numLinha});
            }
        }
        numLinha++;
    }
    fclose(file);
    return grafo;
}

#pragma endregion


#pragma region Encontrar Vértice

/**
 * @brief Procura vértice pelas coordenadas (x,y).
 * @param grafo Ponteiro para a cabeça da lista de vértices.
 * @param x Coordenada x do vértice a procurar.
 * @param y Coordenada y do vértice a procurar.     
 * @return Ponteiro para o vértice encontrado ou NULL se não encontrado.
 */
Vertice* encontraVertice(Vertice *grafo, int x, int y) {
    Vertice *atual = grafo;
    while (atual != NULL) {
        if (atual->info.x == x && atual->info.y == y) {
            return atual; // Vértice encontrado
        }
        atual = atual->proximo; // Avança para o próximo vértice
    }
    return NULL; // Vértice não encontrado
}

#pragma endregion


#pragma region Construir Grafo

/**
 * @brief Constrói o grafo de antenas a partir de um conjunto de vértices.
 * @param grafo Cabeça da lista ligada de vértices.
 * @return 0 se o grafo foi guardado com sucesso, 1 caso contrário.
 */
int construirGrafo(Vertice *grafo) {
    for (Vertice *v1 = grafo; v1 != NULL; v1 = v1->proximo) {
        for (Vertice *v2 = grafo; v2 != NULL; v2 = v2->proximo) {
            if (v1 != v2 && v1->info.frequencia == v2->info.frequencia) {
                // Evita adicionar aresta duplicada ou recriar aresta removida
                int jaLigado = 0;
                for (Adj *adj = v1->adj; adj != NULL; adj = adj->proxima) {
                    if (adj->destino == v2) {
                        jaLigado = 1;
                        break;
                    }
                }
                if (!jaLigado && !isArestaRemovida(v1, v2)) {
                    criarInserirAdj(v1, v2);
                }
            }
        }
    }

    // Mostra as ligações (lista de adjacência)
    for (Vertice *v = grafo; v != NULL; v = v->proximo) {
        printf("(%d,%d)", v->info.x, v->info.y);
        for (Adj *adj = v->adj; adj != NULL; adj = adj->proxima) {
            printf(" -> (%d,%d)", adj->destino->info.x, adj->destino->info.y);
        }
        printf("\n");
    }

    return 0;
}

#pragma endregion


#pragma region DFS

/**
 * @brief Realiza uma busca em profundidade (DFS) a partir de um vértice inicial.
 * @param inicio Vértice inicial para a busca.
 * @return 0 se o grafo foi guardado com sucesso, 1 caso contrário.
 */
int dfs(Vertice *inicio) {
    if (!inicio) return 1;
    for (Vertice *v = inicio; v; v = v->proximo) v->visitado = 0;

    Vertice *stack[100];
    int topo = 0;
    stack[topo++] = inicio;

    while (topo) {
        Vertice *v = stack[--topo];
        if (!v->visitado) {
            v->visitado = 1;
            printf("(%d,%d)\n", v->info.x, v->info.y);
            for (Adj *a = v->adj; a; a = a->proxima)
                if (!a->destino->visitado) stack[topo++] = a->destino;
        }
    }
    return 0;
}

#pragma endregion


#pragma region BFS

/**
 * @brief Realiza uma busca em largura (BFS) a partir de um vértice inicial.
 * @param inicio Vértice inicial para a busca.
 * @return 0 se o grafo foi guardado com sucesso, 1 caso contrário.
 */
int bfs(Vertice *inicio) {
    if (!inicio) return 1;
    for (Vertice *v = inicio; v; v = v->proximo) v->visitado = 0;

    Vertice *fila[100];
    int frente = 0, tras = 0;
    fila[tras++]    = inicio;
    inicio->visitado = 1;

    while (frente < tras) {
        Vertice *v = fila[frente++];
        printf("(%d,%d)\n", v->info.x, v->info.y);
        for (Adj *a = v->adj; a; a = a->proxima)
            if (!a->destino->visitado) {
                a->destino->visitado = 1;
                fila[tras++]         = a->destino;
            }
    }
    return 0;
}

#pragma endregion


#pragma region Listar Interseções A e B

/**
 * @brief Lista as interseções entre dois conjuntos de vértices.
 * @param grafo Cabeça da lista ligada de vértices.
 * @param freqA Frequência do conjunto A.
 * @param freqB Frequência do conjunto B.
 * @return 0 se o grafo foi guardado com sucesso, 1 caso contrário.
 */
int listarIntersecoes(Vertice *grafo, char freqA, char freqB) {
    for (Vertice *v = grafo; v != NULL; v = v->proximo) {
        for (Adj *a = v->adj; a != NULL; a = a->proxima) {
            Vertice *dest = a->destino;

            // Frequências diferentes e interligadas
            if ((v->info.frequencia == freqA && dest->info.frequencia == freqB) ||
                (v->info.frequencia == freqB && dest->info.frequencia == freqA)) {

                // Para evitar mostrar o par 2 vezes (ex: A->0 e 0->A)
                if (v->info.x < dest->info.x || (v->info.x == dest->info.x && v->info.y < dest->info.y)) {
                    printf("Intersecção: %c(%d,%d) <-> %c(%d,%d)\n",
                        v->info.frequencia, v->info.x, v->info.y,
                        dest->info.frequencia, dest->info.x, dest->info.y);
                }
            }
        }
    }
    return 0;
}

#pragma endregion


#pragma region Libertar Memória

/**
 * @brief Liberta a memória alocada para o grafo.
 * @param grafo Ponteiro para a cabeça da lista de vértices.
 * @return 0 se o grafo foi guardado com sucesso, 1 caso contrário.
 */
int libertarGrafo(Vertice *grafo) {
    while (grafo != NULL) {
        Vertice *temp = grafo;
        grafo = grafo->proximo;

        // Liberta as adjacências
        Adj *adj = temp->adj;
        while (adj != NULL) {
            Adj *tempAdj = adj;
            adj = adj->proxima;
            free(tempAdj);
        }

        free(temp);
    }
    return 0;
}

#pragma endregion


#pragma region Guardar em ficheiros binários

/**
 * @brief Guarda o grafo em formato binário.
 * @param filename Nome do ficheiro binário.
 * @param grafo Ponteiro para a cabeça da lista de vértices.
 * @return 0 se o grafo foi guardado com sucesso, 1 caso contrário.
 */
int guardarGrafoBinario(const char* filename, Vertice* grafo) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        return 0;
    }

    for (Vertice* v = grafo; v != NULL; v = v->proximo) {
        fwrite(&v->info, sizeof(Antena), 1, file);

        for (Adj* a = v->adj; a != NULL; a = a->proxima) {
            fwrite(&a->destino->info, sizeof(Antena), 1, file);
        }
    }
    Antena fim = {0, 0, 0};
    fwrite(&fim, sizeof(Antena), 1, file);

    fclose(file);
    return 0;
}

#pragma endregion