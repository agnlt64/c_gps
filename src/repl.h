#pragma once

#include <stdio.h>

#include "city.h"

#ifdef DEBUG
#define NB_COMMANDS 8
#else
#define NB_COMMANDS 7
#endif

static const char* all_commands[NB_COMMANDS] = {
    "a", "s", "m", "l", "h", "q", "r",
#ifdef DEBUG
    "d",
#endif
};

// Affiche la liste des commandes displonibles au sein du REPL
void repl_help();

// Renvoie true si la commande est valide, false sinon
bool repl_is_valid_command(const char* command);

// Récupère les informations d'une ville à partir de la console
void repl_get_city_infos(char* name, int* code, double* latitude, double* longitude);

// Récupère le nom d'une ville à partir de la console
void repl_get_city_name(char* name);

// Ajoute une ville au tableau
void repl_add_city(City_Array* city_arr, bool modified);

// Modifie une ville si elle existe
void repl_modify_city(City_Array* city_arr);

// Enlève une ville du tableau
void repl_delete_city(City_Array* city_arr);

// Fonction principale du REPL
void repl(City_Array* city_arr);