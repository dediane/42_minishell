# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/26 19:30:34 by ddecourt          #+#    #+#              #
#    Updated: 2022/01/21 10:50:33 by ddecourt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	srcs/minishell.c \
		srcs/exec/exec.c \
		srcs/exec/exec2.c \
		srcs/exec/exec_utils.c \
		srcs/exec/built_in.c \
		srcs/exec/redirection.c \
		srcs/exec/heredoc.c \
		srcs/exec/heredoc2.c \
		srcs/exec/fd.c \
		srcs/parsing/parsing.c \
		srcs/parsing/parsing2.c \
		srcs/parsing/parsing3.c \
		srcs/parsing/parsing_utils.c \
		srcs/parsing/parsing_tabs.c \
		srcs/parsing/parsing_quote.c \
		srcs/parsing/parsing_quote_2.c \
		srcs/parsing/add_file.c \
		srcs/parsing/stack_alloc.c \
		srcs/parsing/check_redoc.c \
		srcs/parsing/variable_env.c \
		srcs/parsing/variable_env2.c \
		srcs/parsing/env_liste.c \
		srcs/parsing/ft_free.c \
		srcs/parsing/parsing_dolar.c \
		srcs/built_in/env.c \
		srcs/built_in/pwd.c \
		srcs/built_in/exit.c \
		srcs/built_in/cd.c \
		srcs/built_in/echo.c \
		srcs/built_in/export.c \
		srcs/built_in/export2.c \
		srcs/built_in/unset.c \
		srcs/signal/signal.c \

OBJS = ${SRCS:.c=.o}

NAME = minishell

HEADER = inc/minishell.h

CC = clang

CFLAGS = -Wall -Werror -Wextra 
RM = rm -f

.c.o:
	${CC} -c ${CFLAGS} -I -L./libft/ -o $@ $<

$(NAME):    ${OBJS}
		make -C libft
		${CC} ${CFLAGS} ${OBJS} -I -L./libft/ -lreadline -lm ./libft/libft.a -o ${NAME}

all:	${NAME}

clean:
	make clean -C libft
	${RM} ${OBJS}

fclean: clean
	make fclean -C libft
	${RM} ${NAME}

re:	 fclean all

.PHONY: all clean fclean re
