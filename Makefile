# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sebferna <sebferna@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/07 12:47:50 by sebferna          #+#    #+#              #
#    Updated: 2024/12/04 18:32:33 by sebferna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

CFLAGS = -Wall -Werror -Wextra

SRC = src/minishell.c\
		src/mini_utils/builtins/cd.c\
		src/mini_utils/builtins/echo.c\
		src/mini_utils/builtins/envp.c\
		src/mini_utils/builtins/exit.c\
		src/mini_utils/builtins/pwd.c\
		src/mini_utils/builtins/unset.c\
		src/mini_utils/exec/error_msg.c\
		src/mini_utils/exec/ex_route.c\
		src/mini_utils/exec/executor.c\
		src/mini_utils/exec/pipe.c\
		src/mini_utils/exec/routes.c\
		src/mini_utils/free/free.c\
		src/mini_utils/free/free_all.c\
		src/mini_utils/parsing/expander.c\
		src/mini_utils/parsing/here_doc.c\
		src/mini_utils/parsing/lexer.c\
		src/mini_utils/parsing/parsing_utils.c\
		src/mini_utils/parsing/parsing.c\
		src/mini_utils/utilss/export.c\
		src/mini_utils/utilss/split_words.c\
		src/mini_utils/utilss/split_cmds.c\
		src/mini_utils/utilss/splits.c\
		src/mini_utils/utilss/utils.c\

LIBFT_DIR = ./libft

LIBFT = $(LIBFT_DIR)/libft.a

INC_SYS = -I /usr/include

LIB_SYS = -L /usr/lib/x86_64-linux-gnu -lreadline

OBJS = $(SRC:.c=.o)

all : $(NAME) $(LIBFT)

$(LIBFT) :
	@make -s -C $(LIBFT_DIR)

$(NAME) : $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(SRC) $(LIBFT) $(INC_SYS) $(LIB_SYS) -o $(NAME)

$(OBJS) : $(SRC)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -fr $(OBJS) $(OBJS_BONUS)
	@make clean -s -C $(LIBFT_DIR)

fclean: clean
	@rm -fr $(NAME)
	@make fclean -s -C $(LIBFT_DIR)

re: fclean all

.PHONY : all clean fclean re

