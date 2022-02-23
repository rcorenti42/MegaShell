/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcorenti <rcorenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 22:08:41 by rcorenti          #+#    #+#             */
/*   Updated: 2022/02/23 22:12:24 by rcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_loop(char *line, char *str)
{
	line = readline("> ");
	if (!line)
	{
		ft_putstr_fd("bash: warning: here-document at ", STDERR);
		ft_putstr_fd("line 1 delimited by end-of-file (wanted `", STDERR);
		ft_putstr_fd(str, STDERR);
		ft_putendl_fd("')", STDERR);
		return (ERROR);
	}
	if (!ft_strcmp(line, str))
		return (ERROR);
	return (SUCCESS);
}

int	ft_heredoc(char *str)
{
	char	*line;
	int		fd[2];

	pipe(fd);
	line = NULL;
	rl_outstream = stderr;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &handler);
	while (1)
	{
		if (heredoc_loop(line, str) == ERROR)
			break ;
		ft_putendl_fd(line, fd[1]);
		line = ft_memdel(line);
	}
	line = ft_memdel(line);
	if (dup2(fd[0], STDIN) == -1)
		return (ERROR);
	if (fd[0] > 0)
		if (close(fd[0]) == -1)
			return (ERROR);
	if (fd[1] > 0)
		if (close(fd[1]) == -1)
			return (ERROR);
	return (SUCCESS);
}
