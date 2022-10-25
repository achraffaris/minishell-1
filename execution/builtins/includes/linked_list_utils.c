#include "../builtins.h"

t_env *duplicate_env(t_env *env)
{
    t_env   *new;
    t_env   *new_head;
    t_env   *current;

    new = malloc(sizeof(t_env));
    if (!new)
        raise_error("Memory Allocation Failed!", "malloc");
    new_head = new;
    current = env;
    while (current)
    {
        new->key = ft_strdup(current->key);
        new->value = ft_strdup(current->value);
        if (current->next)
        {
            new->next = malloc(sizeof(t_env));
            if (!new->next)
                raise_error("Memory Allocation Failed!", "malloc");
        }
        else
            new->next = NULL;
        current = current->next;
        new = new->next;
    }
    return (new_head);
}

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
