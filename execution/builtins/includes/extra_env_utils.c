#include "../builtins.h"

void    free_env_item(t_env *item)
{
    if (item)
    {
        if (item->key)
            free(item->key);
        if (item->value)
            free(item->value);
        free(item);
        item = NULL;
    }
}

void    print_env_items(t_env *env)
{
    t_env *current;

    current = env;
    while (current)
    {
        printf("%s\n", current->key);
        current = current->next;
    }
}

void    remove_env_item(char *item, t_env *env, t_env **head)
{
    t_env *current;
    t_env *found;
    
    current = env;
    if (ft_strcmp(item, current->key) == 0)
    {
        *head = current->next;
        free_env_item(current);
    }
    else
    {
        while (current)
        {
            if (current->next && ft_strcmp(item, current->next->key) == 0)
            {
                found = current->next;
                current->next = found->next;
                free_env_item(found);
                break ;
            }
            current = current->next;
        }
    }
}

void    print_sorted_env_items(t_env *env)
{
    t_env *min;
    t_env *current;
    min = get_next_min_item(env);
    current = env;
    while(min)
    {
        if (min->value)
            printf("declare -x %s=\"%s\"\n", min->key, min->value);
        else
            printf("declare -x %s\n", min->key);
        min->is_printed = TRUE;
        min = get_next_min_item(env);
    }
    while (current)
    {
        current->is_printed = FALSE;
        current = current->next;
    }
}

t_env   *get_env_item_or_none(char *key, t_env *env)
{
    t_env *current;

    current = env;
    while (current)
    {
        if (is_identical(key, current->key))
            return (current);
        current = current->next;
    }
    return (NULL);
}

void    update_env_item(t_env *item, char *arg)
{
    char *value;

    value = extract_env_value(arg);
    free(item->value);
    item->value = value;
}
