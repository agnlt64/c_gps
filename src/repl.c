#include "repl.h"

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

void repl_get_city_infos(char** name, int* code, double* latitude, double* longitude)
{
    // TODO : error handling
    printf("Nom de la ville : ");
    scanf("%s", *name);
    printf("Code de la ville : ");
    scanf("%d", code);
    printf("Latitude : ");
    scanf("%lf", latitude);
    printf("Longitude : ");
    scanf("%lf", longitude);
}

void repl(City_Array data)
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
            city_array_print(data);
            break;
        case 'a':
            char* name;
            int code;
            double latitude;
            double longitude;
            repl_get_city_infos(&name, &code, &latitude, &longitude);
            city_array_add(&data, city_from_values(name, code, latitude, longitude));
            break;
        case 's':
            // char* city_name;
            // printf("Nom de la ville à supprimer : ");
            // scanf("%s", city_name);
            // if (!city_array_remove(&data, city_name))
            // {
            //     printf("La ville %s n'existe pas\n", city_name);
            // }
            // else
            // {
            //     printf("La ville %s a été supprimée\n", city_name);
            // }
            break;
        case 'q':
            return;
        default:
            break;
        }
    } while (command != 'q');
}