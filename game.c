/**
*@brief Implementa la interfaz del juego y todas las llamadas para cada comando
*
*
*@file game.c
*@author FJNR & AMH
*@version 1.0
*@date 03/02/2018
*@copyright GNU Public License
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "game.h"
#include "game_reader.h"
#include "player.h"
#include "object.h"
#include "set.h"
#include "space.h"
#include "dice.h"

/*Evitar numeros "magicos" por el codigo*/
#define ID_J 1/*Id del player*/
#define ID_O 1/*Id del objeto*/
#define ID_DICE 1 /*Id del dado*/
#define INIC_P 0/*Posicion inicial del jugador*/
#define MAX_INPUT_OBJ/*tamano del nombre del objeto*/
#define MAX_CASILLAS 12 /*Numero de casillas (variable si modifi. data.dat)*/

#define N_CALLBACK 9 /*Numero maximo de callbacks*/

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

/**
   Define el tipo de función para las llamadas a esta
*/
typedef void (*callback_fn)(Game* game);

/**
   Funciones de llamada para comando
*/
void game_callback_unknown(Game* game);
void game_callback_exit(Game* game);
void game_callback_following(Game* game);
void game_callback_previous(Game* game);
void game_callback_left (Game *game);
void game_callback_right (Game *game);
void game_callback_get(Game* game);
void game_callback_drop(Game* game);
void game_callback_roll_dice(Game *game);

/**
Array de punteros a funciones
static = unico en este modulo (evitar que se exponga) (cuidadin)
*/
static callback_fn game_callback_fn_list[N_CALLBACK]={
  game_callback_unknown,
  game_callback_exit,
  game_callback_following,
  game_callback_previous,
  game_callback_left,
  game_callback_right,
  game_callback_get,
  game_callback_drop,
  game_callback_roll_dice
};


/**
   Funciones privadas, las cuales solo se ponen en el fichero.c
*/



/*
 * @author Alejandro Martin
 * @brief Retorna el id de una casilla (asociándola con una posición predeterminada)
 * @param game, puntero a estructura,(dirección)
 * @param position, posición del espacio (en el array de punteros a Space)
 * @return NO_ID (si la posicion se sale de los límites), y si no, space_get_id (la posición)
 */
Id     game_get_space_id_at(Game* game, int position);


 /*----------------------------------------------*/



/*
 * @author Francisco Nanclares
 * @brief Inicialización de la estructura Game
 * @param game, puntero a estructura Game (dirección)
 * @return status, OK O ERROR
 */
STATUS game_create(Game* game) {
  int i;

  for (i = 0; i < MAX_SPACES; i++) {/*Vacia el array spaces*/
    game->spaces[i] = NULL;
    /*  game->object = object_create(ID_O);*//*1*/

  }
  game->player = player_create(ID_J);/*1*/
  /*game->player = player_create(ID_P)
    game_set_player_location(game,NO_ID)*/
  game_set_player_location(game,NO_ID);

  for (i=0;i<MAX_ID;i++){
    game->objects[i] = NULL;
  }

  game->last_cmd = NO_CMD;
  game->dice =dice_create(ID_DICE);/*1*/
  game->param = " ";

  return OK;
}



/*
 * @author Francisco Nanclares
 * @brief Crea el juego, carga las casillas (data.dat) y ponen el objeto y jugador
    en la posición primera.
 * @param game, puntero a estructura Game (dirección)
 * @param filename, fichero de casillas (data.dat)
 * @return status, OK O ERROR
 */
STATUS game_create_from_file(Game* game, char* filename) {
  if (game_create(game) == ERROR)
    return ERROR;

  if (game_reader_load_spaces(game, filename) == ERROR){
    return ERROR;
  }
  if (game_reader_load_objects(game,filename)==ERROR){
    return ERROR;
  }
    /*Colocamos en casilla 0 a player y random al player*/
  game_set_player_location(game, game_get_space_id_at(game, INIC_P));
  return OK;
}



/*
 * @author Alejandro Martin
 * @brief Elimina las casillas creadas en la función anterior
 * @param game, puntero a estructura Game (dirección)
 * @return status, OK O ERROR
 */
STATUS game_destroy(Game* game) {
  int i;

  for (i=0; i<MAX_SPACES && game->spaces[i] != NULL; i++) {
    space_destroy(game->spaces[i]);
    game->spaces[i]=0;
  }

  for (i=0;i<MAX_ID && game->objects[i] != NULL ;i++){
    object_destroy(game->objects[i]);
  }

  player_destroy(game->player);
  dice_destroy(game->dice);

  return OK;
}



