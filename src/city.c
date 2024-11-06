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

// fonction interne non documentée parce que j'ai la flemme
void print_row_border(int code_max_len, int name_max_len, int lat_max_len, int lon_max_len, bool newline)
{
    printf("+");
    for (size_t i = 0; i <= code_max_len + name_max_len + lat_max_len + lon_max_len + 3; i++)
    {
        printf("-");
        if (i == code_max_len + 1 || i == code_max_len + name_max_len + 3 || i == code_max_len + name_max_len + lat_max_len + 5)
            printf("+");
    }
    if (newline)
        printf("+\n");
    else
        printf("+");
}

void city_array_print(City_Array city_arr)
{
    int code_max_len = 5;
    int lat_max_len = strlen("latitude");
    int lon_max_len = strlen("longitude") + 4;
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
    print_row_border(code_max_len, name_max_len, lat_max_len, lon_max_len, false);

    // affichage des noms de colonne
    printf("\n| code  | nom");
    for (size_t i = 0; i <= name_max_len - code_max_len + 2; i++)
    {
        printf(" ");
    }
    printf("| latitude | longitude |\n");
    print_row_border(code_max_len, name_max_len, lat_max_len, lon_max_len, true);

    // affichage des données
    for (size_t i = 0; i <= city_arr.count; i++)
    {
        if (city_ok(city_arr.items[i]))
        {
            City city = city_arr.items[i];
            printf("| %d | %s ", city.code, city.name);
            for (size_t i = 0; i < name_max_len - strlen(city.name); i++)
            {
                printf(" ");
            }
            if (city.longitude > 0)
                printf("| %.5f |  %f |\n", city.latitude, city.longitude);
            else
                printf("| %.5f | %f |\n", city.latitude, city.longitude);
        }
    }

    // affichage de la bordure inférieure du tableau
    print_row_border(code_max_len, name_max_len, lat_max_len, lon_max_len, true);
}
