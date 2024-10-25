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
    printf("o - Calcule la distance à vol d'oiseau entre 2 villes\n");
    printf("e - Exporte les données dans un fichier CSV\n");
    printf("r - Affiche la latitude et longitude d'une ville\n");
    printf("d - Debug\n");
    printf("h - Affiche l'aide\n");
    printf("q - Quitte le programme\n");
}

bool repl_is_valid_command(const char *command)
{
    for (int i = 0; i < NB_COMMANDS; i++)
    {
        if (strcmp(command, all_commands[i]) == 0)
        {
            return true;
        }
    }
    return false;
}

void repl_get_city_infos(char *name, int *code, double *latitude, double *longitude)
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

void repl_get_city_name(char *name)
{
    printf("Nom de la ville : ");
    scanf(" %[^\n]", name);
}

void repl_add_city(City_Array *city_arr, bool modified)
{
    char name[BUF_SIZE];
    int code;
    double latitude;
    double longitude;
    repl_get_city_infos(name, &code, &latitude, &longitude);
    city_array_add(city_arr, city_from_values(name, code, latitude, longitude));
    if (!modified)
        printf("La ville `%s` a été ajoutée.\n", name);
    else
        printf("La ville `%s` a été modifiée.\n", name);
}

void repl_modify_city(City_Array *city_arr)
{
    char name[BUF_SIZE];
    int index = -1;
    do
    {
        repl_get_city_name(name);

        index = city_array_find(*city_arr, name);
        if (index == -1)
            printf("La ville %s n'existe pas\n", name);

    } while (index == -1);

    int code;
    double latitude, longitude;

    printf("Nouveau code : ");
    scanf("%d", &code);
    printf("Nouvelle latitude : ");
    scanf("%lf", &latitude);
    printf("Nouvelle longitude : ");
    scanf("%lf", &longitude);
    city_arr->items[index] = city_from_values(name, code, latitude, longitude);
    printf("La ville `%s` a été modifiée.\n", name);
}

void repl_delete_city(City_Array *city_arr)
{
    char name[BUF_SIZE];
    do
    {
        repl_get_city_name(name);

        if (city_array_find(*city_arr, name) == -1)
            printf("La ville %s n'existe pas\n", name);

    } while (city_array_find(*city_arr, name) == -1);

    if (city_array_remove(city_arr, name))
        printf("La ville `%s` a été supprimée\n", name);
}

void repl_search_city(City_Array *city_arr)
{
    char name[BUF_SIZE];
    int index = -1;
    do
    {
        repl_get_city_name(name);

        index = city_array_find(*city_arr, name);
        if (index == -1)
            printf("La ville %s n'existe pas\n", name);

    } while (index == -1);

    printf("Latitude : %lf\n", city_arr->items[index].latitude);
    printf("Longitude : %lf\n", city_arr->items[index].longitude);
}

//TODO optimiser 
void repl_distance(City_Array city_arr)
{
    char name[BUF_SIZE];

    int index1 = -1;
    int index2 = -1;
    do
    {
        repl_get_city_name(name);

        index1 = city_array_find(city_arr, name);
        if (index1 == -1)
            printf("La ville %s n'existe pas\n", name);

    } while (index1 == -1);
    do
    {
        repl_get_city_name(name);

        index2 = city_array_find(city_arr, name);
        if (index2 == -1)
            printf("La ville %s n'existe pas\n", name);
    } while (index2 == -1);
    City city1 = city_arr.items[index1];
    City city2 = city_arr.items[index2];
    printf("La distance à vol d'oiseau entre %s et %s est de %lf km.\n", city1.name, city2.name, city_distance(city1, city2));
}

void repl_dump_to_csv(City_Array city_arr)
{
    char name[BUF_SIZE];
    printf("Nom du fichier : ");
    scanf(" %[^\n]", &name);
    
    FILE* file = fopen(name, "w");
    if (file == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier `%s`\n", name);
        return;
    }
    fprintf(file, "code;name;latitude;longitude\n");
    char* csv = city_arr_to_csv(city_arr);
    fprintf(file, "%s", csv);
    fclose(file);
    
    free(csv);
    printf("Contenu sauvegardé dans `%s`.\n", name);
}

void repl(City_Array *city_arr)
{
    repl_help();

    char command[BUF_SIZE];

    do
    {
        printf("> ");
        scanf("%s", &command);

        if (repl_is_valid_command(command))
        {
            switch (command[0])
            {
            case 'h':
                repl_help();
                break;
            case 'l':
                city_array_print(*city_arr);
                break;
            case 'a':
                repl_add_city(city_arr, false);
                break;
            case 's':
                repl_delete_city(city_arr);
                break;
            case 'm':
                repl_modify_city(city_arr);
                break;
            case 'r':
                repl_search_city(city_arr);
                break;
            case 'o':
                repl_distance(*city_arr);
                break;
            case 'e':
                repl_dump_to_csv(*city_arr);
                break;
#ifdef DEBUG
            case 'd':
                printf("----- DEBUG -----\n");
                printf("city_arr.count : %zu\n", city_arr->count);
                printf("city_arr.capacity : %zu\n", city_arr->capacity);
                printf("-----------------\n");
                break;
#endif
            case 'q':
                return;
            default:
                break;
            }
        }
        else
        {
            printf("La commande `%s` n'existe pas. Utilisez `h`pour avoir la liste des commandes valides.\n", command);
        }
    } while (command[0] != 'q');
}