/*
 * @author Alejandro Martin
 * @brief Crea una casilla una vez comprobado el array (hasta que apunte a NULL)
    el espacio que se añade es el parámetro
 * @param game, puntero a estructura Game (dirección)
 * @param space , puntero a estructura Space (dirección)
 * @return status, OK O ERROR
 */
STATUS game_add_space(Game* game, Space* space) {
  int i = 0;

  if (space == NULL) {
    return ERROR;
  }

  while ( (i < MAX_SPACES) && (game->spaces[i] != NULL)){
    i++;
  }

  if (i >= MAX_SPACES) {
    return ERROR;
  }

  game->spaces[i] = space;

  return OK;
}



/*
 * @author Francisco Nanclares
 * @brief Crea un objeto , comprobando el array de objetos ,lo recorre Entero
    hasta que se acaba y anade el objeto pasado por parametro
 * @param game, puntero a estructura Game (dirección)
 * @param object , puntero a estructura Object
 * @return status, OK O ERROR
 */
STATUS game_add_object (Game * game , Object* object){
  int i;

  if (game == NULL || object == NULL){
    return ERROR;
  }
  for (i=0;i<MAX_ID && game->objects[i]!= NULL; i++);

  if (i >= MAX_ID){
    return ERROR;
  }
  /*anade el objeto pasado por argumento*/
  game->objects[i] = object;
  return OK;
}

/*
 * @author Francisco Nanclares
 * @brief Retorna el id de una casilla (asociándola con una posición predeterminada)
 * @param game, puntero a estructura,(dirección)
 * @param position, posición del espacio (en el array de punteros a Space)
 * @return NO_ID (si la posicion se sale de los límites), y si no, space_get_id (la posición)
 */
Id game_get_space_id_at(Game* game, int position) {

  if (position < 0 || position >= MAX_SPACES) {
    return NO_ID;
  }

  return space_get_id(game->spaces[position]);
}



/*
 * @author Francisco Nanclares
 * @brief Retorna la casilla (asociándola con una posición predeterminada)
    y con el id (param)
 * @param game, puntero a estructura,(dirección)
 * @param id, Entero (identificador)
 * @return NULL (si el id esta corrupto, o al final de la función),
    y el array "spaces", de la estructura, si coincide con el id pasado como argumento
 */
Space* game_get_space(Game* game, Id id){
  int i = 0;

  if (id == NO_ID) {
    return NULL;
  }

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    if (id == space_get_id(game->spaces[i])){
      return game->spaces[i];
    }
  }

  return NULL;
}



/*
 * @author Alejandro Martin
 * @brief Retorna el objeto (asociándola con una posición predeterminada)
    y con el id (param)
 * @param game, puntero a estructura,(dirección)
 * @param id, Entero (identificador)
 * @return NULL (si el id esta corrupto, o al final de la función),
    y el array "objects", de la estructura, si coincide con el id pasado como argumento
 */
Object* game_get_object(Game* game, Id id){
  int i = 0;

  if (id == NO_ID) {
    return NULL;
  }

  for (i = 0; i < MAX_ID && game->objects[i] != NULL; i++) {
    if (id == object_get_id(game->objects[i])){
      return game->objects[i];
    }
  }

  return NULL;
}


/*
 * @author Alejandro Martin
 * @brief Esta funcion,
 * @param game, puntero a estructura,(dirección)
 * @param name, puntero a char
 * @return
 */
Id game_object_get_id (Game *game , char *name){
  int i;
  char *aux;

  if (!game || !name ){
    return NO_ID;
  }
  for (i=0;i<MAX_ID;i++){
    /*Obtengo el nombre del objeto de todos los id posibles, con el bucle
      se lo asigno a aux que posteriormente será comparado, si el parametro
      es lo mismo se retorna el id de ese objeto*/
    aux = object_get_name(game->objects[i]);
    if (strcasecmp(name,aux)==0){
      return object_get_id(game->objects[i]);
    }
  }

  return NO_ID;
}
/**
 * @author Francisco Nanclares
 * @brief funcionalidad de modificar la localizacion del jugador mediante el id
 * @param game, puntero a Game (dirección)
 * @param id, Entero de tipo Id (identificador)
 * @return status, OK O ERROR
 */
