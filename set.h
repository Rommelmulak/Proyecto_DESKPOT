/**
*@brief Manejo de conjuntos (interfaz)
*
*
*@file set.h
*@author FJNR & AMH
*@version 1.0
*@date 19/02/2018
*@copyright GNU Public License
*/

#ifndef SET_H
#define SET_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

/*Estructura que define un conjunto(características) */
typedef struct _Set Set;



/*
 * @author Francisco Nanclares
 * @brief Se encarga de crear el conjunto
 * @param nada
 * @return NULL o conj_create (nuevo conjunto recien creado)
 */
Set * set_create ();



/*
 * @author Francisco Nanclares
 * @brief Se encarga de liberar el conjunto
 * @param set puntero a Set
 * @return nada (void)
 */
void set_destroy (Set * set);



/*
 * @author Alejandro Martin
 * @brief Se encarga de anadir un elemento (id) al conjunto
 * @param set puntero a Set
 * @param id (Id) identificador nuevo
 * @return status OK o ERROR
 * @NOTA :Es la funcion add de la iteracion (pero nos parece mas logico llamarla
    de esta manera)
 */
STATUS set_push_id (Set *set , Id id);



/*
 * @author Alejandro Martin
 * @brief Se encarga de sacar un elmento si queremos
 * @param set puntero a Set
 * @return Id el identificador que usaremos
 * @NOTA :Es la funcion del de la iteracion (pero nos parece mas logico llamarla
    de esta manera)
 */
Id  set_pop_id (Set *set);



/*
 * @author Francisco Nanclares
 * @brief Imprimir por pantalla los elementos de la estructura
 * @param set, puntero a set
 * @return OK o ERROR, ya que es de tipo STATUS
 */
STATUS set_print(Set* set);


/*
 * @author Francisco Nanclares
 * @brief Devuelve un id de la posicion que quieras
 * @param set, puntero a set
 * @param num_array_actual_para (int) que indica la posicion
 * @return Id (id_aux) identificador de la posicion
 */
Id get_specific_id (Set *set ,int num_array_actual_para);



/*
 * @author Alejandro Martin
 * @brief Coge el top
 * @param set, puntero a set
 * @return aux (el top como entero)
 */
int set_get_top (Set * set);


/*
 * @author Alejandro Martin
 * @brief Comprueba si Set esta vacio (tiene alguna id)
 * @param set, puntero a set
 * @return status OK o ERROR
 */
BOOL set_ISempty(Set *set);



/*
 * @author Francisco Nanclares
 * @brief Elimina una id del set la que se quiera (parametro)
 * @param set, puntero a set
 * @param id Identificador
 * @return status OK o ERROR
 */
STATUS delete_id (Set *set, Id id);


#endif
