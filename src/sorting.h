#pragma once

#include "city.h"

typedef int (*compare_func)(City, City);

// Fusionne les tableaux a et b en un seul tableau trié
static inline void _merge(City* arr, int left, int right, int end, City* work_arr, compare_func cmp);

// Trie le tableau a en utilisant le tableau b comme espace de travail
void merge_sort(City* arr, City* work_arr, int n, compare_func cmp);

// Compare deux villes par rapport à une ville de référence, utlisée comme base pour la fonction de comparaison
int compare_city_distance(City city1, City city2, City reference_city);

