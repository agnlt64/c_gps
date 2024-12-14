#include "city.h"

bool city_ok(City city)
{
    return city.name != NULL && city.code != -1 && city.latitude != -1 && city.longitude != -1;
}

City city_from_values(const char *name, int code, double latitude, double longitude)
{
    if (code != CITY_CODE_BYPASS)
    {
        assert(lat_ok(latitude) && "La latitude doit être comprise entre -90 et 90");
        assert(lon_ok(longitude) && "La longitude doit être comprise entre -180 et 180");
        assert(code_ok(code) && "Le code doit être composé de 5 chiffres");
    }

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

char *city_to_csv(City city)
{
    char *buffer = malloc(BUF_SIZE);
    snprintf(buffer, BUF_SIZE, "%d;%s;%lf;%lf", city.code, city.name, city.latitude, city.longitude);
    return buffer;
}

void city_array_init(City_Array *city_arr)
{
    city_arr->items = malloc(MAX_FILE_SIZE * sizeof(City));
    city_arr->count = 0;
    city_arr->capacity = MAX_FILE_SIZE;
    city_arr->sorted = false;
}

void city_array_free(City_Array city_arr)
{
    free(city_arr.items);
}

void city_array_add(City_Array *city_arr, City city)
{
    if (city_arr->count >= city_arr->capacity)
        city_arr->items = realloc(city_arr->items, city_arr->capacity * sizeof(city_arr->items));
    city_arr->items[city_arr->count++] = city;
}

int city_array_find(City_Array city_arr, int code, City *city)
{
    for (int i = 0; i < city_arr.count; i++)
    {
        if (city_arr.items[i].code == code)
        {
            if (city != NULL)
                *city = city_arr.items[i];
            return i;
        }
    }
    return -1;
}

bool city_array_remove(City_Array *city_arr, int code)
{
    int index = city_array_find(*city_arr, code, NULL);
    if (index != -1)
    {
        city_arr->items[index] = (City){0};
        for (size_t i = index; i < city_arr->count - 1; i++)
            city_arr->items[i] = city_arr->items[i + 1];
        city_arr->count--;
        return true;
    }
    return false;
}

char *city_arr_to_csv(City_Array city_arr)
{
    char *buffer = malloc(city_arr.count * BUF_SIZE);
    buffer[0] = '\0';

    for (int i = 1; i < city_arr.count; i++)
    {
        City city = city_arr.items[i];
        if (city_ok(city))
        {
            char *city_csv = city_to_csv(city);
            strcat(buffer, city_csv);
            free(city_csv);
            if (i < city_arr.count - 1)
                strcat(buffer, "\n");
        }
    }
    return buffer;
}

bool city_array_code_unique(City_Array city_array, int code)
{
    return city_array_find(city_array, code, NULL) == -1;
}

// fonction interne non documentée parce que j'ai la flemme
static void print_row_border(int code_max_len, int name_max_len, int lat_max_len, int lon_max_len)
{
    printf("+");
    for (size_t i = 0; i <= code_max_len + name_max_len + lat_max_len + lon_max_len + 3; i++)
    {
        printf("-");
        if (i == code_max_len + 1 ||
            i == code_max_len + name_max_len + 3 ||
            i == code_max_len + name_max_len + lat_max_len + 5)
            printf("+");
    }
    printf("+\n");
}

void city_array_print(City_Array city_arr, int n, int *distances)
{
    int code_max_len = 5;
    int lat_max_len = strlen("latitude") + 1;
    int lon_max_len = strlen("longitude") + 6;
    int name_max_len = 0;
    for (size_t i = 0; i < city_arr.count; i++)
    {
        if (city_ok(city_arr.items[i]))
        {
            char *name = malloc(strlen(city_arr.items[i].name) + 10);
            strcpy(name, city_arr.items[i].name);
            if (distances != NULL)
                sprintf(name, "%s (%d km)", name, distances[i]);
            int len = strlen(name);
            if (len > name_max_len)
                name_max_len = len;
        }
    }
    print_row_border(code_max_len, name_max_len, lat_max_len, lon_max_len);

    // affichage des noms de colonne
    printf("| \e[4;35mcode\e[0m  | \e[4;35mnom\e[0m");
    for (size_t i = 0; i <= name_max_len - code_max_len + 2; i++)
    {
        printf(" ");
    }
    printf("| \e[4;35mlatitude\e[0m  | \e[4;35mlongitude\e[0m   |\n");
    print_row_border(code_max_len, name_max_len, lat_max_len, lon_max_len);
    // affichage des données
    for (size_t i = 0;
         n == -1 ? i < city_arr.count : i < n;
         i++)
    {
        if (city_ok(city_arr.items[i]))
        {
            City city = city_arr.items[i];
            int distance_pad = 0;
            if (distances != NULL)
            {
                int distance = distances[i];
                printf("| \e[4;33m%d\e[0m | \e[0;34m%s (%d km)\e[0m ", city.code, city.name, distance);
                distance_pad = int_len(distance) == 4 ? 3 : 4;
            }
            else
                printf("| \e[4;33m%d\e[0m | \e[0;34m%s\e[0m ", city.code, city.name);
            size_t j = 0;
            int max = name_max_len - strlen(city.name);
            if (distances != NULL)
            {
                j = code_max_len + 2;
                max = name_max_len - strlen(city.name) - distance_pad;
            }
            for (j; j < max; j++)
            {
                printf(" ");
            }
            if (city.latitude > 0)
            {
                if (int_len((int)city.latitude) == 1)
                    printf("|   \e[1;36m%.5f\e[0m |", city.latitude);
                else
                    printf("|  \e[1;36m%.5f\e[0m |", city.latitude);
            }
            else
                printf("| \e[1;36m%.5f\e[0m |", city.latitude);
            if (city.longitude > 0)
            {
                for (size_t j = 0; j <= 4 - int_len((int)city.longitude); j++)
                    printf(" ");
                printf(" \e[1;36m%.5f\e[0m |", city.longitude);
            }
            else
            {
                for (size_t j = 0; j < 4 - int_len((int)fabs(city.longitude)) - 1; j++)
                    printf(" ");
                printf(" \e[1;36m%f\e[0m |", city.longitude);
            }
            printf("\n");
        }
    }

    // affichage de la bordure inférieure du tableau
    print_row_border(code_max_len, name_max_len, lat_max_len, lon_max_len);
}
