/**
*@brief It defines a space
*
*
*@file space.c
*@author FJNR & AMH & CMF & MLR
*@version 1.0
*@date 05/02/2018
*@copyright GNU Public License
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "space.h"
/*Lo necesitamos por las macros y utilizacion de nuevo campo Set*objects*/
#include "set.h"

/**
 * @brief Estructura que define un espacio (características)
*/
struct _Space {
  Id id; /*!< identificador del espacio*/
  char name[WORD_SIZE + 1]; /*!< Campo nombre del espacio*/
  Id north;/*!< Id del espaacio norte*/
  Id south;/*!< Id del espacio sur*/
  Id east;/*!< Id del espacio este*/
  Id west;/*!< Id del espacio oeste*/
  Id object;/*!< Id del objeto en un espacio*/
  Set *objects;/*!< Conjunto de objetos*/
  char gdesc[3][21];/*!< Matriz que define los arrays de las casillas gráficas */
};
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
SCREEN_MAX_STR = 80 <==screen.h
P.F.: Private Function
*/



/**
 * @author Francisco Nanclares
 * @brief Se encarga de iniciar la estructura de espacio
   y poner el caracter fin de cadena al final del nombre de este
 * @param id, de tipo Id
 * @return Space, que es el puntero a la estructura Space
 */
Space* space_create(Id id) {

  Space *space = NULL;

  if (id == NO_ID){
    return NULL;
  }

  space = (Space *) malloc(sizeof(Space));

  if (space == NULL) {
    return NULL;
  }
  space->id = id;

  space->name[0] = '\0';

  space->north = NO_ID;
  space->south = NO_ID;
  space->east = NO_ID;
  space->west = NO_ID;
  /*Para crear un conjunto de id (se asignará NO_ID)*/
  space->objects = set_create();

  return space;
}



/**
 * @author Francisco Nanclares
 * @brief Libera memoria para space
 * @param space: puntero a Space.
 * @return status OK o ERROR.
 */
STATUS space_destroy(Space* space) {
  if (!space) {
    return ERROR;
  }
  set_destroy(space->objects);
  space->objects = NULL;

  if (space->objects !=NULL){
    set_destroy(space->objects);
    space->objects=0;
  }
  free(space);



  return OK;
}



/**
 * @author Alejandro Martin
 * @brief Pone o cambia el nombre del espacio
 * @param space: puntero a Space.
 * @param name: puntero a char.
 * @return status OK o ERROR.
 */
STATUS space_set_name(Space* space, char* name) {
  if (!space || !name) {
    return ERROR;
  }

  if (!strcpy(space->name, name)) {
    return ERROR;
  }

  return OK;
}



/**
 * @author Alejandro Martin
 * @brief Pone o cambia el north
 * @param space: puntero a Space
 * @param id: campo de Id
 * @return status OK o ERROR o NO_ID
 */
STATUS space_set_north(Space *space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->north = id;
  return OK;
}



/**
 * @author Alejandro Martin
 * @brief Pone o cambia el south
 * @param space: puntero a Space.
 * @param id: del type Id
 * @return status OK o ERROR o NO_ID
 */
STATUS space_set_south(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->south = id;
  return OK;
}



/*
 * @author Alejandro Martin
 * @brief Pone o cambia el east
 * @param space: puntero a Space.
 * @param name: puntero a char.
 * @return status OK o ERROR o NO_ID
 */
STATUS space_set_east(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->east = id;
  return OK;
}



/**
 * @author Alejandro Martin
 * @brief Pone o cambia el west
 * @param space: puntero a Space.
 * @param id: del type Id
 * @return status OK o ERROR o NO_ID
 */
STATUS space_set_west(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->west = id;
  return OK;
}



/*
 * @author Alejandro Martin
 * @brief Devuelve el nombre (casilla)
 * @param space: puntero a Space.
 * @return name, el name space->name o NULL
 */
const char * space_get_name(Space* space) {
  if (!space) {
    return NULL;
  }
  return space->name;
}



/**
 * @author Alejandro Martin
 * @brief Devuelve el id (casilla)
 * @param space: puntero a Space.
 * @return id, el id space->id o NO_ID
 */
Id space_get_id(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->id;
}



/**
 * @author Alejandro Martin
 * @brief Devuelve el id de la casilla del norte
 * @param space: puntero a Space.
 * @return norte, space->north o NO_ID
 */
Id space_get_north(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->north;
}



/**
 * @author Alejandro Martin
 * @brief Devuelve el id de la casilla del sur
 * @param space: puntero a Space.
 * @return south, space->south o NO_ID
 */
Id space_get_south(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->south;
}



/**
 * @author Alejandro Martin
 * @brief Devuelve el id de la casilla del norte
 * @param space: puntero a Space.
 * @return norte, space->north o NO_ID
 */
Id space_get_east(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->east;
}



/**
 * @author Alejandro Martin
 * @brief Devuelve el id de la casilla del oeste
 * @param space: puntero a Space.
 * @return west, space->west o NO_ID
 */
Id space_get_west(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->west;
}


/**
 * @author Alejandro Martin
 * @brief Muestra por la pantalla de salida, tanto el id, como el nombre del espacio
 * @param space: puntero a Space.
 * @return status, OK o ERROR o NO_ID
 */
STATUS space_print(Space* space) {
  Id idaux = NO_ID;
  Set * set_aux;

  if (!space) {
    return ERROR;
  }

  fprintf(stdout, "--> Space (Id: %ld; Name: %s)\n", space->id, space->name);

  idaux = space_get_north(space);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> North link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No north link.\n");
  }

  idaux = space_get_south(space);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> South link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No south link.\n");
  }

  idaux = space_get_east(space);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> East link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No east link.\n");
  }

  idaux = space_get_west(space);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> West link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No west link.\n");
  }
  set_aux = space_get_objects(space);

  if (set_aux != NULL){
    set_print(set_aux);
    set_destroy(set_aux);
    set_aux = NULL;
  }
  else {
    fprintf(stdout, "---> No objects in the space.\n");
  }
  return OK;
}


