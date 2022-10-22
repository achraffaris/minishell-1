#include "../builtins.h"

int run_env(t_parse *data)
{
    t_env *current;

    current = data->env;
    if (!is_identical(data->cmd, ENV))
        return (FALSE);
    while (current)
    {
        if (current->value)
            printf("%s=%s\n", current->key, current->value);
        current = current->next;
    }
    return (TRUE);
}

int run_exit(t_parse *data)
{
    if (!is_identical(data->cmd, EXIT))
        return (FALSE);
    exit(0);
    return (TRUE);
}