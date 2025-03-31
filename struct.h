/**
 * @file struct.h
 * @author Rodrigo Lopes Ferreira Nº 31525 
 * @brief Definição das estruturas para antenas e localizações nefastas, usadas no antenas.c
 */

 #ifndef STRUCT_H
 #define STRUCT_H
 
 #pragma region Struct Antena
 
 /**
  * @struct Antena
  * @brief Estrutura que representa uma antena numa cidade, com frequência e coordenadas.
  */
 typedef struct Antena {
     char frequencia;         // frequência da antena (a ou b)
     int x, y;                // coordenadas do tipo x e y
     struct Antena* proxima;  // ponteiro para a próxima antena na lista ligada
 } Antena;
 
 #pragma endregion
 
 #pragma region Struct LocalizacaoNefasta
 
 /**
  * @struct LocalizacaoNefasta
  * @brief Estrutura que guarda uma localização com efeito nefasto (ainda não implementado).
  */
 typedef struct LocalizacaoNefasta {
     int x;                        // coordenada x da nefasta
     int y;                        // coordenada y da nefasta
     struct LocalizacaoNefasta* proxima;  // ponteiro para o próximo nó na linkedlist
 } LocalizacaoNefasta; 
 
 #pragma endregion
 
 #endif