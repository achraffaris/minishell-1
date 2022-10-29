#include "../execution.h"

int get_input_redirection(t_parse *cmd)
{
    t_rdr *current;
    int fd;

    fd = NONE;
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

    fd = NONE;
    current = cmd->rdr;
    while (current)
    {
        if (current->type == SINGLE_RIGHT_RED || current->type == DOUBLE_RIGHT_RED)
            fd = current->fd;
        current = current->next;
    }
    return (fd);
}
