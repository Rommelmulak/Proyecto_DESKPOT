/**
 * @brief It defines common types
 *
 * @file types.h
 *@author FJNR & AMH & CMF & MLR
 * @version 1.0
 *@date 05/02/2018
 * @copyright GNU Public License
 */

#ifndef TYPES_H
#define TYPES_H

/** @brief Tamaño maximo de palabra*/
#define WORD_SIZE 1000 
/** @brief Equivalente a Id no existente*/
#define NO_ID -1 
/** @brief Numero maximo de id de objeto presentes en juego*/
#define MAX_ID 64

/**
*
* @brief Especificacion de tipo de dato del id
*/
typedef long Id;


/**
 * @brief Enumeración de códigos de error DE BOOL
*/
typedef enum {
  FALSE, /*<!hay error*/
  TRUE /*<!No hay error*/
} BOOL;


/**
 * @brief Enumeración de códigos de error de STATUS
*/
typedef enum {
  ERROR, /*<!hay error*/
  OK    /*<!No hay error*/
} STATUS;


/**
 *@brief Enumeración de direcciones
*/
typedef enum {
  N,/*<!Norte*/
  S,/*<!Sur*/
  E,/*<!Este*/
  W/*<!Oeste*/
} DIRECTION;

#endif
