/**
*@brief Implementacion del dado
*
*
*@file dice.c
*@author FJNR & AMH
*@version 1.0
*@date 03/02/2018
*@copyright GNU Public License
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "types.h"
#include "dice.h"

/*Estructura que representa datos caracteristicos de un dado (id) y el ultimo
  tiro*/
struct _Dice {
  Id id; /*Identificador del dado*/
  int last_shot; /*Ultima tirada del dado*/
};



/*
 * @author Francisco Nanclares
 * @brief Se encarga de iniciar la estructura de un dado
 * @param nada
 * @return NULL o la propia estructura
 */
Dice * dice_create (Id id){
  Dice *dice;
  dice = (Dice*)malloc(sizeof(Dice));
  if (dice == NULL){
    return NULL;
  }
  dice->id = id;
  dice->last_shot = 0;
  return dice;
}



/*
 * @author Alejandro Martin
 * @brief Se encarga de liberar la memoria para un dado
 * @param dice , puntero a Dice
 * @return nada se trata de una funcion de tipo void
 */
void dice_destroy (Dice *dice){
  if (dice == NULL){
    return;
  }
  free(dice);
  dice = NULL;

  return;
}



/*
 * @author Francisco Nanclares
 * @brief Se encarga de sacar un numero aleatorio entre 6 (dado comun de ocaa)
 * @param dice , puntero a Dice
 * @return int (numero random)
 */
STATUS dice_roll(Dice *dice){
  time_t t;
  if (dice == NULL){
    return ERROR;
  }
  srand((unsigned) time(&t));
  dice->last_shot = (rand() %6 + 1);
  if (dice->last_shot == 0){
    return ERROR;
  }
  return OK;
}



/*
 * @author Francisco Nanclares
 * @brief Se encarga de obtener el id de un dado (funcion por ver)
 * @param dice , puntero a Dice
 * @return dice->id campo id o NULL
 */
/*Por si hay mas de uno en el juego y necesitamos un id especifico*/
Id dice_get_id(Dice*dice){
  if (dice == NULL){
    return NO_ID;
  }
  return dice->id;
}



/*
 * @author Francisco Nanclares
 * @brief Se encarga de obtener la ultima tirada
 * @param dice , puntero a Dice
 * @return dice->last_shot campo de dice
 */
int dice_get_last_shot(Dice *dice){
  if (dice == NULL){
    return 0;
  }
  return dice->last_shot;
}



/*
 * @author Alejandro Martin
 * @brief Imprime un dado (el Id y la ultima tirada)
 * @param dice , puntero a Dice
 * @return status , OK o ERROR
 */
STATUS dice_print (Dice *dice){
  if (!dice){
    return ERROR;
  }
  fprintf(stdout,"--> Dice (Id: %ld;last_shot:%d)",dice->id,dice->last_shot);
  return OK;
}
