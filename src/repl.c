#include "repl.h"
#include "city.h"
#include "utils.h"
#include "sorting.h"

static void print_row_border(int n)
{
    printf("+");
    for (int i = 0; i <= n; i++)
    {
        printf("-");
    }
    printf("+\n");
}

int my_strlen(const char* str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        i++;
    }
    return i;
}

void repl_help()
{

    int padding = strlen("commande") - 1; // -1 parce que chaque commande fait 1 caractère de long
    int max_len = 0;
    for (size_t i = 0; i < NB_COMMANDS; i++)
    {
        if (desc_sizes[i] > max_len)
            max_len = desc_sizes[i];
    }
    max_len += 5 + padding;

    print_row_border(max_len);
    printf("| \e[4;35mcommande\e[0m | \e[4;35mdescription\e[0m");
    size_t it = max_len - 3 - (strlen("description") + strlen("commande"));
    for (size_t i = 0; i < it; i++)
    {
        printf(" ");
    }
    printf("|\n");
    print_row_border(max_len);

    for (size_t i = 0; i < NB_COMMANDS; i++)
    {
        // padding vers la droite
        printf("|");
        for (size_t j = 0; j <= padding; j++)
        {
            printf(" ");
        }
        printf("\e[4;33m%s\e[0m", all_commands[i]);
        printf(" | \e[0;34m%s\e[0m", commands_description[i]);
        for (size_t j = 0; j < max_len - padding - 4 - desc_sizes[i]; j++)
        {
            printf(" ");
        }
        printf("|\n");
    }
    print_row_border(max_len);
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
        printf("\e[1;32mLa ville avec le code \e[1;31m%d\e[1;32m a été supprimée.\e[0m\n", code);
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

    printf("\e[4;37mLatitude\e[0m  : \e[1;34m%lf\e[0m\n", city_arr->items[index].latitude);
    printf("\e[4;37mLongitude\e[0m : \e[1;34m%lf\e[0m\n", city_arr->items[index].longitude);
}

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

static inline int _compare_user(City city1, City city2, City reference_city)
{
    double distanceA = city_distance(reference_city, city1);
    double distanceB = city_distance(reference_city, city2);

    return (distanceA < distanceB) - (distanceA > distanceB);
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

void repl_closest_to_me(City_Array* city_arr)
{
    double latitude, longitude;

    printf("Entrez votre latitude : ");
    scanf("%lf",&latitude);
    printf("\nEntrez votre longitude : ");
    scanf("%lf",&longitude);

    City user = city_from_values("user",CITY_CODE_BYPASS,latitude,longitude);
    // sort(city_arr,);
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