/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcorenti <rcorenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 22:08:41 by rcorenti          #+#    #+#             */
/*   Updated: 2022/02/26 22:49:19 by rcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_handler(int code)
{
	if (code == SIGINT)
	{
		g_signal = 130;
		write(STDERR, "\n", 1);
		rl_redisplay();
		close(STDIN);
	}
}

int	heredoc_loop(char **line, char *str)
{
	*line = readline("> ");
	if (!(*line))
	{
		if (!g_signal)
		{
			ft_putstr_fd("bash: warning: here-document at ", STDERR);
			ft_putstr_fd("line 1 delimited by end-of-file (wanted `", STDERR);
			ft_putstr_fd(str, STDERR);
			ft_putendl_fd("')", STDERR);
		}
		return (ERROR);
	}
	if (!ft_strcmp(*line, str))
		return (ERROR);
	return (SUCCESS);
}

int	ft_heredoc(char *str)
{
	char	*line;
	int		fd[2];

	pipe(fd);
	rl_outstream = stderr;
	signal(SIGINT, &heredoc_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		if (heredoc_loop(&line, str) == ERROR)
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
