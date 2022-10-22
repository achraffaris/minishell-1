#include "../builtins.h"

int env_size(t_env *env)
{
    t_env *current;
    int i;

    i = 0;
    current = env;
    while (current)
    {
        i++;
        current = current->next;
    }
    return (i);
}

int item_is_min(char *key, t_env *env)
{
    t_env *current;

    current = env;
    if (!current->next)
        return (TRUE);
    while (current)
    {
        if (current->is_printed == FALSE && strcmp(key, current->key) > 0)
            return (FALSE);
        current = current->next;
    }
    return (TRUE);
}

int all_env_items_printed(t_env *env)
{
    t_env *current;

    current = env;
    while (current)
    {
        if (current->is_printed == FALSE)
            return (FALSE);
        current = current->next;
    }
    return (TRUE);
}

t_env    *get_next_min_item(t_env *env)
{
    t_env *current;

    current = env;
    while (current)
    {
        if (current->is_printed == FALSE && item_is_min(current->key, env))
            return (current);
        current = current->next;
    }
    return (NULL);
}
