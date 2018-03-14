/**
 * @brief It defines common types
 *
 * @file types.h
 *@author FJNR & AMH
 * @version 1.0
 *@date 05/02/2018
 * @copyright GNU Public License
 */

#ifndef TYPES_H
#define TYPES_H

#define WORD_SIZE 1000 /*Tamaño maximo de palabra*/
#define NO_ID -1 /*Equivalente a Id no existente*/
#define MAX_ID 64/*Numero maximo de id de objeto presentes en juego*/


typedef long Id;/*Especificacion de tipo de dato del id*/
/**
Enumeración de códigos de error DE BOOL
*/
typedef enum {
  FALSE, TRUE/*Condiciones logicas de tipo BOOLEAN*/
} BOOL;
/**
Enumeración de códigos de error de STATUS
*/
typedef enum {
  ERROR, OK /*Condiciones logicas para STATUS*/
} STATUS;
/**
Enumeración de direcciones
*/
typedef enum {
  N, S, E, W /*Norte, sur, estre , oeste*/
} DIRECTION;

#endif
