#include "../execution.h"

int start_with(char *word, char *str)
{
    int i;

    i = 0;
    if (!word || !str)
        return (FALSE);
    while (word[i])
    {
        if (str[i] != word[i])
            return (FALSE);
        i++;   
    }
    return (TRUE);
}

int get_index_or_none(char *str, char c)
{
    int i;
    int pos;

    i = 0;
    pos = NONE;
    while (str && str[i])
    {
        if (str[i] == c)
        {
            pos = i;
            break ;
        }
        i++;
    }
    return (pos);
}

int substring_length(char *str, char to_stop, int mode)
{
    int i;
    int index;

    i = 0;
    index = get_index_or_none(str, to_stop);
    if (index == NONE)
        return (NONE);
    if (mode == BEFORE)
        return (index + 1);
    else
    {
        index++;
        while (str[index])
        {
            index++;
            i++;
        }
        return (i);
    }
    return (NONE);
}
