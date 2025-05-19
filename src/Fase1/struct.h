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
  * @brief Estrutura que guarda uma localização com efeito nefasto.
  */
 typedef struct LocalizacaoNefasta {
    int x, y; // coordenadas da localização
    struct LocalizacaoNefasta* proxima; // ponteiro para a próxima localização
 } LocalizacaoNefasta;
 
 #pragma endregion
 
 #endif