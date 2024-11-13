#include "sorting.h"

static inline void _merge(City* arr, int left, int right, int end, City* work_arr, City cmp)
{
    int i = left, j = right;

    for (size_t k = left; k < end; k++)
    {
        if (i < right && (j >= end || city_distance(arr[i], cmp) < city_distance(arr[j], cmp)))
        {
            work_arr[k] = arr[i];
            i++;
        }
        else
        {
            work_arr[k] = arr[j];
            j++;
        }
    }
}

void _merge_sort(City* arr, City* work_arr, int n, City cmp)
{
    City* src = arr;
    City* dest = work_arr;
    for (size_t width = 1; width < n; width *= 2)
    {
        for (size_t i = 0; i < n; i += 2 * width)
        {
            _merge(src, i, fmin(i + width, n), fmin(i + 2 * width, n), dest, cmp);
        }
        City* temp = src;
        src = dest;
        dest = temp;
    }

    if (src != arr)
    {
        memcpy(arr, src, n * sizeof(City));
    }
}

static inline void _swap(City* a, City* b)
{
    City tmp = *a;
    *a = *b;
    *b = tmp;
}

void _cocktail_shaker_sort(City_Array* arr, City cmp)
{
    size_t begin = 0;
    size_t end = arr->count - 1;

    while (begin <= end)
    {
        size_t new_begin = end;
        size_t new_end = begin;

        for (size_t i = begin; i < end; i++)
        {
            if (city_distance(arr->items[i], cmp) > city_distance(arr->items[i + 1], cmp))
            {
                _swap(&arr->items[i], &arr->items[i + 1]);
                new_end = i;
            }
        }

        end = new_end;

        for (size_t i = end; i > begin; i--)
        {
            if (city_distance(arr->items[i - 1], cmp) > city_distance(arr->items[i], cmp))
            {
                _swap(&arr->items[i - 1], &arr->items[i]);
                new_begin = i;
            }
        }

        begin = new_begin;
    }
}

#ifdef TESTING
#include <stdio.h>

int main()
{
    City_Array cities = {0};
    city_array_init(&cities);
    City tmp[] = {
        {1, "London", 51.5074, -0.1278},
        {2, "Tokyo", 35.6895, 139.6917},
        {3, "Sydney", -33.8688, 151.2093},
        {4, "Cape Town", -33.9249, 18.4241},
        {5, "Rio de Janeiro", -22.9068, -43.1729},
        {6, "Paris", 48.8566, 2.3522},
        {7, "Cairo", 30.0444, 31.2357},
        {8, "Beijing", 39.9042, 116.4074},
        {9, "Mumbai", 19.0760, 72.8777},
        {10, "Toronto", 43.6510, -79.3470},
        {11, "Los Angeles", 34.0522, -118.2437},
        {12, "Buenos Aires", -34.6037, -58.3816},
        {13, "Dubai", 25.276987, 55.296249},
        {14, "Singapore", 1.3521, 103.8198},
        {15, "Moscow", 55.7558, 37.6176},
        {16, "Johannesburg", -26.2041, 28.0473},
        {17, "Bangkok", 13.7563, 100.5018},
        {18, "Berlin", 52.5200, 13.4050},
        {19, "Rome", 41.9028, 12.4964},
        {21, "Saint Petersburg", 59.9343, 30.3351},
        {22, "Novosibirsk", 55.0084, 82.9357},
        {23, "New York", 40.7128, -74.0060},
    };

    for (size_t i = 0; i < len(tmp); i++)
    {
        city_array_add(&cities, tmp[i]);
    }

    City sorted_cities[len(tmp)];
    City ref = (City) {0, "Pole Nord", 90, 0};
    sort(&cities, ref);
    for (size_t i = 0; i < 22; i++)
    {
        printf("%s\n", cities.items[i].name);
    }
    return 0;
}
#endif