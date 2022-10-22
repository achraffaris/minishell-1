#include "../execution.h"

int open_heredoc(char *delimiter)
{
    int     fd[2];
    int     pid;
    char    *read_line;
    char    *line;

    pipe(fd);
    pid = fork();
    if (pid == 0)
    {
        close(fd[0]);
        read_line = readline("> ");
        while (read_line)
        {
            if (is_identical(read_line, delimiter))
                exit(0);
            line = ft_strjoin(read_line, "\n");
            write(fd[1], line, ft_strlen(line));
            read_line = readline("> ");
        }        
    }
    close(fd[1]);
    waitpid(pid, 0, 0);
    return (fd[0]);
}

int get_read_src(t_parse *cmd, t_exec *exe)
{
    int     fd;
    t_rdr   *current;

    fd = NONE;
    current = cmd->rdr;
    if (current)
    {
        while (current)
        {
            if (current->type == HEREDOC)
                fd = open_heredoc(current->value);
            else if (current->type == SINGLE_LEFT_RDR)
            {
                fd = open(current->value, O_RDONLY);
                if (fd == ERROR_RETURNED)
                    raise_error(NULL, current->value);
            }
            current = current->next;
        }
    }
    else if (cmd->id > 0)
        fd = exe->pipes[cmd->id - 1][0];
    return (fd);
}