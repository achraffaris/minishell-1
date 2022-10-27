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

int valid_echo_flag(char *flag)
{
    int i;

    i = 0;
    if (flag && flag[i] != '-' && flag[i + 1] != 'n')
        return (FALSE);
    i++;
    while (flag && flag[i])
    {
        if (flag[i] != 'n')
            return (FALSE);
        i++;
    }
    return (TRUE);
}