/*----------------------------Descripcion Grafica(manejo de parametros)-------------------------------*/

/**
 * @author Francisco Nanclares
 * @brief Descripcion grafica ,Carga el espacio (primera linea de la representacion
    grafica , en codigo ASCII) 7 espacios
 * @param space: puntero a Space.
 * @param cadena , puntero a char (string)
 * @return status, OK o ERROR o NO_ID
 */
STATUS space_set_gdesc1(Space* space, char* cadena){
  /* Comprueba los argumentos */
  if (!space || !cadena){
    return ERROR;
  }

  /* Asigna a space.name el nombre introducido y lo comprueba */
  if (!strcpy(space->gdesc[0], cadena)) {
    return ERROR;
  }
  /* Si todo va bien devuelve OK */
  return OK;
}



/**
 * @author Francisco Nanclares
 * @brief Descripcion grafica ,Carga el espacio (segunda linea de la representacion
    grafica , en codigo ASCII) 7 espacios
 * @param space: puntero a Space.
 * @param cadena , puntero a char (string)
 * @return status, OK o ERROR o NO_ID
 */
STATUS space_set_gdesc2(Space* space, char* cadena){
  /* Comprueba los argumentos */
  if (!space || !cadena){
    return ERROR;
  }

  /* Asigna a space.name el nombre introducido y lo comprueba */
  if (!strcpy(space->gdesc[1], cadena)) {
    return ERROR;
  }
  /* Si todo va bien devuelve OK */
  return OK;
}



/**
 * @author Francisco Nanclares
 * @brief Descripcion grafica ,Carga el espacio (tercera linea de la representacion
    grafica , en codigo ASCII) 7 espacios
 * @param space: puntero a Space.
 * @param cadena , puntero a char (string)
 * @return status, OK o ERROR o NO_ID
 */
STATUS space_set_gdesc3(Space* space, char* cadena){
  /* Comprueba los argumentos */
  if (!space || !cadena){
    return ERROR;
  }

  /* Asigna a space.name el nombre introducido y lo comprueba */
  if (!strcpy(space->gdesc[2], cadena)) {
    return ERROR;
  }
  /* Si todo va bien devuelve OK */
  return OK;
}

/**
 * @author Francisco Nanclares
 * @brief Descripcion grafica  , obtener el string de la descripcion grafica
    en este caso la primera
 * @param space: puntero a Space.
 * @return char, retorna el string de la descripcion grafica (1)
 */
char* space_get_gdesc1(Space* space){
  if (space == NULL){
    return NULL;
  }

  return space->gdesc[0];
}



/**
 * @author Francisco Nanclares
 * @brief Descripcion grafica  , obtener el string de la descripcion grafica
    en este caso la segunda
 * @param space: puntero a Space.
 * @return char, retorna el string de la descripcion grafica (2)
 */
char* space_get_gdesc2(Space* space){
  if (space == NULL){
    return NULL;
  }

  return space->gdesc[1];
}



/*
 * @author Francisco Nanclares
 * @brief Descripcion grafica  , obtener el string de la descripcion grafica
    en este caso la tercera
 * @param space: puntero a Space.
 * @return char, retorna el string de la descripcion grafica (3)
 */
char* space_get_gdesc3(Space* space){
  if (space == NULL){
    return NULL;
  }

  return space->gdesc[2];
}


/*----------------------------Manejo de Objetos modulo Space-------------------------------*/

/**
 * @author Alejandro Martin
 * @brief Quita el ultimo objeto de la casilla
 * @param space: puntero a Space.
 * @return status, OK o ERROR.
 */
STATUS space_delete_object(Space* space){
  if (!space){
    return ERROR;
  }
  if(set_pop_id (space->objects)==NO_ID){
    return ERROR;
  }
  return OK;
}



/**
* @author Alejandro Martin
 * @brief Colocamos en el space un objeto
 * @param space: puntero a Space.
 * @param id: Id (identificador)
 * @return status, OK o ERROR.
 */
STATUS space_add_object(Space* space, Id id) {
  if (!space){
    return ERROR;
  }
  if (set_push_id(space->objects,id)==ERROR){
    return ERROR;
  }
  return OK;
}


/**
 * @author Alejandro Martin
 * @brief Devuelve el si hay o no objeto en la casilla
 * @param space: puntero a Space.
 * @return object, space->object o FALSE si no existen objetos
 */
Set * space_get_objects(Space* space) {
  if (!space || space->objects == NULL) {
    return NULL;
  }

  return space->objects;
}



/**
 * @author Francisco Nanclares
 * @brief Comprueba si un objeto esta en el espacio actual
 * @param space: puntero a Space.
 * @param id_objeto, de tipo id.
 * @return BOOL, TRUE or FALSE (si parámetros vacios/obtención de la estructura
    con errores/si sale en el bucle de comprobación (de set_delete))
 */
BOOL object_check_in_space (Space *space , Id id_objeto){
  Set *aux;
  Id id_aux;
  int i;

  if (!space|| id_objeto == NO_ID){
    return FALSE;
  }
  aux = space_get_objects(space);

  if (aux == NULL){
    return FALSE;
  }
  /*Busca en todos los id del set si encuentra el objeto (id) pasado por argumento*/
  for (i=0;i<MAX_ID;i++){
    id_aux = get_specific_id(aux,i);
    if (id_aux !=NO_ID){
      if(id_aux == id_objeto){

        return TRUE;
      }
    }
  }
  return FALSE;
}
