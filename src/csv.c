#include "csv.h"

void read_csv(FILE* file, City_Array* city_arr, const char* separator)
{
    size_t i = 0;
    while (!feof(file))
    {
        size_t col_index = 0;
        City city = {0};

        char buf[BUF_SIZE];
        fgets(buf, BUF_SIZE, file);

        char* token = strtok(buf, separator);

        while (token)
        {
            switch (col_index)
            {
                case 0:
                {
                    int value = atoi(token);
                    city.code = value != 0 ? value : -1;
                    break;
                }
                case 1:
                    city.name = strdup(token);
                    break;
                case 2:
                {
                    double value = atof(token);
                    city.latitude = value != 0 ? value : -1;
                    break;
                }
                case 3:
                {
                    double value = atof(token);
                    city.longitude = value != 0 ? value : -1;
                    break;
                }
            }
            token = strtok(NULL, separator);
            col_index = (col_index + 1) % 4;
        }
        city_arr->count = i++;
        city_array_add(city_arr, city);
    }
}