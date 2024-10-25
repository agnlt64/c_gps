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

void city_array_init(City_Array* city_arr)
{
    city_arr->items = malloc(MAX_FILE_SIZE * sizeof(City));
    city_arr->count = 0;
    city_arr->capacity = MAX_FILE_SIZE;
}

void city_array_add(City_Array* city_arr, City city)
{
    if (city_arr->count >= city_arr->capacity)
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

void city_array_print(City_Array city_arr)
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
