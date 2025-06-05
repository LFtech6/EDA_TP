/**
 * @file main.c
 * @author Rodrigo Lopes Ferreira Nº 31525 
 * @brief Função principal do programa.
 */

#include <stdio.h>
#include <stdlib.h>
#include "grafos.h"

int main() {

    Vertice* grafo = NULL;

    // Carregar o grafo a partir do ficheiro
    grafo = carregarGrafo("antenas.txt");
    if (grafo == NULL) {
        printf("Erro ao carregar o grafo.\n");
        return 1;
    }

    // Listar os vértices carregados
    printf("\nLista de Vértices:\n");
    Vertice* atual = grafo;
    while (atual != NULL) {
        printf("Vertice: %c (%d, %d)\n", atual->info.frequencia, atual->info.x, atual->info.y);
        atual = atual->proximo;
    }

    printf("\nLista de Adjacências\n");
    construirGrafo(grafo);
    printf("\n");

    // Remover um vértice
    int x = 6, y = 5;
    grafo = removerVertice(grafo, x, y);
    printf("\nVertice (%d, %d) removido\n", x, y);

    
    printf("\nLista de Adjacências Atualizada:\n");
    construirGrafo(grafo);
    printf("\n");


    // Inserir uma aresta manualmente
    Vertice *v1 = encontraVertice(grafo, 4, 4);
    Vertice *v2 = encontraVertice(grafo, 8, 8);
    Vertice *v3 = encontraVertice(grafo, 7, 3);
    Vertice *v4 = encontraVertice(grafo, 8, 8);
    Vertice *v5 = encontraVertice(grafo, 9, 9);
    Vertice *v6 = encontraVertice(grafo, 8, 1);
    if (v1 && v2 && v3 && v4 /*&& v5 && v6*/) {
        criarInserirAdj(v1, v2);
        criarInserirAdj(v2, v1);
        criarInserirAdj(v3, v4);
        criarInserirAdj(v4, v3);
        criarInserirAdj(v5, v6);
        criarInserirAdj(v6, v5);
        printf("Aresta inserida entre (%d,%d) e (%d,%d)\n", 4, 4, 8, 8);
        printf("Aresta inserida entre (%d,%d) e (%d,%d)\n", 7, 3, 8, 8);
        printf("Aresta inserida entre (%d,%d) e (%d,%d)\n", 9, 9, 8, 1);
    }
    

    printf("\nLista de Adjacências Atualizada:\n");
    construirGrafo(grafo);
    printf("\n");

    // Remover uma aresta manualmente
    Vertice *v7 = encontraVertice(grafo, 9, 9);
    Vertice *v8 = encontraVertice(grafo, 8, 8);
    if (v7 && v8) {
        removerAdj(v7, v8);
        removerAdj(v8, v7);
        printf("Aresta removida entre (%d,%d) e (%d,%d)\n", 9, 9, 8, 8);
    }


    printf("\nLista de Adjacências Final:\n");
    construirGrafo(grafo);
    printf("\n");


    printf("\nDFS a partir de (9,9):\n");
    Vertice *inicioDFS = encontraVertice(grafo, 9, 9);
    if (inicioDFS) {
        dfs(inicioDFS);
    } else {
        printf("Antena (9,9) não encontrada para DFS.\n");
    }

    // guardar o grafo num ficheiro binário
    printf("Grafo guardado em formato binário.\n");    
    guardarGrafoBinario("grafo.bin", grafo);

    // libertar a memória do grafo
    libertarGrafo(grafo);
    printf("Memória libertada.\n");


    return 0;
}