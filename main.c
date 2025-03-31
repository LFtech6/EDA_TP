/**
 * @file main.c
 * @author Rodrigo Lopes Ferreira Nº 31525 
 * @brief Função principal do programa.
 * 
 */

#include <stdio.h>
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
    listarAntenas(antena);

    #pragma region Menu

    while (1) {
        printf("Escolha uma opção (ou 0 para sair): \n\n");
        printf("1. Inserir Antena\n");
        printf("2. Remover Antena\n");
        printf("3. Mostrar Localizações com efeito nefasto\n");
        printf("4. Listar Antenas na tabela\n\n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                antena = inserirAntena(antena, 'A', 10, 20);
                printf("Antena (%d, %d) inserida\n\n", 10, 20); 
                break;
            case 2:
                (antena = removerAntena(antena, 5, 2)) ? printf("Antena (%d, %d) removida\n\n", 5, 2) : 
                printf("Antena (%d, %d) não encontrada.\n\n", 5, 2);
                break;    
            case 3:
                //antena = efeitoNef(antena);
                printf("não fiz\n\n");
                break;
            case 4:
                listarAntenas(antena);
                break;
            case 0:
                printf("bye bye 👋🏽👋🏽\n");
                return 0;
            default:
                printf("Não há função com número maior q 4, e foi escrito um %d.\n", opcao);
                break;
        }
    }

    #pragma endregion
    
    return 0;
}