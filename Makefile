# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/26 19:30:34 by ddecourt          #+#    #+#              #
#    Updated: 2021/11/09 11:33:52 by ddecourt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	srcs/minishell.c \

OBJS = ${SRCS:.c=.o}

NAME = minishell

HEADER = inc/minishell.h

CC = clang

CFLAGS = -Wall -Werror -Wextra -g #-fsanitize=address 
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
