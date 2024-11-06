#include "utils.h"

int int_len(int nb)
{
    if (nb < 10) return 1;
    return 1 + (int)int_len(nb / 10);
}