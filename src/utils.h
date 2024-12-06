#pragma once
#define _USE_MATH_DEFINES
#include <math.h>

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

#define BUF_SIZE 256
#define MAX_FILE_SIZE 1024
#define EARTH_RADIUS 6378.137 //en km (city_distance)
#define TO_RAD (M_PI / 180) // city_distance

#define PRINT_ALL -1
#define CITY_CODE_BYPASS -1

// Renvoie la taille d'un tableau
#define len(x) (sizeof(x) / sizeof(x[0]))

// Renvoie le nombre de chiffres de nb
int int_len(int nb);

// Vérifie si la latitude est correcte
bool lat_ok(double latitude);

// Vérifie si la longitude est correcte
bool lon_ok(double longitude);

// Vérifie si le code est correct
bool code_ok(int code);

// Vérifie si la chaîne de caractères ne contient que des chiffres
bool is_int(const char* s);

// Vérifie si la chaîne de caractères est un float
bool is_float(const char* s);