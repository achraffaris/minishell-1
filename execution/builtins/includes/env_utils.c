#include "../builtins.h"

int env_key_valid(char *env_key)
{
    int i;

    i = 0;
    if (!env_key || ft_isdigit(env_key[0]))
        return (FALSE);
    while (env_key[i])
    {
        if (!(ft_isalnum(env_key[i])
                || ft_isdigit(env_key[i])
                || env_key[i] == '_'))
            return (FALSE);
        i++;
    }
    return (TRUE);
}

char    *extract_env_key(char *item)
{
    char *env_key;
    int i;
    int len;

    i = 0;
    len = substring_length(item, '=', BEFORE);
    env_key = malloc(sizeof(char) * (len + 1));
    if (!env_key)
        raise_error("Memory allocation failed!", "malloc");
    while (item[i] && item[i] != '=')
    {
        env_key[i] = item[i];
        i++;
    }
    env_key[i] = '\0';
    if (!env_key_valid(env_key))
        raise_error("Not a valid identifier", env_key);
    return (env_key);
}

char    *extract_env_value(char *item)
{
    char    *env_value;
    int     j;
    int     i;
    int     len;

    len = substring_length(item, '=', AFTER);
    i = 0;
    j = 0;
    if (len == NONE)
        return (NULL);
    env_value = malloc(sizeof(char) * (len + 1));
    if (!env_value)
        raise_error("Memory Allocation Failed!", "malloc");
    while (item[i] && item[i] != '=')
        i++;
    if (item[i] == '=')
    {
        i++;
        while (item[i])
            env_value[j++] = item[i++];
    }
    env_value[j] = '\0';
    return (env_value);
}

void    add_env_item(t_env **head, char *item)
{
    t_env *current;
    t_env *new;

    current = *head;
    new = malloc(sizeof(t_env));
    if (!new)
        raise_error("Memory Allocation Failed!", "malloc");
    while (current && current->next)
        current = current->next;
    new->key = extract_env_key(item);
    new->value = extract_env_value(item);
    new->is_printed = FALSE;
    new->next = NULL;
    if (!(*head))
        *head = new;
    else
        current->next = new;
}

t_env   *setup_env(char **env)
{
    t_env *head;
    int i;

    i = 0;
    head = NULL;
    while (env[i])
    {
        add_env_item(&head, env[i]);
        i++;
    }
    return (head);
}