#include "../builtins.h"

int is_identical(char *s1, char *s2)
{
    size_t i;

    i = 0;
    if (!s1)
        return (FALSE);
    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    if (i == ft_strlen(s2) && i == ft_strlen(s1))
        return (TRUE);
    return (FALSE);
}

