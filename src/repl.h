#pragma once

#include <stdio.h>

#include "gps_data.h"

// Affiche la liste des commandes displonibles au sein du REPL
void repl_help();

// Récupère les informations d'une ville à partir de la console
void repl_get_city_infos(char** name, int* code, double* latitude, double* longitude);

// Fonction principale du REPL
void repl(City_Array city);