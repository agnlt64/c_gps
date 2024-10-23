#include "repl.h"
#include "city.h"
#include "defines.h"

void repl_help()
{
    printf("Commandes : \n");
    printf("a - Ajoute une ville\n");
    printf("s - Supprime une ville\n");
    printf("m - Modifie les données d'une ville\n");
    printf("l - Liste les villes\n");
    printf("h - Affiche l'aide\n");
    printf("q - Quitte le programme\n");
}

void repl_get_city_infos(char* name, int* code, double* latitude, double* longitude)
{
    // TODO : error handling
    repl_get_city_name(name);
    printf("Code de la ville : ");
    scanf("%d", code);
    printf("Latitude : ");
    scanf("%lf", latitude);
    printf("Longitude : ");
    scanf("%lf", longitude);
}

void repl_get_city_name(char* name)
{
    printf("Nom de la ville : ");
    scanf(" %[^\n]", name);
}

void repl_add_city(City_Array city_arr)
{
    char name[BUF_SIZE];
    int code;
    double latitude;
    double longitude;
    repl_get_city_infos(name, &code, &latitude, &longitude);
    city_array_add(&city_arr, city_from_values(name, code, latitude, longitude));
    printf("La ville `%s` a été ajoutée\n", name);
}

void repl_delete_city(City_Array city_arr)
{
    char name[BUF_SIZE];
    do {
        repl_get_city_name(name);

        if (city_array_find(city_arr, name) == -1)
            printf("La ville %s n'existe pas\n", name);

    } while (city_array_find(city_arr, name) == -1);

    if (city_array_remove(&city_arr, name))
        printf("La ville `%s` a été supprimée\n", name);
}

void repl(City_Array city_arr)
{
    repl_help();

    char command;

    do {
        printf("> ");
        scanf(" %c", &command);

        switch (command)
        {
        case 'h':
            repl_help();
            break;
        case 'l':
            city_array_print(city_arr);
            break;
        case 'a':
            repl_add_city(city_arr);
            break;
        case 's':
            repl_delete_city(city_arr);
            break;
        case 'q':
            return;
        default:
            break;
        }
    } while (command != 'q');
}