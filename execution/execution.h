#ifndef EXECUTION_H
# define EXECUTION_H

#include "../header.h"
#include "builtins/builtins.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

#define ERROR_RETURNED -1
#define AFTER 1
#define BEFORE 0
#define NONE -1

#define HEREDOC 3
#define SINGLE_LEFT_RDR 4
#define SINGLE_RIGHT_RDR 5
#define DOUBLE_RIGHT_RDR 6

#define CTRL_D 68

typedef struct s_execution
{
    t_parse     *cmds;
    int         **pipes;
    int         ncmds;
}   t_exec;


void    execution(t_parse *data);
void    raise_error(char *err_msg, char *err_src);
int     substring_length(char *str, char to_stop, int mode);
t_env   *setup_env(char **env);
char    *find_cmd_path(char *cmd, t_env *env);
int     get_read_src(t_parse *cmd, t_exec *exe);

#endif