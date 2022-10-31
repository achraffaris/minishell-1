#include "execution.h"

void    execute_cmd(t_parse *cmd, t_env **env)
{
    g_exitm = EXIT_SUCCESS;
    if (cmd->type == BUILTIN_CMD)
        run_as_builtin(cmd, env);
    else
    {
        if (cmd->path[0] == '.' || cmd->path[0] == '/')
        {
            if(access(cmd->path, X_OK) == ERROR_RETURNED)
                raise_error(NULL, NULL, 126, TRUE);
        }
        if (execve(cmd->path, cmd->cmd_2d, cmd->env_2d) == ERROR_RETURNED)
            raise_error("command not found", cmd->cmd, 127, TRUE);
    }
    
}

int fork_manager(t_parse *cmd, t_exec *exe)
{
    int pid;

    pid = NONE;
    if (exe->pipes || cmd->type == NORMAL_CMD)
        pid = fork();
    return (pid);
}

void    wait_cmds(t_parse *cmds)
{
    t_parse *current;
    
    current = cmds;
    while (current)
    {
        if (current->pid != NONE)
            waitpid(current->pid, &g_exitm, WUNTRACED);
        current = current->next;
    }
}

void    close_fds(t_exec *exe, t_parse *cmd)
{
    int i;

    i = 0;
    while (exe->pipes && i < (exe->ncmds - 1))
    {
        close(exe->pipes[i][WRITE_END]);
        close(exe->pipes[i][READ_END]);
        i++;
    }
    if (cmd)
    {
        close(cmd->read_src);
        close(cmd->write_dst);
    }
}

int read_from_pipe(t_parse *cmd, t_exec *exe)
{
    int fd;

    fd = NONE;
    if (exe->pipes)
    {
        if (cmd->id == 0)
            fd = NONE;
        else
            fd = exe->pipes[cmd->id - 1][READ_END];
    }
    return (fd);
}

int write_into_pipe(t_parse *cmd, t_exec *exe)
{
    int fd;

    fd = NONE;
    if (exe->pipes)
    {
        if (cmd->id == (exe->ncmds - 1))
            fd = NONE;
        else
            fd = exe->pipes[cmd->id][WRITE_END];
    }
    return (fd);
}

void    run_cmd(t_parse *data, t_env **env, t_exec *exe)
{
    t_parse *current;

    current = data;
    if (current->status == OK)
    {
        current->pid = NONE;
        if (exe->pipes || current->type == NORMAL_CMD)
            current->pid = fork();
        if (current->pid == 0 || current->pid == NONE)
        {
            if (current->read_src == NONE && exe->pipes)
                current->read_src = read_from_pipe(current, exe);
            if (current->write_dst == NONE && exe->pipes && current->next)
                current->write_dst = write_into_pipe(current, exe);
            int old = dup(1);
            if (current->read_src != NONE)
                dup2(current->read_src, 0);
            if (current->write_dst != NONE)
                dup2(current->write_dst, 1);
            close_fds(exe, current);
            execute_cmd(current, env);
            dup2(old, 1);
        }

    }
}

int **create_pipes(int npipes)
{
    int **pipes;
    int i;

    i = 0;
    pipes = malloc(sizeof(int *) * npipes);
    while (i < npipes)
    {
        pipes[i] = malloc(sizeof(int ) * 2);
        pipe(pipes[i]);
        i++;
    }
    return (pipes);
}

t_exec  *setup_exec(t_parse *data)
{
    int i;
    t_parse *current;
    t_exec *exe;

    exe = malloc(sizeof(t_exec));
    exe->ncmds = 0;
    exe->pipes = NULL;
    current = data;
    i = 0;
    while (current)
    {
        current = current->next;
        exe->ncmds++;
    }
    if (exe->ncmds > 1)
        exe->pipes = create_pipes(exe->ncmds - 1);
    return (exe);
}

int get_cmd_type(char *cmd_name)
{
    if (is_identical(cmd_name, ECHO)
        || is_identical(cmd_name, CD)
        || is_identical(cmd_name, PWD)
        || is_identical(cmd_name, EXPORT)
        || is_identical(cmd_name, UNSET)
        || is_identical(cmd_name, ENV)
        || is_identical(cmd_name, EXIT))
        return (BUILTIN_CMD);
    return (NORMAL_CMD);
}

void    setup_run_cmds(t_parse *data, t_env **env, t_exec *exe)
{
    t_parse *current;
    int i;

    i = 0;
    current = data;
    while (current)
    {
        current->id = i;
        current->type = get_cmd_type(current->cmd);
        if (current->rdr)
            printf("red fd = %d\n", current->rdr->fd);
        if (current->type == NORMAL_CMD)
        {
            current->path = find_cmd_path(current->cmd, *env);
            current->cmd_2d = get_full_cmd(current->cmd, current->arg);
            current->env_2d = env_converter(*env);
        }
        current->read_src = get_input_redirection(current);
        current->write_dst = get_output_redirection(current);
        if (current->read_src != ERROR_FILE && current->write_dst != ERROR_FILE)
            current->status = OK;
        else
            current->status = KO;
        run_cmd(current, env, exe);
        current = current->next;
        i++;
    }
}



void    execution(t_parse *data, t_env **env)
{
    t_parse *current;
    t_exec *exe;

    exe = setup_exec(data);
    setup_run_cmds(data, env, exe);
    close_fds(exe, data);
    wait_cmds(data);
}