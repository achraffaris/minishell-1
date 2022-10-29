/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoukou <schoukou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 08:44:28 by schoukou          #+#    #+#             */
/*   Updated: 2022/10/27 11:14:17 by schoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "execution/execution.h"
#include <signal.h>

// void my_handler()
// {
//     rl_on_new_line();
//     rl_redisplay();
// }

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

void	herdoc_handler(t_parse *parse)
{
	t_parse *tmp;
	t_rdr   *tmp1;
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
					char *a = readline("> ");
					while (ft_strncmp(a, tmp1->value, ft_strlen(a)))
					{
						if (a)
						{
                            // write(tmp1->fd, a, ft_strlen(a));
                            // write(tmp1->fd, "\n", ft_strlen(a));
							ft_putstr_fd(a, fd[1]);
							ft_putstr_fd("\n", fd[1]);
						}
						free(a);
						a = readline("> ");
					}
                    close(fd[1]);
					tmp1->fd = fd[0];
				}
                // printf("read = %ld\n", read(tmp1->fd, buff, 200));
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
void ft_free_list(t_parse *parse)
{
    int i;
    t_parse *tmp;
    while(parse)
    {
        if (parse->cmd)
			free(parse->cmd);
		if(parse->arg)
        {
            i = 0;
            while(parse->arg[i])
            {
                free(parse->arg[i]);
                i++;
            }
            free(parse->arg);
        }
        while(parse->rdr)
        {
            if(parse->rdr->value)
                free(parse->rdr->value);
            parse->rdr = parse->rdr->next;
        }
        tmp = parse->next;
        free(parse);
        parse = tmp;
    }
    free(parse);
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
    //signal(SIGINT, my_handler);
    while(1)
    {
        str = readline("minishell >$ ");
        if (str[0] != '\0')
        {
            lexer = init_lexer(str, lexer);
			token = NULL;
            while ((tmp = get_next_token(lexer)) != NULL && !lexer->flg_error)
			{
				add_back(&token, tmp);
                tmp = NULL;
			}
			// tmp = token;
			// int i = 0;
			// while(tmp)
			// {
			// 	printf("%d |%s|\n", i,tmp->value);
			// 	i++;
			// 	tmp = tmp->next;
			// }
            if ((token) != NULL)
                parse = init_parsing(&token, lexer);
            if(!token && parse != NULL)
            {
                free(parse->cmd);
                parse->cmd = NULL;
                free(parse->arg);
                parse->arg = NULL;
                free(parse->rdr);
                parse->rdr = NULL;
            }
            // t_parse *tmp1 = parse;
            // if (lexer->flg_error == 0 && parse != NULL)
            // {
            //     while(tmp1)
            //     {
            //         if (tmp1->cmd != NULL)
            //         {
            //             printf("cmd = %s\n", tmp1->cmd);
            //             free(tmp1->cmd);
            //         }
            //         if (tmp1->arg != NULL)
            //         {
            //             int i = 0;
            //             while(tmp1->arg[i])
            //             {
            //                 printf("arg = %s\n", tmp1->arg[i]);
            //                 i++;
            //             }
            //         }
            //         if (tmp1->rdr != NULL)
            //         {
            //             t_rdr *r = tmp1->rdr;
            //             while(r)
            //             {
            //                 printf("rdr->type = |%d|, rdr->value = |%s|\t, flg_error = |%d|\n", r->type, r->value, r->herdoc);
            //                 r = r->next;
            //             }
            //         }
            //         printf("-----------------------\n");
            //         tmp1 = tmp1->next;
					
            //     }
            // }
            if (lexer->flg_error == 1)
            {
                write(2, "syntax_error\n", 14);
                //g_exitm = 255;
            }
            if (parse != NULL)
                herdoc_handler(parse);
			if (!lexer->flg_error && parse != NULL)
				rdr_create_files(parse);
            if (ft_strlen(str) > 0)
                add_history(str);
            if (parse != NULL)
                execution(parse, &env_list);
            tmp = token;
            while(tmp)
            {
                token = token->next;
                free(tmp->value);
                free(tmp);
                tmp = token;
            }
            ft_free_list(parse);
            // free(lexer);
        }
        free(str);
    }
    return (0);
}
