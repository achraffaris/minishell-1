#include "execution.h"

int     exit_status;

char    **get_full_cmd(char *cmd, char **args)
{
    char **full_cmd;
    int i;
    int j;

    j = 0;
    i = 0;
    full_cmd = NULL;
    while (args && args[i])
        i++;
    full_cmd = malloc(sizeof(char *) * (i + 2));
    if (!full_cmd)
        raise_error("Memory allocation failed!", "malloc");
    i = 0;
    full_cmd[i] = cmd;
    i++;
    while (args && args[j])
        full_cmd[i++] = args[j++];
    full_cmd[i] = NULL;
    return (full_cmd);
}

void    first_cmd_exec(t_parse *cmd, t_exec *exe)
{
    cmd->pid = fork();
    if (cmd->pid == ERROR_RETURNED)
        raise_error(NULL, "fork");
    if (cmd->pid == 0)
    {
        close(exe->pipes[cmd->id][0]);
        dup2(exe->pipes[cmd->id][1], 1);
        if (run_as_builtin(cmd))
            exit(0);
        else
            if (execve(find_cmd_path(cmd->cmd, cmd->env), get_full_cmd(cmd->cmd, cmd->arg), cmd->default_env) == ERROR_RETURNED)
                    raise_error(NULL, NULL);
        exit(0);
    }
}

void    midlle_cmds_exec(t_parse *cmd, t_exec *exe)
{
    cmd->pid = fork();
    if (cmd->pid == ERROR_RETURNED)
        raise_error(NULL, "fork");
    if (cmd->pid == 0)
    {
        close(exe->pipes[cmd->id - 1][1]);
        dup2(exe->pipes[cmd->id - 1][0], 0);
        dup2(exe->pipes[cmd->id][1], 1);
        close(exe->pipes[cmd->id][0]);
        if (run_as_builtin(cmd))
            exit(0);
        else
            if (execve(find_cmd_path(cmd->cmd, cmd->env), get_full_cmd(cmd->cmd, cmd->arg), cmd->default_env) == ERROR_RETURNED)
                    raise_error(NULL, NULL);
        exit(0);
    }
}

void    last_cmds_exec(t_parse *cmd, t_exec *exe)
{
    cmd->pid = fork();
    if (cmd->pid == ERROR_RETURNED)
        raise_error(NULL, "fork");
    if (cmd->pid == 0)
    {
        close(exe->pipes[cmd->id - 1][1]);
        dup2(exe->pipes[cmd->id - 1][0], 0);
        if (run_as_builtin(cmd))
            exit(0);
        else
            if (execve(find_cmd_path(cmd->cmd, cmd->env), get_full_cmd(cmd->cmd, cmd->arg), cmd->default_env) == ERROR_RETURNED)
                    raise_error(NULL, NULL);
        exit(0);
    }
}

void    run_cmd(t_parse *cmd, t_exec *exe)
{
    char    *cmd_path;
    cmd_path = NULL;
    if (exe->pipes)
    {
        if (cmd->id == 0)
            first_cmd_exec(cmd, exe);
        else if (cmd->id == exe->ncmds - 1)
            last_cmds_exec(cmd, exe);
        else
            midlle_cmds_exec(cmd, exe);
    }
    else
    {
        if (cmd->type == NORMAL_CMD)
        {
            cmd->pid = fork();
            if (cmd->pid == ERROR_RETURNED)
                raise_error(NULL, "fork");
            if (cmd->pid == 0)
            {
                if (execve(find_cmd_path(cmd->cmd, cmd->env), get_full_cmd(cmd->cmd, cmd->arg), cmd->default_env) == ERROR_RETURNED)
                    raise_error(NULL, NULL);
            }
        }
        else
            run_as_builtin(cmd);
    }
    
}

t_exec  *setup_exec(t_parse *cmds)
{
    t_exec  *exe;
    t_parse *current;

    exe = malloc(sizeof(t_exec));
    if (!exe)
        raise_error("Memory allocation failed!", "malloc");
    exe->cmds = cmds;
    exe->ncmds = 0;
    current = cmds;
    while (current)
    {
        exe->ncmds++;
        current = current->next;
    }
    exe->pipes = NULL;
    if (exe->ncmds > 1)
    {
        exe->pipes = malloc(sizeof(int *) * (exe->ncmds - 1));
        if (!exe->pipes)
            raise_error("Memory allocation failed!", "malloc");
    }
    return (exe);
}

void    execution(t_parse *data)
{
    int i;

    i = 0;
    t_exec  *exe;
    t_parse *current;

    exe = setup_exec(data);
    current = exe->cmds;
    
    while (current)
    {
        if (exe->pipes)
            pipe(exe->pipes[i]);
        current->id = i;
        run_cmd(current, exe);
        i++;
        current = current->next;
    }
    i = 0;
    while (i <= exe->ncmds - 1)
    {
        waitpid(0, &exitm, 0);
        i++;
    }
}

