#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "city.h"
#include "repl.h"
#include "csv.h"

void usage(const char* program_name)
{
    fprintf(stderr, "Usage: %s <CSV file name> [-s 'CSV separator' (default is ',')]\n", program_name);
}

int main(int argc, char* argv[])
{
    const char* separator = ",";
    if (argc < 2)
    {
        usage(argv[0]);
        return 1;
    }
    else if (argc == 3)
    {
        usage(argv[0]);
        if (strcmp(argv[2], "-s") != 0)
            fprintf(stderr, "Error: %s is not a valid argument", argv[2]);
    }
    else if (argc >= 4)
    {
        if (strcmp(argv[2], "-s") == 0)
            separator = argv[3];
        else
        {
            usage(argv[0]);
            fprintf(stderr, "Error: %s is not a valid argument", argv[2]);
            return 1;
        }
    }
    
    char* csv_file = argv[1];

    FILE* file = fopen(csv_file, "r");
    City_Array city_arr;
    city_array_init(&city_arr);

    read_csv(file, &city_arr, separator);
    fclose(file);

    repl(&city_arr);

    city_array_free(city_arr);

    return 0;
}