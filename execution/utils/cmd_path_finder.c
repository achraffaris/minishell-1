#include "../execution.h"

char    *extract_cmd_path(char **paths, char *cmd)
{
    char *full_path;
    char *new_cmd;
    int i;

    i = 0;
    full_path = NULL;
    if (!paths)
        return (cmd);
    new_cmd = ft_strjoin("/", cmd);
    while (paths[i])
    {
        full_path = ft_strjoin(paths[i], new_cmd);
        if (access(full_path, X_OK) != ERROR_RETURNED)
        {
            free(new_cmd);
            return (full_path);
        }
        free(full_path);
        i++;
    }
    return (cmd);
}

char    *find_cmd_path(char *cmd, t_env *env)
{
    t_env *current;
    char **paths;

    paths = NULL;
    current = env;
    while (current)
    {
        if (is_identical(current->key, PATH))
        {
            paths = ft_split(current->value, ':');
            break ;
        }
        current = current->next;
    }
    return (extract_cmd_path(paths, cmd));
}