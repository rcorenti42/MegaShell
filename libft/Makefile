# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rcorenti <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/25 21:57:34 by rcorenti          #+#    #+#              #
#    Updated: 2022/01/26 02:28:50 by rcorenti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FLAGS = -Wall -Wextra -Werror

DIR_S = srcs
HEADER = includes
DIR_O = ft_memdel.c \
	ft_putendl_fd.c \
	ft_putstr_fd.c \
	ft_strcat.c \
	ft_strcmp.c \
	ft_strlen.c \
	ft_strdup.c

OBJ = $(SRC:.c=.o)

SRCS = $(addprefix $(DIR_S)/, $(SRC))
OBJS = $(addprefix $(DIR_O)/, $(OBJ))

all: $(NAME)

$(NAME): $(OBJS)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)

$(DIR_O)/%.o: $(DIR_S)/%.c
	@mkdir -p $(DIR_O)
	@gcc $(FLAGS) -I $(HEADER) -o $a -c $<

clean:
	@rm -f $(OBJS)
	@rm -rf $(DIR_O)

fclean:
	clean
	@rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re
