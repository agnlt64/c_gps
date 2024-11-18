#pragma once

#include <stdio.h>

#include "city.h"

#ifdef DEBUG
#define NB_COMMANDS 11
#else
#define NB_COMMANDS 10
#endif

static const char* all_commands[NB_COMMANDS] = {
    "a",
    "s",
    "m",
    "l",
    "o",
    "e",
    "r",
    "t",
#ifdef DEBUG
    "d",
#endif
    "h",
    "q",
};

static const char* commands_description[NB_COMMANDS] = {
    "Ajoute une ville",
    "Supprime une ville",
    "Modifie les données d'une ville",
    "Liste les villes",
    "Calcule la distance à vol d'oiseau entre 2 villes",
    "Exporte les données dans un fichier CSV",
    "Affiche la latitude et longitude d'une ville",
    "Trie les villes par rapport à leur distance au Pole Nord",
#ifdef DEBUG
    "Debug",
#endif
    "Affiche l'aide",
    "Quitte le programme",
};

// table des tailles de chaque description de commande.
// normalement strlen() fait le job, mais on des fois
// elle renvoie la taille + 1.
static const int desc_sizes[NB_COMMANDS] = {
    16,
    18,
    31,
    16,
    49,
    39,
    44,
    56,
#ifdef DEBUG
    5,
#endif
    14,
    19,
};

// Affiche la liste des commandes displonibles au sein du REPL
void repl_help();

// Renvoie true si la commande est valide, false sinon
bool repl_is_valid_command(const char* command);

// Récupère les informations d'une ville à partir de la console
void repl_get_city_infos(City_Array city_arr, char* name, int* code, double* latitude, double* longitude);

// Récupère le nom d'une ville à partir de la console
void repl_get_city_name(char* name);

// Récupère le code d'une ville à partir de la console
void repl_get_city_code(City_Array city_arr, int* code, bool check_unique);

// Ajoute une ville au tableau
void repl_add_city(City_Array* city_arr);

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
