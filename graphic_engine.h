/**
 * @brief Define un motor gráfico
 *
 * @file graphic_engine.h
 *@author FJNR & AMH & CMF & MLR
 * @version 1.0
 *@date 05/02/2018
 * @copyright GNU Public License
 */

#ifndef __GRAPHIC_ENGINE__
#define __GRAPHIC_ENGINE__

#include "game.h"

/**
 * @brief Estructura que define el Graphic_engine tamaño del area
*/
typedef struct _Graphic_engine Graphic_engine;



/**
 * @author Francisco Nanclares
 * @brief Tiene la función de crear el área (se generan unos puntos en la
    pantalla con: (x,y,width,height)) de los interfaces del juego
    (inicializa la estructura de Graphic_engine)
 * @param nada
 * @return "ge", el puntero que contiene los elementos de la estructura
    (punteros de tipo Area)
 */
Graphic_engine* graphic_engine_create();



/**
 * @author Francisco Nanclares
 * @brief Tiene la función de liberar la memoria de todos los campos de ge
 * @param "ge", el puntero a "Graphic_engine"
 * @return, ya que es una función de tipo void
 */
void graphic_engine_destroy(Graphic_engine *ge);



/**
 * @author Francisco Nanclares
 * @brief Dibuja cada área en la pantalla de salida (se generan puntos en la
    pantalla con: (x,y,width,height))
 * @param "ge",  el puntero a "Graphic_engine"
 * @param "game", el puntero a "Game"
 * @return, ya que es una función de tipo void
 */
void graphic_engine_paint_game(Graphic_engine *ge, Game *game);

/**
 * @author Francisco Nanclares
 * @brief Imprime los comandos recibidos por argumento en la zona del motor gráfico dado por argumento
 * @params puntero a Graphic_engine, y puntero a char
 * @return void
 */
void graphic_engine_write_command(Graphic_engine *ge, char *str);

#endif
