#include "utils.h"

int int_len(int nb)
{
    if (nb < 10) return 1;
    return 1 + int_len(nb / 10);
}

bool lat_ok(double latitude)
{
    return latitude >= -90 && latitude <= 90;
}

bool lon_ok(double longitude)
{
    return longitude >= -180 && longitude <= 180;
}

bool code_ok(int code)
{
    return int_len(code) == 5;
}