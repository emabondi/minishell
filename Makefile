# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/10 18:07:38 by ebondi            #+#    #+#              #
#    Updated: 2022/10/10 18:56:32 by ebondi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

READLINE_FLAGS = -L/usr/include -lreadline -L$$HOME/.brew/opt/readline/lib -I $$HOME/.brew/opt/readline/include/readline
NAME = minishell
FLAGS = -Wall -Werror -Wextra
OBJS = minishell.c

$(NAME):$(OBJS)
		@gcc $(FLAGS) $(OBJS) -o $(NAME)
		@printf "\033[1;35mMinishell compiled!!\n"

all: $(NAME)

bonus:

clean:

fclean:
	@rm -f minishell
	@printf "\033[1;91mRemoving objects...\n"

re: fclean all

	