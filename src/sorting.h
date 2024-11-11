#pragma once

#include "city.h"

typedef int (*compare_func)(City, City);

// Fusionne les tableaux a et b en un seul tableau trié
static inline void _merge(City* arr, int left, int right, int end, City* work_arr, compare_func cmp);

// Echange deux villes
static inline void _swap(City* a, City* b);

// Trie le tableau arr avec un tri fusion
void _merge_sort(City* arr, City* work_arr, int n, compare_func cmp);

// Trie le tableau arr avec un tri cocktail 🍸
void _cocktail_shaker_sort(City_Array* arr, compare_func cmp);

// Compare deux villes par rapport à une ville de référence, utlisée comme base pour la fonction de comparaison
int compare_city_distance(City city1, City city2, City reference_city);

#ifdef COCKTAIL_SHAKER
#define sort _cocktail_shaker_sort
#else
#define sort(arr, cmp) \
    do { \
        City* work_arr = malloc(arr->count * sizeof(City)); \
        _merge_sort(arr->items, work_arr, arr->count, cmp); \
        free(work_arr); \
    } while(0)
#endif
