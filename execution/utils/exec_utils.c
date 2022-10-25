#include "../execution.h"

char **env_converter(t_env *env)
{
    int i;
    char **env_ptr;
    t_env *current;

    current = env;
    i = 0;
    env_ptr = malloc(sizeof(char *) * (env_size(env) + 1));
    while (current)
    {
        env_ptr[i] = ft_strjoin(ft_strjoin(current->key, "="), current->value);
        current = current->next;
        i++;
    }
    env_ptr[i] = NULL;
    return (env_ptr);
}