# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/16 19:30:49 by jtaylor           #+#    #+#              #
#    Updated: 2019/08/22 15:34:56 by jtaylor          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_select

FLAGS = -Wall -Wextra -Werror -I ./libft/includes

DEBUG_FLAG = -g3

SRC =	ft_select_main.c \
		ft_select_init_termcaps.c \
		ft_select_signal.c \
		ft_select_assorted_func.c \
		ft_select_init_argument_list.c \
		ft_select_handle_key_press.c


.PHONY = all clean fclean re

all : $(NAME)

$(NAME) :
	@make -C ./libft
	@echo "\tBuilding $(NAME) executable\n"
	@gcc $(FLAGS) $(SRC) -ltermcap -I ./includes -I ./libft/includes ./libft/libft.a ./libft/ft_printf/libftprintf.a -o $(NAME)

debug :
	@make debug -C ./libft
	@echo "\tBuilding $(NAME) debug executable\n"
	@gcc $(FLAGS) $(SRC) $(DEBUG_FLAG) -ltermcap -I ./includes ./libft/libft.a ./libft/ft_printf/libftprintf.a -o $(NAME)

clean :
	@make -C libft clean

fclean : clean
	@echo "\tRemoving $(NAME) Executable\n"
	@rm -rf $(NAME)
	@rm -rf $(NAME).dSYM
	@make -C libft fclean

re : fclean all

r :
	rm $(NAME);
	make all
