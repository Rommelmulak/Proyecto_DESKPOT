#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "dice.h"
#include "types.h"

/**
 * @author Francisco Nanclares
 * @brief esta función se encarga de realizar
   un examen para asegurarse del funcionamiento del dado
 * @param los agumentos del main (argc y argv)
 * @return, 0,1,2,3 o 4, dependiendo del error
 */
int main (int argc , char *argv[]){
  Dice *dice;
  int ultima_tirada;
  dice = dice_create(1);

  if (dice == NULL){
    return 0;
  }

  if ((dice_get_id(dice)) != NO_ID){
    fprintf(stdout,"%d",(int)dice_get_id(dice));
  }
  else {
    dice_destroy(dice);
    return 1;
  }

  if (dice_roll(dice)==ERROR){
    dice_destroy(dice);
    return 2;
  }

  if ((ultima_tirada=dice_get_last_shot(dice))!=0){
    fprintf(stdout,"Last Shot: %d",ultima_tirada);
  }
  else {
    dice_destroy(dice);
    return 3;
  }

  fprintf(stdout,"Ultima prueba: ");

  if (dice_print(dice) == ERROR){
    dice_destroy(dice);
    return 4;
  }
  return 0;
}
