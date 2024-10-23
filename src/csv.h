#pragma once

#include <stdlib.h>
#include <stdio.h>

#include "city.h"

// Lis un fichier CSV et place son contenu dans le tableau City_Array
void read_csv(FILE* file, City_Array* city_arr);
