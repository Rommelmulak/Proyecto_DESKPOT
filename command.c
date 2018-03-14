/*
*@brief Implementa los comandos
*
*@file command.c
*@author FJNR & AMH
*@version 1.0
*@date 01/02/2018
*@copyright GNU Public License
*/

#include <stdio.h>
#include <strings.h>
#include <string.h>
#include "command.h"

#define CMD_LENGHT 128 /*Longuitud maxima de comando*/
#define N_CMD 10 /*Numero maximo de comandos*/

/* Puntero a char, es una tabla de comandos que el jugador introduce por pantalla */
char *cmd_to_str[N_CMD] = {"No command", "Unknown", "Exit", "Following", "Previous","Left","Right","Get","Drop","dice_roll"};
/*Puntero a char, es una tabla de comandos que tendra que pulsar el jugador en la partida*/
char *short_cmd_to_str[N_CMD] = {"","","e","f","p","l","r","g","d","t"};


/**
* @author Alejandro Martin
* @brief Implementa los comandos, recogiendo el "input" ,
   transformándolo en un valor numérico de T_command;
* @param No param.
* @return cmd (campo de estructura T_command)
*/
T_Command get_user_input(char *p){
  T_Command cmd = NO_CMD;/*-1*/
  char input[CMD_LENGHT] = "";/*Variable "input" (string), leera el comando*/
  int i=UNKNOWN - NO_CMD + 1; /*2*/
  char * palabra =NULL;
  *p = '\0';

  if (fgets(input,sizeof(input),stdin) != NULL){/*Si lee el comando correctamente*/
    cmd = UNKNOWN; /*cmd=0, siempre*/
    input[strlen(input)-1]='\0';
    palabra = strtok(input, " "); /*Esto hace que coja la palabra hasta el espacio el blanco*/

    while (cmd == UNKNOWN && i < N_CMD){ /*Compara el comando introducido por el jugador con los de la lista*/

      if (!strcasecmp(palabra,short_cmd_to_str[i]) || !strcasecmp(palabra,cmd_to_str[i])){/*Si coinciden "cmd" = el valor que le correponde*/
        cmd = i /*=2*/ + NO_CMD/*=-1*/;
        palabra = strtok(NULL, " "); /*Las demas veces que llamamos a strtok lo hacemos con NULL, pues ya cogio la cadena*/

	 /*Control de errores*/
        if(palabra==NULL){
          if (cmd == GET || cmd == DROP){
            return UNKNOWN;
          }
        }
        else{
          if (cmd == GET || cmd == DROP){
            strcpy(p, palabra); /*Copiamos la cadena partida en el parametro*/
          }
          else{
            return UNKNOWN;
          }
        }
      }
      else {
	      i++; /*Despues del control de errores, comprobamos en otros cmd*/
      }
    }
  }

  return cmd;
}