STATUS game_set_player_location(Game* game, Id id) {
  if (id == NO_ID) {
    return ERROR;
  }/*game_get_space (game,id)=>id*/
  if (player_set_location(game->player,id)==ERROR){
    return ERROR;
  }

  return OK;
}



/**
 * @author Francisco Nanclares
 * @brief funcionalidad de modificar la localizacion del objeto mediante el id
 * @param game,puntero a la estructura Game
 * @param id_espacio, campo de la estructura Id
 * @param object, puntero a la estructura de object
 * @return status, OK O ERROR
 */
 /*acordarse de donde se encuentra la funcionalidad y donde se llama a ella  */
STATUS game_set_object_location(Game* game, Id id_espacio,Object * object) {
  int i;
  Id space_aux , object_id_aux;

  if (!game || id_espacio == NO_ID || object == NULL) {
    return ERROR;
  }

  for (i=0;i<MAX_SPACES;i++){
    space_aux = space_get_id(game->spaces[i]);
    /*Si id del arg coincide con el del espacio que busca el bucle coloca objeto*/
    if (space_aux == id_espacio){
      object_id_aux = object_get_id(object);
      space_add_object(game->spaces[i],object_id_aux);
      return OK;

    }
  }
    /*object_set_location (game->object,id);*/
  return ERROR;
}



/**
 * @author Alejandro Martin
 * @brief Devuelve la posicion del jugador (estructura game)
 * @param game, puntero a la estructura Game
 * @return la posición del jugador, modificada de la estructura
 */
Id game_get_player_location(Game* game) {

  return player_get_location(game->player);
}


/*Como antes , solucion alternativa si en vez de pasar un object pasamos un id
for (i=0;i<MAX_ID;i++){
  object_aux = object_get_id(game->objects[i]);
  if (object_aux == id_objeto){
    printf ("%d\n",(int)object_aux);

  }
}*/
/**
 * @author Francisco Nanclares
 * @brief Devuelve la posicion del objeto (estructura game)
 * @param game, puntero a la estructura Game
 * @return la posición del objeto, modificada de la estructura
 *//*  return location(id) o NO_ID (id)
*/
Id game_get_object_location(Game* game,Object *object) {
  int i,j;
  Id space_id_aux , object_id_aux, location;
  Set * set;

  if (!game || !object){
    return NO_ID;
  }
  else {
    object_id_aux = object_get_id(object);

    for (i=0;i<MAX_SPACES;i++){
      set = space_get_objects(game->spaces[i]);

      for (j=0;j<set_get_top(set);j++){
        space_id_aux = get_specific_id(set,j);
        /*Si id (objeto_en_casilla) == id (objeto)*/
        if (space_id_aux == object_id_aux){
          location = space_get_id(game->spaces[i]);

          return location;
        }
      }
    }
  }
  return NO_ID;/*puede darse el caso de que no lo encuentre porque no este*/
}


/**
 * @author Francisco Nanclares
 * @brief Obtiene los id, los campara, y nos dice si hay objeto
 * @param game, puntero a la estructura Game
 * @param object, puntero a object
 * @return bool, TRUE or FALSE
 */
BOOL game_get_object_player(Game* game , Object* object){
  int i;
  Id id_player_aux , id_obj_aux;
  Set *set;

  if (!game || !object){
    return FALSE;
  }
  /* Coge el id del objeto, para despues comparar los auxiliares de objeto y jugador*/
  id_obj_aux = object_get_id(object);
  set = player_get_inventory_items(game->player);
  /*Se recorre el array de objetos hasta el tope (del Set)*/
  for (i=0;i<set_get_top(set);i++){
    /*Cada vez que se entra en el bucle, el id del jugador toma el id especifico del
      set y compara con el del objeto pasado por referencia. Si coinciden, hay objeto*/
    id_player_aux = get_specific_id(set,i);

    if (id_player_aux == id_obj_aux){
      return TRUE;
    }
  }

  return FALSE;
}



/**
 * @author Alejandro Martin
 * @brief Actualizacion de los comandos (muestra el último).
 * @param game, puntero a la estructura Game
 * @param cmd, enumeración (identificador de cada comando)
 * @return status, OK O ERROR
 */
