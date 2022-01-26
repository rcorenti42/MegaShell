/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcorenti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 16:18:24 by rcorenti          #+#    #+#             */
/*   Updated: 2022/01/26 07:05:31 by rcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <limits.h>

# define SUCCESS 0
# define ERROR 1

# define STDIN 0
# define STDOUT 1
# define STDERR 2

typedef struct		s_expand
{
	char		*arg;
	int		i;
	int		j;
}			t_expend;

typedef struct		s_token
{
	char		*val;
	int		type;
	struct s_token	*next;
}			t_token;

typedef struct		s_env
{
	char		*val;
	struct s_env	*next;
}			t_env;

typedef struct		s_shell
{
	int		in;
	int		out;
	int		ret;
	int		exit;
	t_env		*env;
}			t_shell;

//PARSING

//EXECUTION

//ENV

//BUILTINS

//TOOLS

#endif
