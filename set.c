/**
*@brief Manejo de conjuntos
*
*
*@file set.c
*@author FJNR & AMH & CMF & MLR
*@version 1.0
*@date 19/02/2018
*@copyright GNU Public License
*/
#include <stdio.h>
#include <stdlib.h>

#include "set.h"
#include "types.h"

/*Para no desaprovechar memoria...*/
/*
#define Set_Empty(x) (x==0)Macro para ver si el conjunto esta vacio
#define Set_Full(x) (x > MAX_ID)Macro para ver si el conjunto esta lleno*/



/**
 * @brief Estructura que define un conjunto(características) 
*/
struct _Set {
  Id id_array[MAX_ID]; /*!< Identificador del stack*/
  int num_array_actual; /*!< Numero actual del stack*/
};



/**
 * @author  Carlos Miret
 * @brief Se encarga de crear el conjunto
 * @param nada
 * @return NULL o conj_create (nuevo conjunto recien creado)
 */
Set * set_create (){
  int i;
  Set *conj_create;
  conj_create = (Set*)malloc(sizeof(Set));
  if (conj_create == NULL){
    return NULL;
  }
  else {
    for (i=0;i<MAX_ID;i++){
      conj_create->id_array[i] = NO_ID;
    }
    conj_create->num_array_actual = 0;
  }
  return conj_create;
}



/**
 * @author Francisco Nanclares
 * @brief Se encarga de liberar el conjunto
 * @param set puntero a Set
 * @return nada (void)
 */
void set_destroy (Set * set){
  if (set == NULL){
    return;
  }
  else {
    free(set);

    return;
  }
}



/**
 * @author Alejandro Martin
 * @brief Se encarga de anadir un elemento (id) al conjunto
 * @param set puntero a Set
 * @param id (Id) identificador nuevo
 * @return status OK o ERROR
 */
STATUS set_push_id (Set *set , Id id){

  if (set == NULL || id == NO_ID){
    return ERROR;
  }
  /*mete el id en el tope*/
  set->id_array[set->num_array_actual] = id;
  /*suma uno al tope*/
  set->num_array_actual++;

  return OK;
}


/**
 * @author  Carlos Miret
 * @brief Se encarga de sacar un elmento si queremos
 * @param set puntero a Set
 * @return Id el identificador que usaremos
 */
Id  set_pop_id (Set *set){
  Id temp;

  if(!set){
    return NO_ID;
  }
  /*Set_empty no es una funcion, es una macro (devuelve 1 = verdadero)*/
  if (set_ISempty(set) == TRUE){
    return NO_ID;
  }
  else {
    /*coge el último elemento del array(dato)*/
    temp = set->id_array[(set->num_array_actual)-1];
    /*pone a NULL(NO_ID) ese tope para que se pueda volver a utilizar*/
    set->id_array[set->num_array_actual] = NO_ID;
    /*reduce el tope*/
    set->num_array_actual--;

    return temp;
  }
}


/**
 * @author Francisco Nanclares
 * @brief Imprimir por pantalla los elementos de la estructura
 * @param set, puntero a set
 * @return OK o ERROR, ya que es de tipo STATUS
 */
STATUS set_print(Set* set) {
  int i;
  if (set == NULL){
    return ERROR;
  }
  for (i=0;i<MAX_ID/*no necesario*/ || i<set->num_array_actual;i++){
    fprintf(stdout,"Elemento %d : %ld\n",i+1,set->id_array[i]);
  }
  fprintf(stdout,"La cantidad de elementos total es : %d",i);

  return OK;
}



/**
 * @author Francisco Nanclares
 * @brief Devuelve un id de la posicion que quieras
 * @param set, puntero a set
 * @param num_array_actual_para (int) que indica la posicion
 * @return Id (id_aux) identificador de la posicion
 */
Id get_specific_id (Set *set ,int num_array_actual_para){
  Id id_aux;
  if (set == NULL|| num_array_actual_para < 0 || num_array_actual_para > set->num_array_actual || set_ISempty(set) == TRUE){
    return NO_ID;
  }
  id_aux = set->id_array[num_array_actual_para];

  return id_aux;
}




/**
 * @author Alejandro Martin
 * @brief Coge el top
 * @param set, puntero a set
 * @return aux (el top como entero)
 */
int set_get_top (Set * set){
  int pos;
  if (set == NULL){
    return 0;
  }
  pos = set->num_array_actual;

  return pos;
}



/**
 * @author  Carlos Miret
 * @brief Comprueba si Set esta vacio (tiene alguna id)
 * @param set, puntero a set
 * @return status OK o ERROR
 */
BOOL set_ISempty(Set *set){
  if (set == NULL){
    return TRUE;
  }
  if (set->num_array_actual == 0){
    return TRUE;
  }
  return FALSE;
}



/**
 * @author  Carlos Miret
 * @brief Elimina una id del set la que se quiera (parametro)
 * @param set, puntero a set
 * @param id Identificador
 * @return status OK o ERROR
 */
STATUS delete_id (Set *set, Id id){
  int i,j;
  Id id_aux;
  STATUS flag = ERROR;
  if (set == NULL || id == NO_ID){
    return ERROR;
  }
  /*Lineas generales: encuentra id en el array y lo elimina (con mecanica parecida a pop)*/
  for (i=0; i<set->num_array_actual;i++){
    id_aux = get_specific_id (set, i);
    if(id == id_aux){
      for (j=i;j+1<MAX_ID && set->id_array[j] != NO_ID;j++){
        set->id_array[j] = set->id_array[j+1];
      }
      flag = OK;
      set->num_array_actual--;
    }
  }

  return flag;
}
