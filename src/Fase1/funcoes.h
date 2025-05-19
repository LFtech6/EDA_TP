/**
 * @file funcoes.h
 * @author Rodrigo Lopes Ferreira Nº 31525 
 * @brief Declaração das funções para manipular antenas e localizações nefastas.
 */

 #ifndef FUNCOES_H
 #define FUNCOES_H
 #include "struct.h"
 
 #pragma region Inserir Antena
 
 /**
  * @brief Insere uma nova antena na lista ligada.
  * @param head Ponteiro para o início da lista de antenas.
  * @param freq Frequência da antena (ex.: 'A', 'B').
  * @param x Coordenada X da antena.
  * @param y Coordenada Y da antena.
  * @return Antena* Novo ponteiro para o início da lista atualizada.
  */
 Antena* inserirAntena(Antena* head, char freq, int x, int y);
 
 #pragma endregion
 
 #pragma region Carregar Antenas
 
 /**
  * @brief Carrega antenas de um ficheiro de texto para a lista ligada.
  * @param filename Nome do ficheiro a ser lido (ex.: "antenas.txt").
  * @return Antena* Ponteiro para o início da lista carregada ou NULL se der erro.
  */
 Antena* carregarAntenas(const char* filename);
 
 #pragma endregion
 
 #pragma region Remover Antena
 
 /**
  * @brief Remove uma antena da lista com base nas coordenadas X e Y.
  * @param head Ponteiro para o início da lista de antenas.
  * @param x Coordenada X da antena a remover.
  * @param y Coordenada Y da antena a remover.
  * @return Antena* Novo ponteiro para o início da lista atualizada.
  */
 Antena* removerAntena(Antena* head, int x, int y);
 
 #pragma endregion

 #pragma region Listar Antenas
 /**
  * @brief Lista as antenas numa tabela.
  * @param head Ponteiro para o início da lista de antenas.
  * @return void
  */
 Antena* listarAntenas(Antena* head);
 
 #pragma endregion

 #pragma region Mostrar Localizações com efeito nefasto
 
 /**
  * @brief Identifica e mostra localizações com efeito nefasto (antenas com mesma frequência a distância <= 2).
  * @param head Ponteiro para o início da lista de antenas.
  * @return Antena* Ponteiro para a cabeça da lista (mantida inalterada).
  */
 LocalizacaoNefasta* efeitoNef(Antena* head);
 
 #pragma endregion
 
 #endif