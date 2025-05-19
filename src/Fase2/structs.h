/**
 * @file structs.h
 * @author Rodrigo Lopes Ferreira Nº 31525 
 * @brief Definições para representação de antenas via grafos e operações de busca.
 */

#ifndef STRUCTS_H
#define STRUCTS_H
#include "../Fase1/struct.h"


#pragma region Struct Vertice

/**
 * @struct Vertice
 * @brief Vértice do grafo, contém informação da antena e lista de adjacência.
 */
typedef struct Vertice {
    struct Antena info; //Informação da antena
    struct Adj* adj; //Lista de adjacência (arestas)
    struct Vertice* proximo; //Próximo vértice na lista
    int visitado; //Flag para verificar se o vértice foi visitado
} Vertice;

#pragma endregion

#pragma region Struct Adj

/**
 * @struct Adj
 * @brief Nó da lista de adjacência, representa as ligações com os vértices vizinhos.
 */
typedef struct Adj {
    struct Vertice* origem; //Vértice de origem da aresta
    struct Vertice* destino; //Vértice de destino da aresta
    struct Adj *proxima; //Próxima aresta na lista
} Adj;

#pragma endregion

#pragma region Struct ArestaRemovida

/**
 * @struct ArestaRemovida
 * @brief Estrutura que representa uma aresta removida do grafo.
 */
typedef struct ArestaRemovida {
    Vertice *origem;
    Vertice *destino;
    struct ArestaRemovida *proxima;
} ArestaRemovida;

#pragma endregion


#endif