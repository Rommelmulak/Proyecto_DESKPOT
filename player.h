/**
*@brief Manejo de jugadores (funcionalidad)
*
*
*@file player.h
*@author FJNR & AMH & CMF & MLR
*@version 1.0
*@date 06/02/2018
*@copyright GNU Public License
*/

#ifndef PLAYER_H
#define PLAYER_H
#include "types.h"
#include "space.h"
#include "object.h"


/**
 * @brief Estructura que define un jugador(características)
 */
typedef struct _Player Player;

/**
 * @author Miguel Angel Lianno
 * @brief Se encarga de crear el player,
   y poner el caracter fin de cadena al final del nombre de este
 * @param id, de tipo Id
 * @return newPlayer, que es el puntero a la estructura
 */
Player* player_create (Id id);



/**
 * @author Miguel Angel Lianno
 * @brief Libera memoria para player.
 * @param Player: puntero a Player .
 * @return status OK o ERROR.
 */
STATUS player_destroy (Player * player);



/**
 * @author Miguel Angel Lianno
 * @brief Pone o cambia el nombre del player
 * @param objeto: puntero a Objeto.
 * @param name: puntero a char.
 * @return status OK o ERROR.
 */
STATUS player_set_name (Player* , char* name);



/**(NO SE NECESITA)
 * @brief Pone o cambia el objeto del inventario
 * @param objeto: puntero a Objeto.
 * @param objeto: campo de Objeto.
 * @return status OK o ERROR.
 */
STATUS player_set_object(Player* player,Id object);



/**
 * @author Miguel Angel Lianno
 * @brief Pone o cambia la localizacion de player
 * @param player: puntero a Player.
 * @param location: campo de Space.
 * @return status OK o ERROR.
 */
STATUS player_set_location(Player* player,Id location);



/**
 * @author Miguel Angel Lianno
 * @brief Devuelve el nombre asignado a un player
 * @param player: puntero a player.
 * @return name, el nombre que asignamos al player
 */
const char * player_get_name(Player* player);



/**(NO SE NECESITA)
 * @brief Devuelve la inventory_item
 * @param jugador: puntero a Jugador.
 * @return player->inventory_item (objeto)
 */
Id player_get_inventory_item(Player* player);



/**
 * @author Miguel Angel Lianno
 * @brief Devuelve el set de objetos de un jugador
 * @param player: puntero a Player.
 * @return player->inventory_items (puntero a Set)
 */
Set *player_get_inventory_items (Player *player);



/**
 * @author Miguel Angel Lianno
 * @brief Devuelve el set de objetos de un jugador
 * @param player: puntero a Player.
 * @return player->inventory_items (puntero a Set)
 */
Set *player_get_inventory_items (Player *player);



/**
 * @author Miguel Angel Lianno
 * @brief Devuelve la location
 * @param player: puntero a Player.
 * @return player->location(localizacion)
 */
Id player_get_location(Player* player);



/**
 * @author Miguel Angel Lianno
 * @brief Devuelve el id del player
 * @param player: puntero a player.
 * @return player->player_id(identificador)
 */
Id player_get_id(Player * player);


/**
 * @author Miguel Angel Lianno
 * @brief Quita un objeto al jugador
 * @param pla: puntero a player.
 * @return status OK o ERROR
 */
STATUS player_delete_inventory_item(Player *player);


/**
 * @author Miguel Angel Lianno
 * @brief Pone un objeto al jugador
 * @param pla: puntero a player.
 * @param id: Identificador
 * @return status OK o ERROR
 */
STATUS player_add_inventory_item(Player *player , Id id);



/**
 * @author Miguel Angel Lianno
 * @brief Muestra por la pantalla de salida, tanto el id, como el nombre del player
 * @param player: puntero a player.
 * @return status, OK o ERROR
 */
 /**
 * USO ALTERNATIVO ==> PLAYER PRINT: Control de errores Debugging
 */
STATUS player_print(Player* player);

#endif
