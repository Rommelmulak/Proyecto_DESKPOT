/**
*@brief Manejo de objetos (funcionalidad)
*
*
*@file object.c
*@author FJNR & AMH
*@version 1.0
*@date 05/02/2018
*@copyright GNU Public License
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "object.h"
#include "space.h"

/*Estructura que define un objeto(características) */
struct _Object {
  Id id; /*Identificador del Objeto*/
  char name[WORD_SIZE+1]; /*Nombre del objeto*/
  Id location; /*Id del space (Donde esta el objeto)*/
};



/*
 * @author Alejandro Martin
 * @brief Se encarga de crear el objeto,
   y poner el caracter fin de cadena al final del nombre de este
 * @param id, de tipo Id
 * @return newObject, que es el puntero a la estructura
 */
Object* object_create (Id id){
  Object *newObject = NULL;
  if (id == NO_ID){
    return NULL;
  }
  newObject = (Object*)malloc(sizeof(Object));

  if (newObject==NULL){
    return NULL;
  }
  newObject->id=id;

  return newObject;
}



/*
 * @author Alejandro Martin
 * @brief Libera memoria para objeto.
 * @param objeto: puntero a Objeto.
 * @return status OK o ERROR.
 */
STATUS object_destroy (Object* object){
  if(!object){
    return ERROR;
  }

  free(object);

  return OK;
}


/*
 * @author Alejandro Martin
 * @brief Devuelve el id de un objeto
 * @param objeto: puntero a Objeto.
 * @return Id NO_ID o puntero (object->id).
 */
Id object_get_id(Object *object){
  if (object==NULL){
    return NO_ID;
  }
  else {
    return object->id;
  }
}



/*
 * @author Alejandro Martin
 * @brief Devuelve el nombre asignado a un objeto
 * @param objeto: puntero a Objeto.
 * @return name, el nombre que asignamos al objeto
 */
char * object_get_name(Object* object) {
  if (!object) {
    return NULL;
  }
  return object->name;
}



/*
 * @author Alejandro Martin
 * @brief Devuelve el id asignado a un objeto
 * @param objeto: puntero a Objeto.
 * @return location, campo object->location
 */
Id object_get_location(Object* object){
  if (object == NULL){
    return NO_ID;
  }
  else {
    return object->location;
  }
}



/*
 * @author Francisco Nanclares
 * @brief Pone o cambia el id del objeto conforme a la location
 * @param objeto: puntero a Objeto.
 * @param id: del type Id
 * @return status OK o ERROR.
 */
STATUS object_set_location(Object* object , Id id){
  if (!object || id == NO_ID){
    return ERROR;
  }
  object->location = id;
  return OK;
}



/*
 * @author Alejandro Martin
 * @brief Pone o cambia el nombre del objeto
 * @param objeto: puntero a Objeto.
 * @param name: puntero a char.
 * @return status OK o ERROR.
 */
STATUS object_set_name (Object* object, char* name){
  if (!object || !name){
    return ERROR;
  }
  if (!strcpy(object->name,name)){
    return ERROR;
  }

  return OK;
}



/*
 * @author Francisco Nanclares
 * @brief Muestra por la pantalla de salida, tanto el id, como el nombre del objeto
 * @param objeto: puntero a Objeto.
 * @return status, OK o ERROR
 */
STATUS object_print(Object* object) {

  if (!object) {
    return ERROR;
  }

  fprintf(stdout, "--> Object (Id: %ld; Name: %s)\n", object->id, object->name);

  return OK;
}
