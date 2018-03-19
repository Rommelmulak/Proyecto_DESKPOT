/**
*@brief Interfaz del dado
*
*
*@file dice.h
*@author FJNR & AMH & CMF & MLR
*@version 1.0
*@date 03/02/2018
*@copyright GNU Public License
*/
#ifndef DICE_H
#define DICE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "types.h"

/**
 * @brief Estructura del dado
*/
typedef struct _Dice Dice;


/**
 * @author Carlos Miret
 * @brief Se encarga de iniciar la estructura de un dado
 * @param nada
 * @return NULL o la propia estructura
 */
Dice * dice_create (Id id);



/**
 * @author Carlos Miret
 * @brief Se encarga de liberar la memoria para un dado
 * @param dice , puntero a Dice
 * @return nada se trata de una funcion de tipo void
 */
void dice_destroy (Dice *dice);



/**
 * @author Carlos Miret
 * @brief Se encarga de sacar un numero aleatorio entre 6 (dado comun de ocaa)
 * @param dice , puntero a Dice
 * @return int (numero random)
 */
STATUS dice_roll(Dice* dice);



/**
 * @author Carlos Miret
 * @brief Se encarga de obtener el id de un dado (funcion por ver)
 * @param dice , puntero a Dice
 * @return dice->id campo id o NULL
 */
/*Por si hay mas de uno en el juego y necesitamos un id especifico*/
Id dice_get_id(Dice* dice);


/**
 * @author Carlos Miret
 * @brief Se encarga de obtener la ultima tirada
 * @param dice , puntero a Dice
 * @return dice->last_shot campo de dice
 */
int dice_get_last_shot(Dice *dice);



/**
 * @author Carlos Miret
 * @brief Imprime un dado (el Id y la ultima tirada)
 * @param dice , puntero a Dice
 * @return status , OK o ERROR
 */
STATUS dice_print (Dice *dice);

#endif
