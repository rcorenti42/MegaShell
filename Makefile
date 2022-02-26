# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/16 11:41:35 by rcorenti          #+#    #+#              #
#    Updated: 2022/02/26 03:00:05 by sobouatt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

INC = include

SRCS = srcs

PARS = parser

EXEC = execution

SRCS1 = main.c \
	main2.c \
	utils.c \
	utils_two.c \
	display_args.c \
	custom_frees.c 

SRCS2 = lexer.c \
	lexer_utils.c \
	list.c \
	first_pass.c \
	first_pass2.c \
	second_pass.c \
	expand.c \
	expand_unquoted.c \
	expand_utils.c \
	expand_utils2.c \
	remove_quotes.c \
	split_cmd.c \
	fill_final.c \
	fill_final2.c \
	ft_itoa.c \
	get_token.c \
	trash.c \
	lexer2.c

SRCS3 = redir.c \
	fd.c \
	init_env.c \
	builtins.c \
	binary.c \
	ft_cd.c \
	ft_echo.c \
	ft_env.c \
	ft_export.c \
	ft_pwd.c \
	ft_unset.c \
	ft_exit.c \
	get_val_env.c \
	get_path.c \
	execution.c \
	ft_export_utils.c \
	heredoc.c \
	ft_calloc.c

PARS = ${addsuffix /parser,${SRCS}}

EXEC = ${addsuffix /execution,${SRCS}}

LIBFT = libft/libft.a

CC = clang

CFLAGS = -g -Wall -Wextra -Werror -MMD
 
OBJS = ${addprefix ${SRCS}/,${SRCS1:.c=.o}} ${addprefix ${PARS}/,${SRCS2:.c=.o}} ${addprefix ${EXEC}/,${SRCS3:.c=.o}}
DEPS = ${OBJS:%.o=%.d}

all: $(NAME)
	@echo "  __  __                      _          _ _   ________     __  __                      _          _ _   ________    __  __                      _          _ _   ________     __  __                      _          _ _   ________   "
	@echo " |  \/  |                    | |        | | | /  ____  \   |  \/  |                    | |        | | | /  ____  \  |  \/  |                    | |        | | | /  ____  \   |  \/  |                    | |        | | | /  ____  \  "
	@echo " | \  / | ___  __ _  __ _ ___| |__   ___| | |/  / ___|  \  | \  / | ___  __ _  __ _ ___| |__   ___| | |/  / ___|  \ | \  / | ___  __ _  __ _ ___| |__   ___| | |/  / ___|  \  | \  / | ___  __ _  __ _ ___| |__   ___| | |/  / ___|  \ "
	@echo " | |\/| |/ _ \/ _  |/ _  / __|  _ \ / _ \ | |  | |       | | |\/| |/ _ \/ _  |/ _  / __|  _ \ / _ \ | |  | |       || |\/| |/ _ \/ _  |/ _  / __|  _ \ / _ \ | |  | |       | | |\/| |/ _ \/ _  |/ _  / __|  _ \ / _ \ | |  | |       |"
	@echo " | |  | |  __/ (_| | (_| \__ \ | | |  __/ | |  | |___    | | |  | |  __/ (_| | (_| \__ \ | | |  __/ | |  | |___    || |  | |  __/ (_| | (_| \__ \ | | |  __/ | |  | |___    | | |  | |  __/ (_| | (_| \__ \ | | |  __/ | |  | |___    |"
	@echo " |_|  |_|\___|\__, |\__,_|___/_| |_|\___|_|_|\  \____|  /  |_|  |_|\___|\__, |\__,_|___/_| |_|\___|_|_|\  \____|  / |_|  |_|\___|\__, |\__,_|___/_| |_|\___|_|_|\  \____|  /  |_|  |_|\___|\__, |\__,_|___/_| |_|\___|_|_|\  \____|  / "
	@echo "               __/ |                          \________/                 __/ |                          \________/                __/ |                          \________/                 __/ |                          \________/  "
	@echo "              |___/                                                     |___/                                                    |___/                                                     |___/                                       "


$(NAME): $(OBJS) ${LIBFT} ${INC}
	$(CC) $(CFLAGS) ${OBJS} -lreadline -o $(NAME) ${LIBFT}

-include ${DEPS}
.c.o:
	$(CC) $(CFLAGS) -I $(INC) -c $< -o ${<:.c=.o}


$(LIBFT):
	make -C ./libft

clean:
	@rm -f $(OBJS)
	@rm -f $(DEPS)
	@rm -rf $(LIBFT)
	@make clean -C libft

fclean: clean
	@rm -f $(NAME)

re: fclean all

SHELL:=/bin/bash

val: 
	@make
	@make clean
	@source ./home.sh
	@valshell


.PHONY: all clean fclean re val reval
