#include "gps_data.h"

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

void print_gps_arr(GPS_Data data[])
{
    for (int i = 0; i < MAX_FILE_SIZE; i++)
    {
        if (gps_ok(data[i]))
        {
            print_gps_data(data[i]);
            printf("------------------\n");
        }
    }
}