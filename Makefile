# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/10 18:07:38 by ebondi            #+#    #+#              #
#    Updated: 2022/10/11 11:30:06 by ebondi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

READLINE_FLAGS = -L/usr/include -lreadline -L$$HOME/.brew/opt/readline/lib -I $$HOME/.brew/opt/readline/include/readline
NAME = minishell
FLAGS = -Wall -Werror -Wextra
OBJS = minishell.c
LIBFT = libft/libft.a

$(NAME):$(OBJS)
		@gcc $(FLAGS) $(OBJS) -o $(NAME) $(LIBFT) $(READLINE_FLAGS)
		@printf "\033[1;35mMinishell compiled!!\n"

all: $(NAME)

bonus: $(NAME)

clean:

fclean:
	@rm -f minishell
	@printf "\033[1;91mRemoving objects...\n"

re: fclean all

	