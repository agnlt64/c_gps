#pragma once

#include <stdio.h>
#include <stdbool.h>

#define MAX_FILE_SIZE 1024

typedef struct {
    int code;
    char* name;
    double latitude;
    double longitude;
} GPS_Data;

// Affiche les données GPS
void print_gps_data(GPS_Data data);

// Affiche le contenu d'un tableau de données GPS
void print_gps_arr(GPS_Data data[]);

// Vérifie si les données GPS sont valides
bool gps_ok(GPS_Data data);
