/**
 * @file grafos.h
 * @author Rodrigo Lopes Ferreira Nº 31525 
 * @brief Definições para representação de antenas via grafos e operações de busca.
 */

#ifndef GRAFOS_H
#define GRAFOS_H
#include "structs.h"


#pragma region | Inserir | Remover | Adjacências e Vértices

#pragma region Criar e Inserir Adjacências e Vértices

/**
 * @brief Cria e insere uma nova adjacência na lista de adjacências de um vértice.
 * @param vertice Vértice onde a adjacência será inserida.
 * @param destino Vértice de destino da adjacência.
 * @return 0 se o grafo foi guardado com sucesso, 1 caso contrário.
 */
int criarInserirAdj(Vertice *vertice, Vertice *destino);

/**
 * @brief Cria e insere um novo vértice com os dados de 'info'.
 * @param info Estrutura Antena com frequência e coords.
 * @return Ponteiro para o vértice (visitado inicializado a 0, adj = NULL).
 */
Vertice* criarInserirVert(Vertice *grafo, Antena info);

#pragma endregion

#pragma region Remover Adjacências e Vértices

/**
 * @brief Remove uma adjacência da lista de adjacências do vértice.
 * @param vertice Vértice onde a adjacência será removida.
 * @param destino Ponteiro para a adjacência a ser removida.
 * @return 0 se o grafo foi guardado com sucesso, 1 caso contrário.
 */
int removerAdj(Vertice *vertice, Vertice *destino);

/**
 * @brief Remove um vértice da lista de vértices do grafo e elimina as arestas associadas.
 * @param grafo Ponteiro para a cabeça da lista de vértices.
 * @param x Coordenada x do vértice a remover.
 * @param y Coordenada y do vértice a remover.
 * @return Novo ponteiro para a cabeça da lista de vértices.
 */
Vertice* removerVertice(Vertice *grafo, int x, int y);

#pragma endregion

#pragma endregion


#pragma region Carregar Grafo

/**
 * @brief Constrói o grafo de antenas a partir de ficheiro.
 * @param filename Caminho para o ficheiro de antenas.
 * @return Cabeça da lista de vértices (grafo).
 */
Vertice* carregarGrafo(const char *filename);

#pragma endregion


#pragma region Encontrar Vértice

/**
 * @brief Procura vértice pelas coordenadas (x,y).
 * @param grafo Ponteiro para a cabeça da lista de vértices.
 * @param x Coordenada x do vértice a procurar.
 * @param y Coordenada y do vértice a procurar.     
 * @return Ponteiro para o vértice encontrado ou NULL se não encontrado.
 */
Vertice* encontraVertice(Vertice *grafo, int x, int y);

#pragma endregion


#pragma region Construir Grafo

/**
 * @brief Constrói o grafo de antenas a partir de um conjunto de vértices.
 * @param grafo Cabeça da lista ligada de vértices.
 * @return 0 se o grafo foi guardado com sucesso, 1 caso contrário.
 */
int construirGrafo(Vertice *grafo);

#pragma endregion


#pragma region DFS

/**
 * @brief Realiza uma busca em profundidade (DFS) a partir de um vértice inicial.
 * @param inicio Vértice inicial para a busca.
 * @return 0 se o grafo foi guardado com sucesso, 1 caso contrário.
 */
int dfs(Vertice *inicio);

#pragma endregion


#pragma region BFS

/**
 * @brief Realiza uma busca em largura (BFS) a partir de um vértice inicial.
 * @param inicio Vértice inicial para a busca.
 * @return 0 se o grafo foi guardado com sucesso, 1 caso contrário.
 */
int bfs(Vertice *inicio);

#pragma endregion


#pragma region Listar Interseções A e B

/**
 * @brief Lista as interseções entre dois conjuntos de vértices.
 * @param grafo Cabeça da lista ligada de vértices.
 * @param freqA Frequência do conjunto A.
 * @param freqB Frequência do conjunto B.
 * @return 0 se o grafo foi guardado com sucesso, 1 caso contrário.
 */
int listarIntersecoes(Vertice *grafo, char freqA, char freqB);

#pragma endregion


#pragma region Libertar Memória

/**
 * @brief Liberta a memória alocada para o grafo.
 * @param grafo Ponteiro para a cabeça da lista de vértices.
 * @return 0 se o grafo foi guardado com sucesso, 1 caso contrário.
 */
int libertarGrafo(Vertice *grafo);

#pragma endregion


#pragma region Guardar em ficheiros binários

/**
 * @brief Guarda o grafo em formato binário.
 * @param filename Nome do ficheiro binário.
 * @param grafo Ponteiro para a cabeça da lista de vértices.
 * @return 0 se o grafo foi guardado com sucesso, 1 caso contrário.
 */
int guardarGrafoBinario(const char* filename, Vertice* grafo);

#pragma endregion


#endif