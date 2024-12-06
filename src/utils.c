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

bool is_int(const char* s)
{
    const char* p = s;
    while (*p)
    {
        if (!isdigit(*p++))
            return false;
    }
    return true;
}

// for more details see this SO question:
// https://stackoverflow.com/questions/45554639/is-there-a-way-to-check-if-a-string-can-be-a-float-in-c
bool is_float(const char* s)
{
    int len;
    float ignore;
    int ret = sscanf(s, "%f %n", &ignore, &len);
    return ret == 1 && !s[len];
}