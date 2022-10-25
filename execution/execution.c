#include "execution.h"

void    execute_cmd(t_parse *cmd)
{
    if (run_as_builtin(cmd))
        exit(0);
    else if (execve(find_cmd_path(cmd->cmd, cmd->env), get_full_cmd(cmd->cmd, cmd->arg), env_converter(cmd->env)) == ERROR_RETURNED)
        raise_error(NULL, NULL);
    exit(0);
}

void    handle_cmd(t_parse *cmd)
{
    int in_red;
    int out_red;

    in_red = get_input_redirection(cmd);
    out_red = get_output_redirection(cmd);
    cmd->pid = fork();
    if (cmd->pid == 0)
    {
        if (in_red != 0)
            cmd->read_src = in_red;
        if (out_red != 0)
            cmd->write_dst = out_red;
        if (cmd->read_src != NONE)
            dup2(cmd->read_src, 0);
        if (cmd->write_dst != NONE)
            dup2(cmd->write_dst, 1);
        execute_cmd(cmd);
    }
}

void    wait_cmds(int ncmds)
{
    int i;

    i = 0;
    while (i < ncmds)
    {
        waitpid(0, 0, 0);
        i++;
    }
}

void    execution(t_parse *data, t_env *env, char **primary_env)
{
    t_parse *current;
    int i;
    int fd[2];

    i = 0;
    current = data;
    while (current)
    {
        cmd_init(current, env);
        if (i == 0)
            current->read_src = NONE;
        if (i < (cmds_len(data) - 1))
        {
            pipe(fd);
            current->write_dst = fd[WRITE_END];
        }
        handle_cmd(current);
        close(current->write_dst);
        current = current->next;
        if (current)
            current->read_src = fd[READ_END];
        i++; 
    }
    wait_cmds(cmds_len(data));
}