/*
*@brief Carga de espacios (funcionalidad)
*
*@file game_reader.c
*@author FJNR & AMH
*@version 1.0
*@date 05/02/2018
*@copyright GNU Public License
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "game_reader.h"
#include "space.h"
#include "command.h"/*Ya vienen en "game_reader.h"*/
#include "game.h" /*Ya vienen en "game_reader.h"*/
#include "set.h"


/**                 Definidos en:
                        ||
                        ||
                        V
WORD_SIZE = 1000 <==types.h
MAX_SPACES = 100 <==space.h
FIRST_SPACE = 1 <==space.h
NO_ID = -1 <==types.h
NO_CMD = -1 <==command.h
UNKNOWN = 0 <==command.h
EXIT = 1 <==command.h
FOLLOWING = 2 <==command.h
PREVIOUS = 3 <==command.h
P. F.: Private Function
*/

/*
 * @author Alejandro Martin
 * @brief  Lee el fichero (funcionalidad de carga de espacios)
 * @param Game, es el string destino, en el que se copia el puntero al string de tipo char, "toks"
 * @param filename, puntero a char, que es el nombre del fichero que estamos accediendo
 * @param numcasillas , representa cuantas casillas hay en el juego (funcion de cuenta por si hace falta)
 * @return status, OK O ERROR
 */

STATUS game_reader_load_spaces(Game* game, char* filename) {
  FILE* file = NULL;
  char line[WORD_SIZE] = "";/*Representacion de una linea*/
  char name[WORD_SIZE] = "";
  char* toks = NULL;/*Token (division) de un string en una lectura*/

  /*strings de la primera descripcion grafica: */
  char *string = NULL;
  char *string2= NULL;
  char *string3= NULL;

  char string_z[20] = "                 ";/*string de NULL (si objeto == NULL)string = string_z*/
  Id id = NO_ID, north = NO_ID, east = NO_ID, south = NO_ID, west = NO_ID;
  Space* space = NULL;
  /*Suponemos OK*/
  STATUS status = OK;/*Bandera de estado*/

  if (!filename) {
    return ERROR;
  }


  file = fopen(filename, "r");
  if (file == NULL) {
    return ERROR;
  }


  /**
  Este bucle:
  -Establece donde se copiará el string leído,
  -Escanea el fichero por líneas (1000 como máximo) y almacena en "line"
  */
  while (fgets(line, WORD_SIZE, file)) {
    /*Si los 3 primeros caracteres son #s: */
    if (strncmp("#s:", line, 3) == 0) {
      /*Rompemos la cadena en trozos y los separamos con el caracter "|"*/
      /*Se asigna a las variables el valor obtenido del archivo correspondiente*/
      toks = strtok(line + 3, "|");
      /*"atol" convierte la porción inicial de la cadena apuntada por "toks" a una representación de "id", y lo devuelve.*/
      /*Por lo tanto, "id" = valor convertido*/
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);

      toks = strtok(NULL, "|");
      north = atol(toks);

      toks = strtok(NULL, "|");
      east = atol(toks);

      toks = strtok(NULL, "|");
      south = atol(toks);

      toks = strtok(NULL, "|");
      west = atol(toks);

      string = strtok(NULL, "|");
      string2 = strtok(NULL, "|");
      string3 = strtok(NULL, "|");



    #ifdef DEBUG /*Se ejecuta el código de dentro si debug está definido*/

      printf("Leído: %ld|%s|%ld|%ld|%ld|%ld\n", id, name, north, east, south, west);


    #endif
    /*Asignamos los nuevos valores (leídos con fgets)*/
      space = space_create(id);
      if (space != NULL) {
	      space_set_name(space, name);
	      space_set_north(space, north);
	      space_set_east(space, east);
	      space_set_south(space, south);
	      space_set_west(space, west);
        if (string == NULL){
          space_set_gdesc1(space,string_z);
        }
        else{
          space_set_gdesc1(space,string);
        }
        if (string2 == NULL){
          space_set_gdesc2(space,string_z);
        }
        else {
          space_set_gdesc2(space,string2);
        }
        if (string3 == NULL){
          space_set_gdesc3(space,string_z);
        }
        else {
          space_set_gdesc3(space,string3);
        }

        game_add_space(game,space);
      }
    }
  }
  /*Se modifica el estado del código de error y devuelve
    un valor distinto de cero si se detectan errores*/
  if (ferror(file)) {
    status = ERROR;
  }
  fclose(file);

  return status;
}



/*
 * @author Francisco Nanclares
 * @brief  Lee el fichero (funcionalidad de carga de objetos)
 * @param Game, es el string destino, en el que se copia el puntero al string de tipo char, "toks"
 * @param filename, puntero a char, que es el nombre del fichero que estamos accediendo
 * @return status, OK O ERROR
 */
STATUS game_reader_load_objects(Game* game, char* filename){
  FILE* file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char* toks = NULL;

  Id id_object = NO_ID;
  Id space_id = NO_ID;
  Object * object = NULL;
  /*Suponemos OK*/
  STATUS status = OK;

  if (!filename) {
    return ERROR;
  }

  file = fopen(filename, "r");
  if (file == NULL) {
    return ERROR;
  }

  while (fgets (line,WORD_SIZE,file)){
    if (strncmp("#o:",line,3) ==0){

      toks =strtok(line+3 , "|");

      id_object = atol(toks);
      toks = strtok(NULL,"|");
      strcpy(name,toks);
      toks = strtok(NULL,"|");
      space_id = atol(toks);

      #ifdef DEBUG

        printf("\n\n\n\n");
        printf ("Leido: %ld|%s|%ld\n" ,id_object,name,space_id);
      #endif

        object = object_create(id_object);
        if (object != NULL){
          /*Si objeto se ha creado con exito se anade a el set de objetos (y se cambian atributos)*/
          object_set_name(object, name);
          game_add_object(game,object);
          game_set_object_location(game,space_id,object);
        }
    }
  }
  if (ferror(file)){
    status = ERROR;
  }

  fclose(file);

  return status;
}
