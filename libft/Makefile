# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rcorenti <rcorenti@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/28 02:14:43 by rcorenti          #+#    #+#              #
#    Updated: 2022/02/20 16:50:14 by rcorenti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FLAGS = -Wall -Wextra -Werror

HEADER = include

DIR_O = ft_memdel.c \
	ft_putendl_fd.c \
	ft_putstr_fd.c \
	ft_strcat.c \
	ft_strcmp.c \
	ft_strlen.c \
	ft_strdup.c \
	ft_memcpy.c \
	ft_split.c \
	ft_strncmp.c \
	ft_atoi.c \
	ft_isspace.c \
	ft_isalpha.c \
	ft_isalnum.c \

OBJS = ${addprefix srcs/,${DIR_O:.c=.o}}

CC = clang

.c.o:
	${CC} ${FLAGS} -I ${HEADER} -c $< -o ${<:.c=.o}

$(NAME): ${OBJS} ${HEADER}
	ar rcs ${NAME} ${OBJS}

all:	${NAME}

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
