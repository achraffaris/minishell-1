# include "builtins.h"

int run_as_builtin(t_parse *data)
{
    if (run_echo(data)
            || run_cd(data)
            || run_pwd(data)
            || run_unset(data)
            || run_echo(data)
            || run_env(data)
            || run_exit(data)
            || run_export(data))
        return (TRUE);
    return FALSE;
}