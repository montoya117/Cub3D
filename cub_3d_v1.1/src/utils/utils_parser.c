#include "cub_3d.h"

int is_str_digit(char *str)
{
    int i;

    i= 0;
    if (!str || str[0] == '\0')
        return (0);
    while (str[i] == ' ' || (str[i] > 9 && str[i] < 13))
        i++;
    while (str[i])
    {
        if (str[i] < '0' && str[i] > 9)
            return (0);
        i++;
    }
    return (1);
}