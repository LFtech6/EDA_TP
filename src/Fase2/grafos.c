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
        return 1;
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
        return grafo; // Falha de alocação
    }

    // Inicializa o novo vértice
    novoVertice->info = info;
    novoVertice->visitado = 0;
    novoVertice->adj = NULL;
    novoVertice->proximo = NULL;

    // Inserção no início da lista se for 'A'
    if (info.frequencia == 'A') {
        novoVertice->proximo = grafo;
        return novoVertice;
    }

    // Inserção no fim da lista se for '0'
    if (grafo == NULL) {
        return novoVertice; // Lista estava vazia
    }

    Vertice *atual = grafo;
    while (atual->proximo != NULL) {
        atual = atual->proximo;
    }
    atual->proximo = novoVertice;

    return grafo;
}


#pragma endregion

#pragma region Remover Adjacências e Vértices

/**
 * @brief Remove uma adjacência da lista de adjacências do vértice.
 * @param vertice Vértice onde a adjacência será removida.
 * @param destino Ponteiro para a adjacência a ser removida.
 * @return 0 se o grafo foi guardado com sucesso, 1 caso contrário.
 */
int removerAdj(Vertice *vertice, Vertice *destino) {
    Adj *anterior = NULL;
    Adj *atual = vertice->adj;

    // Procurar a adjacência a remover
    while (atual != NULL) {
        if (atual->destino == destino) {
            break; // Encontrou a adjacência
        }
        anterior = atual;
        atual = atual->proxima;
    }

    if (atual == NULL) {
        return 1; // Não encontrado
    }

    // Remover a adjacência
    if (anterior == NULL) {
        vertice->adj = atual->proxima; // Era o primeiro
    } else {
        anterior->proxima = atual->proxima; // Remove do meio ou fim
    }

    free(atual);
    return 0; // Sucesso
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

    // Procurar o vértice a remover
    while (atual != NULL) {
        if (atual->info.x == x && atual->info.y == y) {
            break; // Encontrou o vértice
        }
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        return grafo; // Vértice não encontrado, retorna o grafo original
    }

    // Remover arestas associadas ao vértice
    for (Vertice *v = grafo; v != NULL; v = v->proximo) {
        removerAdj(v, atual); // Remove arestas de outros vértices para este
    }

    // Remover o vértice da lista
    if (anterior == NULL) {
        grafo = atual->proximo; // Era o primeiro vértice
    } else {
        anterior->proximo = atual->proximo; // Remove do meio ou fim
    }

    free(atual); // Libera memória do vértice removido
    return grafo; // Retorna o novo início da lista de vértices
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
                // Evita adicionar aresta duplicada
                int jaLigado = 0;
                for (Adj *adj = v1->adj; adj != NULL; adj = adj->proxima) {
                    if (adj->destino == v2) {
                        jaLigado = 1;
                        break;
                    }
                }
                if (!jaLigado) {
                    if (criarInserirAdj(v1, v2) != 0) {
                        return 1; // Erro ao criar adjacência
                    }
                }
            }
        }
    }
    return 0; // Sucesso
}

#pragma endregion


#pragma region Mostrar Adjacências

/**
 * @brief Mostra as adjacências de cada vértice do grafo.
 * @param grafo Cabeça da lista ligada de vértices.
 * @return 0 se o grafo foi guardado com sucesso, 1 caso contrário.
 */
void mostrarAdjacencias(Vertice *grafo) {
for (Vertice *v = grafo; v != NULL; v = v->proximo) {
        printf("(%d,%d)", v->info.x, v->info.y);
        for (Adj *adj = v->adj; adj != NULL; adj = adj->proxima) {
            printf(" -> (%d,%d)", adj->destino->info.x, adj->destino->info.y);
        }
        printf("\n");
    }
}

#pragma endregion


#pragma region resetar V visitados

/**
 * @brief Reseta as flags de visitado para todos os vértices do grafo.
 * @param grafo Ponteiro para a cabeça da lista de vértices.
 */
void resetvVisitados(Vertice *grafo) {
    for (Vertice *v = grafo; v; v = v->proximo) {
        v->visitado = 0;
    }
}

#pragma endregion


#pragma region DFS

/**
 * @brief Realiza uma busca em profundidade (DFS) a partir de um vértice inicial.
 * @param inicio Vértice inicial para a busca.
 * @return 0 se o grafo foi guardado com sucesso, 1 caso contrário.
 */
int dfs(Vertice *grafo, Vertice *inicio) {
    
    if (inicio == NULL) return 1; // Se o vértice inicial for NULL, retorna erro

    // cria o stack para armazenar os vértices a visitar
    Vertice *stack[100];
    int topo = 0;
    
    // puxa o vertice inicial para o stack e marca como visitado
    stack[topo++] = inicio;
    inicio->visitado = 1;
    
    // enquanto o stack nao estiver vazio
    while (topo > 0) {
        // pega no vértice do topo da stack
        Vertice *v = stack[--topo];
        
        //print o vertice visitado
        printf("(%d,%d)\n", v->info.x, v->info.y);
        
        // puxa os nao visitados para o stack
        for (Adj *adj = v->adj; adj != NULL; adj = adj->proxima) {
            Vertice *vizinho = adj->destino;
            if (!vizinho->visitado) {
                stack[topo++] = vizinho;
                vizinho->visitado = 1; // sempre que puxar um vértice para o stack, marca como visitado
            }
        }
    }
    
    return 0;
}

#pragma endregion


#pragma region BFS

/**
 * @brief Realiza uma busca em largura (BFS) a partir de um vértice inicial.
 * @param grafo Ponteiro para a cabeça da lista de vértices (para resetar visitados).
 * @param inicio Vértice inicial para a busca.
 * @return 0 se sucesso, 1 caso contrário.
 */
int bfs(Vertice *grafo, Vertice *inicio) {
    if (!inicio) return 1;
    
    // Criar fila para BFS
    Vertice *fila[100];
    int frente = 0, tras = 0;
    
    // regra 1: inicialização
    // Colocar o nó inicial na fila e marcar como visitado
    fila[tras++] = inicio;
    inicio->visitado = 1;
    
    // regra 2 / 3: exploração enquanto a fila não estiver vazia / Repetir regra 1 e regra 2 até que a fila fique vazia
    while (frente < tras) {
        // Retirar um nó da fila e visitá-lo (imprimir o seu valor)
        Vertice *v = fila[frente++];
        
        // Visitar o vértice atual (imprimir)
        printf("(%d,%d)\n", v->info.x, v->info.y);
        
        // Para cada vizinho não visitado do nó retirado da fila:
        for (Adj *adj = v->adj; adj != NULL; adj = adj->proxima) {
            Vertice *vizinho = adj->destino;
            
            // Verificar se o vizinho ainda não foi visitado
            if (!vizinho->visitado) {
                // Colocar o vizinho na fila
                fila[tras++] = vizinho;
                // Marcar o vizinho como visitado
                vizinho->visitado = 1;
            }
        }
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