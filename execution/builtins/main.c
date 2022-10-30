# include "builtins.h"

int run_as_builtin(t_parse *data, t_env **env)
{
    if (run_echo(data)
            || run_cd(data, *env)
            || run_pwd(data)
            || run_unset(data, env)
            || run_env(data, env)
            || run_exit(data)
            || run_export(data, env))
        return (TRUE);
    return FALSE;
}