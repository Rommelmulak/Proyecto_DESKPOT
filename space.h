/**
*@brief It defines a space
*
*
*@file space.h
*@author FJNR & AMH & CMF & MLR
*@version 1.0
*@date 05/02/2018
*@copyright GNU Public License
*/

#ifndef SPACE_H
#define SPACE_H

#include "types.h"
#include "set.h"

/**
 * @brief Estructura que define un espacio (características)
*/
typedef struct _Space Space;

/** @brief Numero maximo de espacios*/
#define MAX_SPACES 100 

/** @brief Primer espacio*/
#define FIRST_SPACE 1 



/**
 * @author Francisco Nanclares
 * @brief Se encarga de iniciar la estructura de espacio
   y poner el caracter fin de cadena al final del nombre de este
 * @param id, de tipo Id
 * @return space, que es el puntero a la estructura Space
 */
Space* space_create(Id id);



/**
 * @author Francisco Nanclares
 * @brief Libera memoria para space
 * @param space: puntero a Space.
 * @return status OK o ERROR.
 */
STATUS space_destroy(Space* space);



/**
 * @author Alejandro Martin
 * @brief Pone o cambia el nombre del espacio
 * @param space: puntero a Space.
 * @param name: puntero a char.
 * @return status OK o ERROR.
 */
STATUS space_set_name(Space* space, char* name);



/**
 * @author Alejandro Martin
 * @brief Pone o cambia el north
 * @param space: puntero a Space
 * @param id: campo de Id
 * @return status OK o ERROR o NO_ID
 */
STATUS space_set_north(Space* space, Id id);



/**
 * @author Alejandro Martin
 * @brief Pone o cambia el south
 * @param space: puntero a Space.
 * @param id: del type Id
 * @return status OK o ERROR o NO_ID
 */
STATUS space_set_south(Space* space, Id id);



/**
 * @author Alejandro Martin
 * @brief Pone o cambia el east
 * @param space: puntero a Space.
 * @param name: puntero a char.
 * @return status OK o ERROR o NO_ID
 */
STATUS space_set_east(Space* space, Id id);



/**
 * @author Alejandro Martin
 * @brief Pone o cambia el west
 * @param space: puntero a Space.
 * @param id: del type Id
 * @return status OK o ERROR o NO_ID
 */
STATUS space_set_west(Space* space, Id id);



/**
 * @author Alejandro Martin
 * @brief Devuelve el nombre (casilla)
 * @param space: puntero a Space.
 * @return name, el name space->name o NULL
 */
const char * space_get_name(Space* space);



/**
 * @author Alejandro Martin
 * @brief Devuelve el id (casilla)
 * @param space: puntero a Space.
 * @return id, el id space->id o NO_ID
 */
Id space_get_id(Space* space);



/**
 * @author Alejandro Martin
 * @brief Devuelve el id de la casilla del norte
 * @param space: puntero a Space.
 * @return norte, space->north o NO_ID
 */
Id space_get_north(Space* space);



/**
 * @author Alejandro Martin
 * @brief Devuelve el id de la casilla del sur
 * @param space: puntero a Space.
 * @return south, space->south o NO_ID
 */
Id space_get_south(Space* space);



/**
 * @author Alejandro Martin
 * @brief Devuelve el id de la casilla del norte
 * @param space: puntero a Space.
 * @return norte, space->north o NO_ID
 */
Id space_get_east(Space* space);



/**
 * @author Alejandro Martin
 * @brief Devuelve el id de la casilla del oeste
 * @param space: puntero a Space.
 * @return west, space->west o NO_ID
 */
Id space_get_west(Space* space);



/**
 * @author Alejandro Martin
 * @brief Muestra por la pantalla de salida, tanto el id, como el nombre del espacio
 * @param space: puntero a Space.
 * @return status, OK o ERROR o NO_ID
 */
STATUS space_print(Space* space);



/*----------------------------Descripcion Grafica(manejo de parametros)-------------------------------*/

/**
 * @author Francisco Nanclares
 * @brief Descripcion grafica ,Carga el espacio (primera linea de la representacion
    grafica , en codigo ASCII) 7 espacios
 * @param space: puntero a Space.
 * @param cadena , puntero a char (string)
 * @return status, OK o ERROR o NO_ID
 */
STATUS space_set_gdesc1(Space* space, char* cadena);



/**
 * @author Francisco Nanclares
 * @brief Descripcion grafica ,Carga el espacio (segunda linea de la representacion
    grafica , en codigo ASCII) 7 espacios
 * @param space: puntero a Space.
 * @param cadena , puntero a char (string)
 * @return status, OK o ERROR o NO_ID
 */
STATUS space_set_gdesc2(Space* space, char* cadena);



/**
 * @author Francisco Nanclares
 * @brief Descripcion grafica ,Carga el espacio (tercera linea de la representacion
    grafica , en codigo ASCII) 7 espacios
 * @param space: puntero a Space.
 * @param cadena , puntero a char (string)
 * @return status, OK o ERROR o NO_ID
 */
STATUS space_set_gdesc3(Space* space, char* cadena);



/**
 * @author Francisco Nanclares
 * @brief Descripcion grafica  , obtener el string de la descripcion grafica
    en este caso la primera
 * @param space: puntero a Space.
 * @return char, retorna el string de la descripcion grafica (1)
 */
char* space_get_gdesc1(Space* space);


/**
 * @author Francisco Nanclares
 * @brief Descripcion grafica  , obtener el string de la descripcion grafica
    en este caso la segunda
 * @param space: puntero a Space.
 * @return char, retorna el string de la descripcion grafica (2)
 */
char* space_get_gdesc2(Space* space);



/**
 * @author Francisco Nanclares
 * @brief Descripcion grafica  , obtener el string de la descripcion grafica
    en este caso la tercera
 * @param space: puntero a Space.
 * @return char, retorna el string de la descripcion grafica (3)
 */
char* space_get_gdesc3(Space* space);

/*----------------------------Manejo de Objetos modulo Space-------------------------------*/

/**
 * @author Alejandro Martin
 * @brief Quita el ultimo objeto de la casilla
 * @param space: puntero a Space.
 * @return status, OK o ERROR.
 */
STATUS space_delete_object(Space* space);



/**
 * @author Alejandro Martin
 * @brief Colocamos en el space un objeto
 * @param space: puntero a Space.
 * @param id: Id (identificador)
 * @return status, OK o ERROR.
 */
STATUS space_add_object(Space* space, Id id);



/**
 * @author Alejandro Martin
 * @brief Devuelve el si hay o no objeto en la casilla
 * @param space: puntero a Space.
 * @return object, space->object o FALSE si no existen objetos
 */
Set * space_get_objects(Space* space);



/**
 * @author Francisco Nanclares
 * @brief Comprueba si un objeto esta en el espacio actual
 * @param space: puntero a Space.
 * @param id_objeto, de tipo id.
 * @return BOOL, TRUE or FALSE (si parámetros vacios/obtención de la estructura
    con errores/si sale en el bucle de comprobación (de set_delete))
 */
BOOL object_check_in_space (Space *space , Id id_objeto);

#endif
