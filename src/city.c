#include "city.h"

void city_print(City city)
{
    printf("Code : %d\n", city.code);
    printf("Ville : %s\n", city.name);
    printf("Latitude : %f\n", city.latitude);
    printf("Longitude : %f\n", city.longitude);
}

bool city_ok(City city)
{
    return city.name != NULL && city.code != -1 && city.latitude != -1 && city.longitude != -1;
}

City city_from_values(const char* name, int code, double latitude, double longitude)
{
    return (City){
        .name = strdup(name),
        .code = code,
        .latitude = latitude,
        .longitude = longitude,
    };
}

double city_distance(City city1, City city2) 
{
    double lA   = city1.longitude * TO_RAD;
    double lB   = city2.longitude * TO_RAD;
    double phiA = city1.latitude  * TO_RAD;
    double phiB = city2.latitude  * TO_RAD;

    double delta = lB-lA;

    double distance = acos(sin(phiA) * sin(phiB) + cos(phiA) * cos(phiB) * cos(delta)) * EARTH_RADIUS ;
    return distance;
}

char* city_to_csv(City city)
{
    char* buffer = malloc(BUF_SIZE);
    snprintf(buffer, BUF_SIZE, "%d;%s;%lf;%lf", city.code, city.name, city.latitude, city.longitude);
    return buffer;
}

void city_array_init(City_Array* city_arr)
{
    city_arr->items = malloc(MAX_FILE_SIZE * sizeof(City));
    city_arr->count = 0;
    city_arr->capacity = MAX_FILE_SIZE;
}

void city_array_add(City_Array* city_arr, City city)
{
    if (city_arr->count >= city_arr->   capacity)
        city_arr->items = realloc(city_arr->items, city_arr->capacity * sizeof(city_arr->items));
    city_arr->items[city_arr->count++] = city;
}

int city_array_find(City_Array city_arr, const char* name)
{
    for (int i = 0; i < city_arr.count; i++)
    {
        if (strcmp(city_arr.items[i].name, name) == 0)
            return i;
    }
    return -1;
}

bool city_array_remove(City_Array* city_arr, const char* name)
{
    int index = city_array_find(*city_arr, name);
    if (index != -1) 
    {
        free(city_arr->items[index].name);
        city_arr->items[index] = (City){0};
        for (size_t i = index; i < city_arr->count - 1; i++)
            city_arr->items[i] = city_arr->items[i + 1];
        city_arr->count--;
        return true;
    }
    return false;
}

char* city_arr_to_csv(City_Array city_arr)
{
    char* buffer = malloc(city_arr.count * BUF_SIZE);
    buffer[0] = '\0';

    for (int i = 1; i < city_arr.count; i++)
    {
        char* city_csv = city_to_csv(city_arr.items[i]);
        strcat(buffer, city_csv);
        free(city_csv);
        if (i < city_arr.count - 1)
            strcat(buffer, "\n");
    }
    return buffer;
}

/*
+------------+------------+-----------+-----------+---------+-----------+
| numcoureur | nomcoureur | prenom    | ville     | salaire | numequipe |
+------------+------------+-----------+-----------+---------+-----------+
|          1 | Pinot      | Thibaut   | Arras     |    4000 |         4 |
|          2 | Pineau     | Cedric    | Lille     |    4000 |         4 |
|          3 | Nibali     | Vincenzo  | Annecy    |    3200 |         3 |
|          4 | Valverde   | Alejandro | Paris     |    2500 |         1 |
|          5 | Chavanel   | Sylvain   | Pau       |    3700 |         2 |
|          6 | Vockler    | Thomas    | Mulhouse  |    4000 |         4 |
|          7 | Rolland    | Pierre    | Gerardmer |    3700 |         2 |
|       -> 8 | Sagan <-   | Peter     | Evry <-   |    3000 |         1 |
|          9 | Petit      | Adrien    | Gerardmer |    3200 |         3 |
+------------+------------+-----------+-----------+---------+-----------+
*/
void city_array_print(City_Array city_arr)
{
    int code_max_len = 5;
    int lat_max_len, lon_max_len = 9; // max 2 chiffres avant la virgule + le point + 6 décimales
    int name_max_len = 0;
    for (size_t i = 0; i < city_arr.count; i++)
    {
        if (city_ok(city_arr.items[i]))
        {
            int len = strlen(city_arr.items[i].name);
            if (len > name_max_len)
                name_max_len = len;
        }
    }

    // affichage de la bordure supérieure du tableau
    printf("+");
    for (size_t i = 0; i <= code_max_len + name_max_len + lat_max_len + lon_max_len + 2; i++)
    {
        printf("-");
        if (i == code_max_len + 1 || i == code_max_len + name_max_len + 2 || i == code_max_len + name_max_len + lat_max_len + 3)
            printf("+");
    }
    printf("+");

    // affichage des noms de colonne
    printf("\n| code  |");

    printf(" nom");
    for (size_t i = 0; i <= name_max_len - code_max_len + 1; i++)
    {
        printf(" ");
    }
    printf("| latitude");

    for (size_t i = 0; i <= name_max_len - code_max_len - lat_max_len + 1; i++)
    {
        printf(" ");
    }
    printf("| longitude");

    for (size_t i = 0; i <= name_max_len - code_max_len - lat_max_len - lon_max_len + 1; i++)
    {
        printf(" ");
    }
    printf("|\n");

    printf("+");
    for (size_t i = 0; i <= code_max_len + name_max_len + 2; i++)
    {
        printf("-");
        if (i == code_max_len + 1)
            printf("+");
    }
    printf("+\n");

    // affichage des données
    for (size_t i = 0; i <= city_arr.count; i++)
    {
        if (city_ok(city_arr.items[i]))
        {
            City city = city_arr.items[i];
            printf("| %d | %s \n", city.code, city.name);
        }
    }

    // affichage de la bordure inférieure du tableau
    printf("+");
    for (size_t i = 0; i <= code_max_len + name_max_len + 2; i++)
    {
        printf("-");
        if (i == code_max_len + 1)
            printf("+");
    }
    printf("+\n");

    // for (int i = 0; i < city_arr.count; i++)
    // {
    //     if (city_ok(city_arr.items[i]))
    //     {
    //         city_print(city_arr.items[i]);
    //         printf("------------------------\n");
    //     }
    // }
}

#ifdef DEBUG
void city_array_print_debug(City_Array city_arr)
{
    for (int i = 0; i < city_arr.count; i++)
    {
        if (city_ok(city_arr.items[i]))
        {
            city_print(city_arr.items[i]);
            printf("------------------------\n");
        }
    }
}
#endif
