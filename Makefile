# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/10 18:07:38 by ebondi            #+#    #+#              #
#    Updated: 2022/10/30 18:13:44 by ebondi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#READLINE_FLAGS = -L/usr/include -lreadline -L$$HOME/.brew/opt/readline/lib -I $$HOME/.brew/opt/readline/include/readline
READLINE_FLAGS = -L/usr/include -lreadline -lcurses -L /Users/$(USER)/.brew/opt/readline/lib -I /Users/$(USER)/.brew/opt/readline/include
NAME = minishell
FLAGS = -Wall -Werror -Wextra
OBJS = minishell.c command.c expand_env.c ft_parser.c export.c utils.c smart_split.c builtins.c external_command.c unset.c export2.c
LIBFT = libft/libft.a

$(NAME):$(OBJS)
		@make -C libft
		@gcc $(FLAGS) $(OBJS) -o $(NAME) $(LIBFT) $(READLINE_FLAGS)
		@printf "\033[1;35mMinishell compiled!!\e[0m\n"

all: $(NAME)

bonus: $(NAME)

clean:
	@make clean -C libft

fclean:
	@rm -f minishell tests
	@make fclean -C libft
	@printf "\033[1;91mRemoving objects...\n"

re: relibft fclean all

relibft:
		@make fclean -C libft
		@make -C libft
vai: re
	@./$(NAME)

leaks:
	@leaks --atExit -- ./$(NAME)

test: test.c re
	@gcc test.c libft/libft.a -o tests
	@./tests | ./minishell

.PHONY:	all clean fclean re bonus vai leaks test relibft