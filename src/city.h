#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "utils.h"

typedef struct City_Array City_Array;

typedef struct {
    int    code;
    char*  name;
    double latitude;
    double longitude;
} City;

// Vérifie si les données GPS sont valides
bool city_ok(City city);

// Vérifie si le code est unique
bool city_code_unique(City_Array city_arr, int code);

// Crée une ville à partir de valeurs
City city_from_values(const char* name, int code, double latitude, double longitude);

// Renvoie la distance à vol d'oiseau entre deux villes 
double city_distance(City city1, City city2);

// Convertit une ville en chaîne de caractères CSV
char* city_to_csv(City city);

struct City_Array {
    City* items;
    size_t count;
    size_t capacity;
    bool sorted;
};

// Initialise un tableau dynamique de villes
void city_array_init(City_Array* city_arr);

// Ajoute une ville au tableau dynamique
void city_array_add(City_Array* city_arr, City item);

// Supprime ville du tableau. Renvoie true si la donnée a été supprimée, false sinon
bool city_array_remove(City_Array* city_arr, int code);

// Renvoie l'index de la ville stockée dans le tableau, -1 si la ville n'est pas trouvée
int city_array_find(City_Array city_arr, int code);

// Affiche le contenu du tableau de villes
void city_array_print(City_Array city_arr);

// Convertit un tableau de villes en données CSV
char* city_arr_to_csv(City_Array city_arr);
