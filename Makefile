# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rcorenti <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/26 06:37:14 by rcorenti          #+#    #+#              #
#    Updated: 2022/01/26 07:14:51 by rcorenti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = clang

FLAGS = -Wall -Wextra -Werror

HEADER = include

LIBFT = libft/libft.a

srcs = main.c

OBJS = ${addprefix srcs/,${srcs:.c=.o}}

.c.o :
	${CC} ${FLAGS} -I ${HEADER} -c $< -o ${<:.c=.o}

all: $(NAME)

$(NAME): $(OBJS) ${LIBFT} ${HEADER}
	${CC} ${FLAGS} ${OBJS} -lreadline -o ${NAME} ${LIBFT}

$(LIBFT):
	make -C ./libft

clean:
	@rm -f $(OBJS)
	@rm -rf $(LIBFT)
	@make clean -C libft

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PNONY: all clean fclean re
