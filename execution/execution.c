#include "execution.h"

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
    full_cmd[i] = ft_strdup(cmd);
    i++;
    while (args && args[j])
        full_cmd[i++] = ft_strdup(args[j++]);
    full_cmd[i] = NULL;
    return (full_cmd);
}

void    print_redirection_content(t_rdr *rd)
{
    t_rdr *current;

    current = rd;
    while (current)
    {
        char buff[200];
        printf("readed = %zd\n",read(current->fd, buff, 200));
        printf("fd no:%d type: %d content: %s\n", current->fd, current->type, buff);
        current = current->next;
    }
}

int get_input_redirection(t_parse *cmd)
{
    t_rdr *current;
    int fd;

    fd = 0;
    current = cmd->rdr;
    while (current)
    {
        if (current->type == HEREDOC || current->type == SINGLE_LEFT_RED)
            fd = current->fd;
        current = current->next;
    }
    return (fd);
}

int get_output_redirection(t_parse *cmd)
{
    t_rdr *current;
    int fd;

    fd = 0;
    current = cmd->rdr;
    while (current)
    {
        if (current->type == SINGLE_RIGHT_RED || current->type == DOUBLE_RIGHT_RED)
            fd = current->fd;
        current = current->next;
    }
    return (fd);
}

void    run_cmd(t_parse *cmd)
{
    char *cmd_path = find_cmd_path(cmd->cmd, cmd->env);
    char **full_cmd = get_full_cmd(cmd->cmd, cmd->arg);
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
        if (run_as_builtin(cmd))
            exit(0);
        else if (execve(cmd_path, full_cmd, cmd->primary_env) == ERROR_RETURNED)
            raise_error(NULL, NULL);
        exit(0);
    }
}

int cmds_len(t_parse *cmds)
{
    int i;
    t_parse *current;

    i = 0;
    current = cmds;
    while (current)
    {
        current = current->next;
        i++;
    }
    return (i);
}

void    execution(t_parse *data, t_env *env, char **primary_env)
{
    t_parse *current;
    int i;
    int ncmds;
    int fd[2];

    ncmds = cmds_len(data);
    i = 0;
    current = data;
    while (current)
    {

        current->write_dst = NONE;
        current->env = env;
        current->primary_env = primary_env;
        if (i == 0)
            current->read_src = NONE;
        if (i < (ncmds - 1))
        {
            pipe(fd);
            current->write_dst = fd[WRITE_END];
        }
        run_cmd(current);
        close(current->write_dst);
        current = current->next;
        if (current)
            current->read_src = fd[READ_END];
        i++; 
    }
    i = 0;
    while (i < ncmds)
    {
        waitpid(0, 0, 0);
        i++;
    }
}