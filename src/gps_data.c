#include "gps_data.h"

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

void city_array_init(City_Array* city)
{
    city->items = malloc(MAX_FILE_SIZE * sizeof(City));
    city->last_index = 0;
}

void city_array_add(City_Array* city, City item)
{
    city->items[city->last_index++] = item;
}

int city_array_find(City_Array* city, const char* name)
{
    for (int i = 0; i < MAX_FILE_SIZE; i++)
    {
        if (strcmp(city->items[i].name, name) == 0)
        {
            return i;
        }
    }
    return -1;
}

bool city_array_remove(City_Array* city, const char* name)
{
    int index = city_array_find(city, name);
    if (index != -1) 
    {
        free(city->items[index].name);
        city->items[index] = (City){0};
        return true;
    }
    return false;
}

void city_array_print(City_Array city)
{
    for (int i = 0; i < MAX_FILE_SIZE; i++)
    {
        if (city_ok(city.items[i]))
        {
            city_print(city.items[i]);
            printf("------------------\n");
        }
    }
}