STATUS game_update(Game* game, T_Command cmd,char *param,FILE *pf) {
  extern char *cmd_to_str[];
  game->flag_command = ERROR;
  game->last_cmd = cmd;
  game->param = param;
  (*game_callback_fn_list[cmd])(game);
  if (pf != NULL){
    if (game->flag_command == ERROR){
      fprintf(pf,"%s:ERROR\n",cmd_to_str[cmd-NO_CMD]);
    }
    else {
      fprintf(pf,"%s:OK\n",cmd_to_str[cmd-NO_CMD]);
    }
  }
  return OK;
}



/**
 * @author Alejandro Martin
 * @brief Devuelve el último comando que se ha introducido.
 * @param game, puntero a la estructura Game
 * @return cmd, el último comando.
 */
T_Command game_get_last_command(Game* game){

  return game->last_cmd;
}



/**
 * @author Francisco Nanclares
 * @brief Imprime la "info" de todas las casillas ,y la posición del jugador y
    de los objetos.
 * @param game, puntero a la estructura Game
 * @return nada
 */
void game_print_data(Game* game) {
  int i = 0;

  printf("\n\n-------------\n\n");

  printf("=> Spaces: \n");
  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    space_print(game->spaces[i]);
  }
  printf("=> Player location: %d\n", (int) game_get_player_location(game));

  for (i=0;i<MAX_ID && game->objects[i] != NULL; i++){
    printf("=>Object location %d \n",(int)(game_get_object_location(game,game->objects[i])));
  }

  printf("prompt:> ");
}



/*
 * @author Francisco Nanclares
 * @brief modificamos un string (parametro) descripcion grafica
 * @param game, puntero a estructura Game (dirección)
 * @param param, de tipo puntero a char (string) (el parametro)
 * @return nada, es de tipo void
 */
void game_set_parametro (Game * game , char *param){
  if (strcmp(param,object_get_name(game_get_object(game,game_get_player_location(game))))!=0){
    game->flag_command = ERROR;
  }
  game->param = param;

  game->flag_command = OK;
}
/**
 * @author Alejandro Martin
 * @brief Posible llamada a la finalización del juego
 * @param game, puntero a la estructura Game
 * @return bool, TRUE or FALSE
 */
BOOL game_is_over(Game* game) {

  return FALSE;
}

/*----------------------------------------------*/
/**
   Callbacks : implementación para cada comando.
*/

void game_callback_unknown(Game* game) {
  game->flag_command = ERROR;
}
void game_callback_exit(Game* game) {
  game->flag_command = OK;
}



/**
 * @author Francisco Nanclares
 * @brief Implementa la función del comando following
 * @param game, puntero a la estructura Game
 * @return nada, ya que es una función de tipo void
 */
void game_callback_following(Game* game) {
  int i = 0;
  Id current_id = NO_ID;/*-1*/
  Id space_id = NO_ID;/*id del jugador*/

  space_id = game_get_player_location(game);
  if (space_id == NO_ID) {
    game->flag_command = ERROR;
    return;
  }
  game->flag_command = ERROR;

  /*Recorre todos los espacios*/
  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    current_id = space_get_id(game->spaces[i]);

    if (current_id == space_id) {
      current_id = space_get_south(game->spaces[i]);

      if (current_id != NO_ID) {
	       game_set_player_location(game, current_id);
         game->flag_command = OK;
      }
      return;
    }
  }
}



/**
 * @author Francisco Nanclares
 * @brief Implementa la función del comando previous
 * @param game, puntero a la estructura Game
 * @return nada, ya que es una función de tipo void
 */
void game_callback_previous(Game* game) {
  int i = 0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);

  if (NO_ID == space_id) {
    game->flag_command = ERROR;
    return;
  }
  game->flag_command = ERROR;

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    current_id = space_get_id(game->spaces[i]);

    if (current_id == space_id) {
      current_id = space_get_north(game->spaces[i]);

      if (current_id != NO_ID) {
	       game_set_player_location(game, current_id);
         game->flag_command = OK;
      }
      return;
    }
  }
}


/**
 * @author Alejandro Martin
 * @brief Implementa la función del comando left
 * @param game, puntero a la estructura Game
 * @return, ya que es una función de tipo void
 */
void game_callback_left (Game *game){
  int i;
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location (game);

  if (NO_ID == space_id){
    return;
  }
  for (i=0;i<MAX_SPACES && game->spaces[i] != NULL; i++){
    current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id) {
      current_id = space_get_west(game->spaces[i]);

      if (current_id != NO_ID){
        game_set_player_location(game , current_id);
      }
      return;
    }
  }
}



