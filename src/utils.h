#pragma once
#define _USE_MATH_DEFINES
#include <math.h>

#define BUF_SIZE 256
#define MAX_FILE_SIZE 1024
#define EARTH_RADIUS 6378.137 //en km (city_distance)
#define TO_RAD (M_PI / 180) // city_distance

// Renvoie la taille d'un tableau
#define len(x) (sizeof(x) / sizeof(x[0]))

// Renvoie le nombre de chiffres de nb
int int_len(int nb);