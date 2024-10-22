#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gps_data.h"
#include "repl.h"


#define BUF_SIZE 256

void read_csv(FILE* file, City_Array city_arr)
{
    while (!feof(file))
    {
        size_t col_index = 0;
        City data = {0};

        char buf[BUF_SIZE];
        fgets(buf, BUF_SIZE, file);

        char* token = strtok(buf, ";");

        while (token)
        {
            switch (col_index)
            {
                case 0:
                {
                    int value = atoi(token);
                    data.code = value != 0 ? value : -1;
                    break;
                }
                case 1:
                    data.name = strdup(token);
                    break;
                case 2:
                {
                    double value = atof(token);
                    data.latitude = value != 0 ? value : -1;
                    break;
                }
                case 3:
                {
                    double value = atof(token);
                    data.longitude = value != 0 ? value : -1;
                    break;
                }
            }
            token = strtok(NULL, ";");
            col_index = (col_index + 1) % 4;
        }
        city_array_add(&city_arr, data);
    }
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <CSV file name>\n", argv[0]);
        return 1;
    }
    
    char* csv_file = argv[1];

    FILE* file = fopen(csv_file, "r");
    City_Array city_arr;
    city_array_init(&city_arr);

    read_csv(file, city_arr);

    repl(city_arr);

    fclose(file);
    free(city_arr.items);

    return 0;
}