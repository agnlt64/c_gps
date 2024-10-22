#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_FILE_SIZE 1024
#define BUF_SIZE 256

typedef struct {
    int code;
    char* name;
    double latitude;
    double longitude;
} GPS_Data;

void print_gps_data(GPS_Data data)
{
    printf("Code : %d\n", data.code);
    printf("Ville : %s\n", data.name);
    printf("Latitude : %f\n", data.latitude);
    printf("Longitude : %f\n", data.longitude);
}

bool gps_ok(GPS_Data data)
{
    return data.name != NULL && data.code != -1 && data.latitude != -1 && data.longitude != -1;
}

void read_csv(FILE* file, GPS_Data gps_data_arr[])
{
    size_t i = 0;
    while (!feof(file))
    {
        size_t col_index = 0;
        GPS_Data data = {0};

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
        gps_data_arr[i] = data;
        i++;
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
    GPS_Data* data = malloc(MAX_FILE_SIZE * sizeof(GPS_Data));

    read_csv(file, data);

    for (int i = 0; i < MAX_FILE_SIZE; i++)
    {
        if (gps_ok(data[i]))
        print_gps_data(data[i]);
    }

    fclose(file);
    free(data);

    return 0;
}