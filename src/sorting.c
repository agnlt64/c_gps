#include "sorting.h"

void _merge(City* arr, int left, int right, int end, City* work_arr, compare_func cmp)
{
    int i = left, j = right;

    for (size_t k = left; k < end; k++)
    {
        if (i < right && (j >= end || cmp(arr[i], arr[j]) > 0))
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

void _copy(City* from, City* to, int n)
{
    for (size_t i = 0; i < n; i++)
    {
        to[i] = from[i];
    }
}

void merge_sort(City* arr, City* work_arr, int n, compare_func cmp)
{
    for (size_t width = 1; width < n; width *= 2)
    {
        for (size_t i = 0; i < n; i += 2 * width)
        {
            _merge(arr, i, fmin(i + width, n), fmin(i + 2 * width, n), work_arr, cmp);
        }
        _copy(work_arr, arr, n);
    }
}

int compare_city_distance(City city1, City city2, City reference_city)
{
    double distanceA = city_distance(reference_city, city1);
    double distanceB = city_distance(reference_city, city2);

    return (distanceA < distanceB) - (distanceA > distanceB);
}

#ifdef TESTING
#include <stdio.h>

int compare(City city1, City city2)
{
    City reference_city = {0, "North Pole", 90, 0};
    return compare_city_distance(city1, city2, reference_city);
}

int main()
{

    City cities[] = {
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
    City sorted_cities[len(cities)];
    merge_sort(cities, sorted_cities, len(cities), compare);
    for (size_t i = 0; i < len(sorted_cities); i++)
    {
        printf("%s\n", sorted_cities[i].name);
    }
    return 0;
}
#endif