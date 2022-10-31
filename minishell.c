/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoukou <schoukou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 08:44:28 by schoukou          #+#    #+#             */
/*   Updated: 2022/10/31 16:32:53 by schoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "execution/execution.h"
#include <signal.h>

void my_handler(int signum)
{
   if (signum == SIGINT)
    {
        printf("\n");
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
}

void add_back(t_token **list, t_token *tmp)
{
    t_token *tmp1;
    
    tmp1 = *list;
    if (*list == NULL)
        (*list) = tmp;
    else
    {
        while(tmp1->next != NULL)
			tmp1 = tmp1->next;
        tmp1->next = tmp;
    }
}

int bigger(int a, int c)
{
    if (a > c)
        return (a);
    return (c);
}

void	herdoc_handler(t_parse *parse)
{
	t_parse *tmp;
	t_rdr   *tmp1;
    char    *a;
    int     fd[2];

    tmp = parse;
	while(tmp)
	{
		if (tmp->rdr != NULL)
		{
			tmp1 = tmp->rdr;
			while(tmp1)
			{
				if (tmp1->type == 3 && tmp1->herdoc)
				{
                    pipe(fd);
					a = readline("> ");
					while (ft_strncmp(a, tmp1->value, bigger(ft_strlen(a), ft_strlen(tmp1->value))))
					{
						if (a)
						{
                            free(a);
							ft_putstr_fd(a, fd[1]);
							ft_putstr_fd("\n", fd[1]);
						}
                        a = readline("> ");
                    }
                    free(a);
                    close(fd[1]);
					tmp1->fd = fd[0];
				}
				tmp1 = tmp1->next;
			}
		}
		tmp = tmp->next;
	}
}

void	rdr_create_files(t_parse **parse)
{
	t_parse *tmp = (*parse);
    t_rdr *tmpr;
	while(tmp)
	{
        tmpr = tmp->rdr;
        while(tmpr)
        {
		    if (tmpr->type == 4)
			    tmpr->fd = open(tmpr->value, O_RDWR, 0777);
		    if (tmpr->type == 5)
			    tmpr->fd = open(tmpr->value, O_CREAT | O_WRONLY | O_TRUNC, 0777);
		    if (tmpr->type == 6)
			    tmpr->fd = open(tmpr->value, O_CREAT | O_RDWR | O_APPEND, 0777);
            tmpr = tmpr->next;
        }
        tmp = tmp->next;
	}
}

void ft_free_list(t_parse *parse)
{
    int i;
    t_rdr *tmpr;
    t_parse *tmp = parse;

    while(tmp)
    {
        if (tmp->cmd)
            free(tmp->cmd);
        if(tmp->arg)
        {
            i = 0;
            while(tmp->arg[i])
            {
                free(tmp->arg[i]);
                i++;
            }
            free(tmp->arg);
        }
        if (tmp->rdr)
        {
            while(tmp->rdr)
            {
                tmpr = tmp->rdr;
                if (tmpr->value)
                    free(tmpr->value);
                tmp->rdr = tmp->rdr->next;
                free(tmpr);
            }
        }
        parse = parse->next;
        free(tmp);
        tmp = parse;
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
    while(1)
    {
        lexer->env = env_converter(env_list);
        signal(SIGINT, my_handler);
        signal(SIGQUIT, SIG_IGN);
        str = readline("minishell >$ ");
        if (!str)
        {
            printf("exit\n");
            exit(g_exitm);
        }
        if (str[0] != '\0')
        {
            lexer = init_lexer(str, lexer);
			token = NULL;
            while ((tmp = get_next_token(lexer)) != NULL && !lexer->flg_error)
			{
                add_back(&token, tmp);
                tmp = NULL;
			}
            if ((token) != NULL)
                parse = init_parsing(&token, lexer);
            t_parse *tmp1 = parse;
            if (lexer->flg_error == 0 && parse != NULL && token != NULL)
            {
                while(tmp1)
                {
                    if (tmp1->cmd != NULL)
                    {
                        printf("cmd = %s\n", tmp1->cmd);
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
            }
            if (lexer->flg_error == 1)
            {
                write(2, "syntax_error\n", 14);
                g_exitm = 255;
            }
            if (parse != NULL)
                herdoc_handler(parse);
			if (!lexer->flg_error && parse != NULL)
				rdr_create_files(&parse);
            if (ft_strlen(str) > 0)
                add_history(str);
            // if (parse != NULL)
            //     execution(parse, &env_list);
            tmp = token;
            if (token)
            {
                while (tmp)
                {
                    token = token->next;
                    free(tmp->value);
                    free(tmp);
                    tmp = token;
                }
            }
            ft_free_list(parse);
            parse = NULL;
        }
        free(str);
    }
    return (0);
}
