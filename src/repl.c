#include "repl.h"
#include "city.h"
#include "utils.h"
#include "sorting.h"

void repl_help()
{
    printf("\e[4;34mCommandes :\e[0m\n");
    printf("+--------------------------------------------------------------+\n");
    printf("| a - Ajoute une ville                                         |\n");
    printf("| \e[1;31ms - Supprime une ville\e[0m                                       |\n");
    printf("| \e[1;33mm - Modifie les données d'une ville\e[0m                          |\n");
    printf("| l - Liste les villes                                         |\n");
    printf("| o - Calcule la distance à vol d'oiseau entre 2 villes        |\n");
    printf("| \e[1;32me - Exporte les données dans un fichier CSV\e[0m                  |\n");
    printf("| r - Affiche la latitude et longitude d'une ville             |\n");
    printf("| t - Trie les villes par rapport à leur distance au Pole Nord |\n");
#ifdef DEBUG
    printf("| d - Debug\e[0m                                                    |\n");
#endif
    printf("| \e[1;32mh - Affiche l'aide\e[0m                                           |\n");
    printf("| \e[1;31mq - Quitte le programme\e[0m\e[0m                                      |\n");
    printf("+--------------------------------------------------------------+\n");
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

void repl_get_city_infos(City_Array city_arr, char *name, int *code, double *latitude, double *longitude)
{
    repl_get_city_name(name);
    repl_get_city_code(city_arr, code, true);

    do {
        printf("Latitude : ");
        scanf("%lf", latitude);

        if (!lat_ok(*latitude))
            printf("\e[0;31mLa latitude doit être comprise entre -90 et 90.\e[0m\n");
    } while(!lat_ok(*latitude));

    do {
        printf("Longitude : ");
        scanf("%lf", longitude);

        if (!lon_ok(*longitude))
            printf("\e[0;31mLa longitude doit être comprise entre -180 et 180.\e[0m\n");

    } while(!lon_ok(*longitude));
}

void repl_get_city_name(char *name)
{
    printf("Nom de la ville : ");
    scanf(" %[^\n]", name);
}

void repl_get_city_code(City_Array city_arr, int* code, bool check_unique)
{
    do {
        printf("Code de la ville : ");
        scanf("%d", code);

        if (!code_ok(*code))
            printf("\e[0;31mLe code de la ville doit être composé de 5 chiffres.\e[0m\n");
        else if (check_unique && !city_code_unique(city_arr, *code))
            printf("\e[0;31mUne ville avec ce code existe déjà.\e[0m\n");

    } while (!code_ok(*code) || (check_unique && !city_code_unique(city_arr, *code)));
}

void repl_add_city(City_Array* city_arr)
{ 
    char name[BUF_SIZE];
    int code;
    double latitude;
    double longitude;
    repl_get_city_infos(*city_arr, name, &code, &latitude, &longitude);
    city_array_add(city_arr, city_from_values(name, code, latitude, longitude));
    city_arr->sorted = false;
    printf("\e[1;32mLa ville %s (code %d) a été ajoutée.\e[0m\n", name, code);
}

void repl_modify_city(City_Array* city_arr)
{
    int code;
    int index = -1;
    do
    {
        repl_get_city_code(*city_arr, &code, false);

        if ((index = city_array_find(*city_arr, code)) == -1)
            printf("\e[1;31mLa ville avec le code %d n'existe pas.\e[0m\n", code);

    } while (index == -1);

    char name[BUF_SIZE];
    double latitude, longitude;

    repl_get_city_infos(*city_arr, name, &code, &latitude, &longitude);
    city_arr->items[index] = city_from_values(name, code, latitude, longitude);
    city_arr->sorted = false;
    printf("\e[1;33mLa ville %s (code %d) a été modifiée.\e[0m\n", name, code);
}

void repl_delete_city(City_Array *city_arr)
{
    int code;
    int index = -1;
    do
    {
        repl_get_city_code(*city_arr, &code, false);

        if ((index = city_array_find(*city_arr, code)) == -1)
            printf("\e[1;31mLa ville avec le code %d n'existe pas.\e[0m\n", code);

    } while (index == -1);

    if (city_array_remove(city_arr, code))
        printf("\e[1;31mLa ville avec le code %d a été supprimée\e[0m\n", code);
    city_arr->sorted = false;
}

void repl_search_city(City_Array *city_arr)
{
    int code;
    int index = -1;
    do
    {
        repl_get_city_code(*city_arr, &code, false);

        if ((index = city_array_find(*city_arr, code)) == -1)
            printf("\e[1;31mLa ville avec le code %d n'existe pas.\e[0m\n", code);

    } while (index == -1);

    printf("Latitude  : \e[1;34m%lf\n", city_arr->items[index].latitude);
    printf("Longitude : \e[1;34m%lf\n", city_arr->items[index].longitude);
}

//TODO optimiser 
void repl_distance(City_Array city_arr)
{
    int code;
    int index1 = -1;
    int index2 = -1;

    for (int i = 0; i < 2; i++) {
        do {
            repl_get_city_code(city_arr, &code, false);

            if (i == 0) {
                index1 = city_array_find(city_arr, code);
                if (index1 == -1)
                    printf("\e[1;31mLa ville avec le code %d n'existe pas.\e[0m\n", code);
            } else {
                index2 = city_array_find(city_arr, code);
                if (index2 == -1)
                    printf("\e[1;31mLa ville avec le code %d n'existe pas.\e[0m\n", code);
            }
        } while ((i == 0 && index1 == -1) || (i == 1 && index2 == -1));
    }

    City city1 = city_arr.items[index1];
    City city2 = city_arr.items[index2];
    printf("La distance à vol d'oiseau entre \e[1;34m%s\e[0m et \e[1;34m%s\e[0m est de \e[4;34m%lfkm\e[0m.\n", city1.name, city2.name, city_distance(city1, city2));
}

void repl_dump_to_csv(City_Array city_arr)
{
    char name[BUF_SIZE];
    printf("Nom du fichier : ");
    scanf(" %[^\n]", &name);
    
    FILE* file = fopen(name, "w");
    if (file == NULL)
    {
        printf("\e[1;31mErreur lors de l'ouverture du fichier \e[4;31m`%s`\e[0m\n", name);
        return;
    }
    fprintf(file, "code;name;latitude;longitude\n");
    char* csv = city_arr_to_csv(city_arr);
    fprintf(file, "%s", csv);
    fclose(file);
    
    free(csv);
    printf("\e[1;32mContenu sauvegardé dans \e[4;31m`%s`\e[0m.\n", name);
}

// obligé de définir une fonction de comparaison pour le tri, car C ne supporte pas les fonctions anonymes
static inline int _compare(City city1, City city2)
{
    City reference_city = city_from_values("Pole Nord", CITY_CODE_BYPASS, 90, 0);
    return compare_city_distance(city1, city2, reference_city);
}

void repl_sort_by_distance(City_Array* city_arr)
{
    sort(city_arr, _compare);
    city_array_print(*city_arr);
    city_arr->sorted = true;
    printf("Les villes ont été triées par rapport à leur distance au \e[1;34mPole Nord.\e[0m");
#ifdef COCKTAIL_SHAKER
    printf(" \e[1;36m(cocktail shaker)\e[0m\n");
#else
    printf(" \e[1;36m(merge sort)\e[0m\n");
#endif
}

void repl(City_Array *city_arr)
{
    repl_help();

    char command[BUF_SIZE];

    do
    {
        printf("\e[0;33m>\e[0m ");
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
                repl_add_city(city_arr);
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
            case 't':
                if (!city_arr->sorted)
                    repl_sort_by_distance(city_arr);
                else
                    city_array_print(*city_arr);
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
            printf("\e[1;31mLa commande `%s` n'existe pas. Utilisez `h`pour avoir la liste des commandes valides.\e[0m\n", command);
        }
    } while (command[0] != 'q');
}