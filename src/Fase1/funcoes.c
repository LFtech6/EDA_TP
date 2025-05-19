/**
 * @file funcoes.c
 * @author Rodrigo Lopes Ferreira Nº 31525 
 * @brief Implementação das funções para manipulação de antenas.
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include "funcoes.h"
 
 #pragma region Inserir Antena
 
 /**
  * @brief Insere uma nova antena no início da lista ligada.
  * @param head Ponteiro para o início da lista.
  * @param freq Frequência da antena.
  * @param x Coordenada X.
  * @param y Coordenada Y.
  * @return Ponteiro atualizado para o início da lista.
  */
 Antena* inserirAntena(Antena* head, char freq, int x, int y) {
     Antena* nova = (Antena*)malloc(sizeof(Antena));
     if (nova == NULL) {
         return head; // se der erro, devolve a lista como estava
     }
 
     nova->frequencia = freq; // atribui a frequência à nova antena
     nova->x = x; // atribui os valores x à nova antena
     nova->y = y; // =        =    =    y =   =    =
     nova->proxima = head; // nova antena aponta para o antigo início
     head = nova;          // novo início agora = nova antena
     return head;

 }
 
 #pragma endregion
 
 #pragma region Carregar Antenas
 
 /**
  * @brief Carrega antenas de um ficheiro de texto para a lista ligada.
  * @param filename Nome do ficheiro a ser lido.
  * @return Ponteiro para o início da lista ou NULL se der erro.
  */
 Antena* carregarAntenas(const char* filename) {
     FILE* file = fopen(filename, "r");
     if (file == NULL) {
         return NULL; // se não abrir o ficheiro, devolve NULL
     }
 
     Antena* lista = NULL;
     int numLinha = 0;
     char texto[50];
 
     // Lê linha por linha do ficheiro com fgets, antes tinha posto com fscanf
     while (fgets(texto, 50, file)) {
        //tal cena do \0
         for (int pos = 0; texto[pos] != '\0' && texto[pos] != '\n'; pos++) {
             if (texto[pos] != '.') {
                 // insere cada cada letra como uma antena
                 lista = inserirAntena(lista, texto[pos], pos, numLinha);
             }
         }
         numLinha++;
     }
 
     fclose(file);
     return lista;
 }
 
 #pragma endregion
 
 #pragma region Remover Antena
 
 /**
  * @brief Remove uma antena da lista com base nas coordenadas X e Y.
  * @param head Ponteiro para o início da lista.
  * @param x Coordenada X da antena a remover.
  * @param y Coordenada Y da antena a remover.
  * @return Ponteiro atualizado para o início da lista.
  */
 Antena* removerAntena(Antena* head, int x, int y) {
     Antena* atual = head;
     Antena* anterior = NULL;
 
     // percorre a lista até encontrar a antena ou chegar ao fim
     while (atual != NULL) {
         if (atual->x == x && atual->y == y) {
             if (anterior == NULL) {
                 // se for o primeiro elemento, muda o início para próximo
                 head = atual->proxima;
             } else {
                 // liga o anterior ao próximo e esquece o atual
                 anterior->proxima = atual->proxima;
             }
             free(atual);
             return head;
         }
         anterior = atual;
         atual = atual->proxima; // Avança para o próximo
     }

     return head; 
 }
 
 #pragma endregion

 #pragma region Listar Antenas

/**
 * @brief Retorna a lista de antenas sem exibir.
 * @param head Ponteiro para o início da lista.
 * @return Antena* Ponteiro para o início da lista (inalterado).
 */
Antena* listarAntenas(Antena* head) {
    return head; // Devolve a lista como está
}

 #pragma endregion
 
 #pragma region Mostrar Localizações com efeito nefasto
 
 /**
 * @brief Identifica localizações com efeito nefasto (antenas com mesma frequência a distância <= 2).
 * @param head Ponteiro para o início da lista de antenas.
 * @return Ponteiro para a cabeça da lista (mantém se igual).
 */
 LocalizacaoNefasta* efeitoNef(Antena* head) {
    LocalizacaoNefasta* nefastas = NULL;

    // Compara cada antena com as seguintes
    Antena* atual = head;
    while (atual != NULL) {
        Antena* prox = atual->proxima;
        while (prox != NULL) {
            if (atual->frequencia == prox->frequencia) {
                int dist = abs(atual->x - prox->x) + abs(atual->y - prox->y);
                if (dist <= 2) {
                    // Adiciona coordenadas da primeira antena
                    LocalizacaoNefasta* nova = (LocalizacaoNefasta*)malloc(sizeof(LocalizacaoNefasta));
                    if (nova == NULL) continue;
                    nova->x = atual->x;
                    nova->y = atual->y;
                    nova->proxima = nefastas;
                    nefastas = nova;

                    // Adiciona coordenadas da segunda antena
                    nova = (LocalizacaoNefasta*)malloc(sizeof(LocalizacaoNefasta));
                    if (nova == NULL) continue;
                    nova->x = prox->x;
                    nova->y = prox->y;
                    nova->proxima = nefastas;
                    nefastas = nova;
                }
            }
            prox = prox->proxima;
        }
        atual = atual->proxima;
    }

    return nefastas; // Devolve a lista de localizações nefastas
}


 #pragma endregion