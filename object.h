/**
*@brief Manejo de objetos (interfaz)
*
*
*@file object.h
*@author FJNR & AMH & CMF & MLR
*@version 1.0
*@date 05/02/2018
*@copyright GNU Public License
*/

#ifndef OBJECT_H
#define OBJECT_H
#include "types.h"

/**
 * @brief Estructura que define un objeto(características)
*/
typedef struct _Object Object;



/**
 * @author Carlos Miret
 * @brief Se encarga de crear el objeto,
   y poner el caracter fin de cadena al final del nombre de este
 * @param id, de tipo Id
 * @return newObject, que es el puntero a la estructura
 */
Object* object_create (Id id);



/**
 * @author Carlos Miret
 * @brief Libera memoria para objeto.
 * @param objeto: puntero a Objeto.
 * @return status OK o ERROR.
 */
STATUS object_destroy (Object* object);



/**
 * @author Carlos Miret
 * @brief Devuelve el id de un objeto
 * @param objeto: puntero a Objeto.
 * @return Id NO_ID o puntero (object->id).
 */
Id object_get_id(Object *object);



/**
 * @author Carlos Miret
 * @brief Devuelve el nombre asignado a un objeto
 * @param objeto: puntero a Objeto.
 * @return name, el nombre que asignamos al objeto
 */
char * object_get_name(Object* object);


/**
 * @author Carlos Miret
 * @brief Devuelve el id asignado a un objeto
 * @param objeto: puntero a Objeto.
 * @return location, campo object->location
 */
Id object_get_location(Object* object);



/**
 * @author Carlos Miret
 * @brief Pone o cambia el id del objeto conforme a la location
 * @param objeto: puntero a Objeto.
 * @param id: del type Id
 * @return status OK o ERROR.
 */
STATUS object_set_location(Object* object , Id id);



/**
 * @author Carlos Miret
 * @brief Pone o cambia el nombre del objeto
 * @param objeto: puntero a Objeto.
 * @param name: puntero a char.
 * @return status OK o ERROR.
 */
STATUS object_set_name (Object* object , char* name);



/**
 * @author Carlos Miret
 * @brief Muestra por la pantalla de salida, tanto el id, como el nombre del objeto
 * @param objeto: puntero a Objeto.
 * @return status, OK o ERROR
 */
STATUS object_print(Object* object);

#endif
