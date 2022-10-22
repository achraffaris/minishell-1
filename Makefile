src = *.c ./libft/*.c ./execution/*/*.c ./execution/*/*/*.c ./execution/*.c
minishell = minishell
FLAGS =  -lreadline -Wall -Wextra -Werror -fsanitize= -g3
CC = cc

all : minishell
	
$(minishell): $(src)	
	@$(CC) $(FLAGS) $(RDLINE) $(src) -o minishell
	@tput setaf 2; echo "MINISHELL IS READY"

clean :
	@rm -f minishell
	@tput setaf 1; echo "CLEAN COMPLET"

fclean : clean

re: fclean all