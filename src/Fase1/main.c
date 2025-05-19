/**
 * @file main.c
 * @author Rodrigo Lopes Ferreira Nº 31525 
 * @brief Função principal do programa.
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

int main() {

    int opcao;

    Antena* antena = NULL;
    
    antena = carregarAntenas("antenas.txt");
    if (antena == NULL) {
        printf("Erro ao carregar antenas do ficheiro.\n");
        return 1;
    }   

    // listar antenas para dar p comparar
    Antena* lista = listarAntenas(antena);
    printf("Lista de Antenas:\n\n");
    printf("Frequência|\tX|\tY|\n");
    printf("--------------------------\n\n");
    Antena* temp = lista;
    while (temp != NULL) {
        printf("|\t%c|\t%d|\t%d|\n", temp->frequencia, temp->x, temp->y);
        temp = temp->proxima;
    }
    printf("--------------------------\n\n");

    #pragma region Menu

    while (1) {
        printf("Escolha uma opção (ou 0 para sair): \n\n");
        printf("1. Inserir Antena\n");
        printf("2. Remover Antena\n");
        printf("3. Mostrar Localizações com efeito nefasto\n");
        printf("4. Listar Antenas\n\n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 0: 
                return 0; // Encerra o programa
            case 1:
                printf("\n");
                antena = inserirAntena(antena, 'A', 10, 20);
                printf("Antena (%d, %d) inserida\n\n", 10, 20); 
                break;
            case 2:
                printf("\n");
                (antena = removerAntena(antena, 5, 2)) ? printf("Antena (%d, %d) removida\n\n", 5, 2) : 
                printf("Antena (%d, %d) não encontrada.\n\n", 5, 2);
                break;    
            case 3:
                printf("\n");
                LocalizacaoNefasta* nefastas = efeitoNef(antena);
                if (nefastas == NULL) {
                    printf("Nenhuma localização nefasto encontrada.\n\n");
                } else {
                    printf("Localizações com efeito nefasto:\n");
                    printf("X|\tY|\n");
                    printf("------------------\n");
                    LocalizacaoNefasta* temp = nefastas;
                    while (temp != NULL) {
                        printf("%d|\t%d|\n", temp->x, temp->y);
                        temp = temp->proxima;
                    }
                    printf("------------------\n\n");
                }
                // Liberta a memória da lista de nefastas
                while (nefastas != NULL) {
                    LocalizacaoNefasta* temp = nefastas;
                    nefastas = nefastas->proxima;
                    free(temp);
                }
                break;
            case 4:
                printf("\n");
                Antena* lista = listarAntenas(antena);
                printf("Lista de Antenas:\n\n");
                printf("Frequência|\tX|\tY|\n");
                printf("--------------------------\n\n");
                Antena* temp = lista;
                while (temp != NULL) {
                    printf("|\t%c|\t%d|\t%d|\n", temp->frequencia, temp->x, temp->y);
                    temp = temp->proxima;
                }
                printf("--------------------------\n\n");
                break;
            default:
                printf("\n");
                printf("Não há função com número maior q 4, e foi escrito um %d.\n", opcao);
                printf("\n");
                break;
        }
    }

    #pragma endregion
    
    return 0;
}