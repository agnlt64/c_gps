#pragma once

#include <stdio.h>

#include "city.h"

#ifdef DEBUG
#define NB_COMMANDS 11
#else
#define NB_COMMANDS 10
#endif

static const char* all_commands[NB_COMMANDS] = {
    "a", "s", "m", "l", "h", "q", "r", "e", "o", "t",
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

// Affiche les coordonnées d'une ville
void repl_search_city(City_Array* city_arr);

// Enregistre le contenu du tableau dans un fichier CSV
void repl_dump_to_csv(City_Array city_arr);

// Trie les villes par rapport à leur distance au Pole Nord
void repl_sort_by_distance(City_Array* city_arr);

// Fonction principale du REPL
void repl(City_Array* city_arr);
