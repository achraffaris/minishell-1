#include "header.h"
#include "execution/execution.h"
void add_back(t_token **list, t_token *tmp)
{
    if (*list == NULL)
        (*list) = tmp;
    else
    {
        t_token *tmp1 = *list;
        while(tmp1->next != NULL)
            tmp1 = tmp1->next;
        tmp1->next = tmp;
    } 
}

void	herdoc_handler(t_parse *parse)
{
	t_parse *tmp = parse;
	t_rdr *tmp1;
	while(tmp)
	{
		if (tmp->rdr != NULL)
		{
			tmp1 = tmp->rdr;
			while(tmp1)
			{
				if (tmp1->type == 3 && tmp1->herdoc)
				{
					tmp1->fd = open("/tmp/herdoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
					char *a = readline("> ");
					while (ft_strncmp(a, tmp1->value, ft_strlen(a)))
					{
						if (a)
						{
                            write(tmp1->fd, a, ft_strlen(a));
                            write(tmp1->fd, "\n", ft_strlen(a));
							ft_putstr_fd(a, tmp1->fd);
							ft_putstr_fd("\n", tmp1->fd);
						}
						free(a);
						a = readline("> ");
					}
				}
				tmp1 = tmp1->next;
			}
		}
		tmp = tmp->next;
	}
}

void	rdr_create_files(t_parse *parse)
{
	t_rdr *tmp = parse->rdr;
	while(tmp)
	{
		if (tmp->type == 4)
			tmp->fd = open(tmp->value, O_RDWR, 0777);
		if (tmp->type == 5)
			tmp->fd = open(tmp->value, O_CREAT | O_WRONLY | O_TRUNC, 0777);
		if (tmp->type == 6)
			tmp->fd = open(tmp->value, O_CREAT | O_RDWR | O_APPEND, 0777);
		tmp = tmp->next;
	}
}

int main(int ac, char **av, char **env)
{
    (void) ac;
    (void) av;
    t_lexer  *lexer;
    t_token *token = NULL;
    t_token *tmp;
    t_parse *parse = NULL;
	t_env 	*env_list;

    env_list = setup_env(env);
    char *str = NULL;
    lexer = malloc(sizeof(t_lexer));
    lexer->env = copy_env(env);
    while(1)
    {
        str = readline("minishell >$ ");
        if (str[0] != '\0')
        {
            lexer = init_lexer(str, lexer);
            while ((tmp = get_next_token(lexer)) != NULL && !lexer->flg_error)
                add_back(&token, tmp);
            if ((token) != NULL)
            {
                parse = init_parsing(&token, lexer);
            }
            if(!token && parse != NULL)
            {
                free(parse->cmd);
                parse->cmd = NULL;
                free(parse->arg);
                parse->arg = NULL;
                free(parse->rdr);
                parse->rdr = NULL;
            }
            //t_parse *tmp1 = parse;
            /*
            if (lexer->flg_error == 0 && parse != NULL)
            {
                while(tmp1)
                {
                    if (tmp1->cmd != NULL)
                    {
                        printf("cmd = %s\n", tmp1->cmd);
                        free(tmp1->cmd);
                    }
                    if (tmp1->arg != NULL)
                    {
                        int i = 0;
                        while(tmp1->arg[i])
                        {
                            printf("arg = %s\n", tmp1->arg[i]);
                            i++;
                        }
                    }
                    if (tmp1->rdr != NULL)
                    {
                        t_rdr *r = tmp1->rdr;
                        while(r)
                        {
                            printf("rdr->type = |%d|, rdr->value = |%s|\t, flg_error = |%d|\n", r->type, r->value, r->herdoc);
                            r = r->next;
                        }
                    }
                    printf("-----------------------\n");
                    tmp1 = tmp1->next;
					
                }
            }*/
            if (lexer->flg_error == 1)
                write(2, "syntax_error\n", 14);
            if (parse != NULL)
                herdoc_handler(parse);
			if (!lexer->flg_error && parse != NULL)
				rdr_create_files(parse);
            if (ft_strlen(str) > 0)
                add_history(str);
            if (parse != NULL)
                execution(parse, env_list, env);
            tmp = token;
            while(tmp)
            {
                token = token->next;
                free(tmp);
                tmp = token;
            }
            // tmp1 = parse;
            // while(tmp1)
            // {
            //     if (tmp1->cmd != NULL && tmp1->cmd[0] != '\0')
            //     {
            //         free(tmp1->cmd);
            //     }
            //     tmp1 = tmp1->next;
            // }
        }

    }
return 0;
}