# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/10 18:07:38 by ebondi            #+#    #+#              #
#    Updated: 2022/10/14 17:57:01 by atarsi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#READLINE_FLAGS = -L/usr/include -lreadline -L$$HOME/.brew/opt/readline/lib -I $$HOME/.brew/opt/readline/include/readline
READLINE_FLAGS = -L/usr/include -lreadline -lcurses -L /Users/$(USER)/.brew/opt/readline/lib -I /Users/$(USER)/.brew/opt/readline/include
NAME = minishell
FLAGS = -Wall -Werror -Wextra
OBJS = minishell.c get_command.c expand_env.c ft_parser.c export.c
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
	@rm -f minishell
	@make fclean -C libft
	@printf "\033[1;91mRemoving objects...\n"

re: fclean all
	@make fclean -C libft
	@make -C libft
	
vai: re
	@./$(NAME)

leaks:
	@leaks --atExit -- ./$(NAME)

.PHONY:	all clean fclean re bonus