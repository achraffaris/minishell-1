#include "execution.h"

void    execute_cmd(t_parse *cmd, t_env **env)
{
    if (run_as_builtin(cmd, env))
        exit(0);
    // if (cmd->path[0] == '.' || cmd->path[0] == '/')
    // {
    //     if(access(cmd->path, X_OK))
    //         raise_error(NULL, NULL, 126);
    //         exit(126);
    // }
    else if (execve(cmd->path, cmd->cmd_2d, cmd->env_2d) == ERROR_RETURNED)
    {
        raise_error(NULL, NULL, 127);
        exit(127);
    }
    exit(0);
}

void    handle_cmd(t_parse *cmd, t_env **env)
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
        execute_cmd(cmd, env);
    }
}

void    wait_cmds(t_parse *cmds)
{
    t_parse *current;
    
    current = cmds;
    while (current)
    {
        waitpid(current->pid, &g_exitm, 0);
        current = current->next;
    }
    printf("exit code =  %d\n", g_exitm);
}

void    execution(t_parse *data, t_env **env)
{
    t_parse *current;
    int i;
    int fd[2];
    int ncmds;

    ncmds = cmds_len(data);
    i = 0;
    current = data;
    while (current)
    {
        cmd_init(current, *env);
        if (ncmds == 1 && run_as_builtin(current, env))
            break ;
        if (i == 0)
            current->read_src = NONE;
        if (i < (ncmds - 1))
        {
            pipe(fd);
            current->write_dst = fd[WRITE_END];
        }
        handle_cmd(current, env);
        close(current->write_dst);
        current = current->next;
        if (current)
            current->read_src = fd[READ_END];
        i++; 
    }
    wait_cmds(data);
}