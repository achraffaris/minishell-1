#ifndef BUILTINS_H
#define BUILTINS_H

#define ECHO "echo"
#define CD "cd"
#define PWD "pwd"
#define EXPORT "export"
#define UNSET "unset"
#define ENV "env"
#define EXIT "exit"

#define FALSE 0
#define TRUE 1

#define NULL_CHARACTER '\0'

#define ECHO_N_FLAG "-n"

# include "../execution.h"
# include <string.h>

int     is_identical(char *s1, char *s2);
int     start_with(char *word, char *str);

int     run_as_builtin(t_parse *data);
int     run_echo(t_parse *data);
int     run_cd(t_parse *data);
int     run_pwd(t_parse *data);
int     run_unset(t_parse *data);
int     run_export(t_parse *data);
int     run_env(t_parse *data);
int     run_exit(t_parse *data);
int     env_key_valid(char *env_key);

void    remove_env_item(char *item, t_env *env, t_env **head);
void    add_env_item(t_env **head, char *item);
void    print_sorted_env_items(t_env *env);
t_env   *get_env_item_or_none(char *key, t_env *env);
char    *extract_env_key(char *item);
char    *extract_env_value(char *item);
void    update_env_item(t_env *item, char *arg);
t_env   *duplicate_env(t_env *env);
int     env_size(t_env *env);
t_env   *get_next_min_item(t_env *env);
int     all_env_items_printed(t_env *env);

#endif