#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "city.h"
#include "repl.h"
#include "csv.h"

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

    read_csv(file, &city_arr);

    repl(city_arr);

    fclose(file);
    free(city_arr.items);

    return 0;
}