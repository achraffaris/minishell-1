#ifndef EXECUTION_H
# define EXECUTION_H

#include "../header.h"
#include "builtins/builtins.h"
#include <sys/types.h>
#include <sys/wait.h>

#define ERROR_RETURNED -1
#define AFTER 1
#define BEFORE 0
#define NONE -1
#define READ_END 0
#define WRITE_END 1
#define PATH "PATH"

#define HEREDOC 3
#define SINGLE_LEFT_RED 4
#define SINGLE_RIGHT_RED 5
#define DOUBLE_RIGHT_RED 6
#define ERROR_FILE -2

#define OK 1
#define KO 0

#define BUILTIN_CMD 7
#define NORMAL_CMD 8

typedef struct s_exec
{
    int ncmds;
    int i;
    int **pipes;
}   t_exec;

void    execution(t_parse *data, t_env **env);
void    raise_error(char *err_msg, char *err_src, int exit_code, int exit);
int     substring_length(char *str, char to_stop, int mode);
t_env   *setup_env(char **env);
char    *find_cmd_path(char *cmd, t_env *env);
char    *extract_cmd_path(char **paths, char *cmd);
char    *find_cmd_path(char *cmd, t_env *env);
char    **get_full_cmd(char *cmd, char **args);
void    cmd_init(t_parse *cmd, t_env *env);
int     cmds_len(t_parse *cmds);
int     get_input_redirection(t_parse *cmd);
int     get_output_redirection(t_parse *cmd);
char    **env_converter(t_env *env);


#endif