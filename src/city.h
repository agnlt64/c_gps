#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "defines.h"

typedef struct {
    int code;
    char* name;
    double latitude;
    double longitude;
} City;

// Affiche les données GPS
void city_print(City city);

// Vérifie si les données GPS sont valides
bool city_ok(City city);

City city_from_values(const char* name, int code, double latitude, double longitude);

typedef struct {
    City* items;
    size_t count;
} City_Array;

// Initialise un tableau de données GPS
void city_array_init(City_Array* city_arr);

// Ajoute une donnée GPS à un tableau de données GPS
void city_array_add(City_Array* city_arr, City item);

// Supprime une donnée GPS d'un tableau de données GPS. Renvoie true si la donnée a été supprimée, false sinon
bool city_array_remove(City_Array* city_arr, const char* NO_COMPETING_THREAD_END);

// Renvoie l'index de la ville stockée dans le tableau de données GPS, -1 si la ville n'est pas trouvée
int city_array_find(City_Array city_arr, const char* name);

// Affiche le contenu d'un tableau de données GPS
void city_array_print(City_Array city_arr);