/**
 * @author Alejandro Martin
 * @brief Implementa la función del comando right
 * @param game, puntero a la estructura Game
 * @return, ya que es una función de tipo void
 */
void game_callback_right (Game *game){
  int i;
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location (game);

  if (NO_ID == space_id){
    return;
  }
  for (i=0;i<MAX_SPACES && game->spaces[i] != NULL; i++){
    current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id) {
      current_id = space_get_east(game->spaces[i]);

      if (current_id != NO_ID){
        game_set_player_location(game , current_id);
      }
      return;
    }
  }
}



/**
 * @author Francisco Nanclares
 * @brief Implementa la función del comando get
 * @param game, puntero a la estructura Game
 * @return, ya que es una función de tipo void
 */
void game_callback_get(Game* game) {
  Id current_id = NO_ID;
  Space *current_space = NULL;
  Id id_object = NO_ID;
  Set *set = NULL;

  current_id = game_get_player_location(game);

  if (NO_ID == current_id) {
    game->flag_command = ERROR;
    return;
  }

  current_space = game_get_space(game, current_id);

  if (current_space == NULL){
    game->flag_command = ERROR;
    return;
  }
  /*POR AHORA NOfprintf (stdout,"Dime el objeto que quieres coger del espacio: ");
  scanf("%s", ) */

  set = space_get_objects(current_space);
  /* Si el jugador está en casilla con un objeto,
   y decide cogerlo (se le asigna) y desaparece de la casilla */
  if (set_ISempty(set) == TRUE || set == NULL){/*1 significa que esta vacio (sentimos el numero magico)<=definido en set.h*/
    game->flag_command = ERROR;
    return;
  }

  id_object = game_object_get_id(game,game->param);
  if (id_object == NO_ID){
    game->flag_command = ERROR;
    return;
  }
  if (object_check_in_space(current_space,id_object)==TRUE){
    if (delete_id(set,id_object)==ERROR){
      game->flag_command = ERROR;
      return;
    }
    if (player_add_inventory_item(game->player,id_object)==ERROR){
      game->flag_command = ERROR;
      return;
    }
  }
  game->flag_command = OK;
  return;
}



/**
 * @author Francisco Nanclares
 * @brief Implementa la función del comando drop
 * @param game, puntero a la estructura Game
 * @return, ya que es una función de tipo void
 */
void game_callback_drop(Game* game) {
  int i;
  Id current_id = NO_ID;
  Set * set= NULL;
  Set *p_player_set = NULL;
  Object* p_object =NULL;
  Space *current_space = NULL;
  Id id_object = NO_ID;
  current_id = game_get_player_location(game);

  p_player_set = player_get_inventory_items(game->player);
  if (set_ISempty(p_player_set) == TRUE){
    game->flag_command = ERROR;
    return;
  }

  current_id = game_get_player_location(game);

  if (NO_ID == current_id) {
    game->flag_command = ERROR;
    return;
  }

  current_space = game_get_space(game, current_id);

  if (current_space == NULL){
    game->flag_command = ERROR;
    return;
  }

  id_object = game_object_get_id(game,game->param);

  /*Set lo que hace es coger los objetos de la casilla actual
    y object recibe el objeto que tiene actualmente el jugador(Id)*/
  set = space_get_objects(current_space);

  if (set == NULL){
    game->flag_command = ERROR;
    return;
  }
  if (delete_id(p_player_set ,id_object) == ERROR){
    game->flag_command = ERROR;
    return;
  }
  for (i=0,p_object = game->objects[0];i<MAX_ID && object_get_id(p_object) != id_object;i++,p_object = game->objects[i]);

  game_set_object_location(game,current_id,p_object);
  /*PLAYER PRINT*/
  game->flag_command = OK;

  return;

}



/**
 * @author Alejandro Martin
 * @brief Implementa la función del comando roll
 * @param game, puntero a la estructura Game
 * @return, ya que es una función de tipo void
 */
void game_callback_roll_dice(Game *game){
  if (game == NULL){
    game->flag_command = ERROR;
    return;
  }
  dice_roll(game->dice);
  game->flag_command = OK;
  return;
}


/**
 * @author Francisco Nanclares
 * @brief Hace flag del cmd
 * @param game, puntero a la estructura Game
 * @return flag_command, que es la flag de la estructura game
 */
STATUS game_get_last_command_flag(Game *game){
  return game->flag_command;
}
