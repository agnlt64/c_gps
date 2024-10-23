#pragma once

#include <stdio.h>

#include "city.h"

// Affiche la liste des commandes displonibles au sein du REPL
void repl_help();

// Récupère les informations d'une ville à partir de la console
void repl_get_city_infos(char* name, int* code, double* latitude, double* longitude);

// Récupère le nom d'une ville à partir de la console
void repl_get_city_name(char* name);

// Ajoute une ville au tableau
void repl_add_city(City_Array city_arr);

// Enlève une ville du tableau
void repl_delete_city(City_Array city_arr);

// Fonction principale du REPL
void repl(City_Array city_arr);