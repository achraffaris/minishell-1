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

void    execution(t_parse *data, t_env *env, char **primary_env);
void    raise_error(char *err_msg, char *err_src);
int     substring_length(char *str, char to_stop, int mode);
t_env   *setup_env(char **env);
char    *find_cmd_path(char *cmd, t_env *env);


#endif