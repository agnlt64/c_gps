#pragma once

#include <stdio.h>

#include "gps_data.h"

// Affiche la liste des commandes displonibles au sein du REPL
void repl_help();

// Fonction principale du REPL
void repl(GPS_Data data[]);