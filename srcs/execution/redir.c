/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcorenti <rcorenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 03:34:59 by rcorenti          #+#    #+#             */
/*   Updated: 2022/02/27 07:56:30 by sobouatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	error_redir(t_shell *shell, char *str)
{
	ft_putstr_fd("megashell: ", STDERR);
	ft_putstr_fd(str, STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putendl_fd(strerror(errno), STDERR);
	shell->exec = 0;
	g_signal = 1;
}

int	ft_pipe(t_shell *shell)
{
	int		fd[2];

	pipe(fd);
	(shell->redir.pid_pipe)[++shell->redir.i_pipe] = fork();
	if (shell->redir.pid_pipe[shell->redir.i_pipe] == -1)
		return (-1);
	else if (shell->redir.pid_pipe[shell->redir.i_pipe] == 0)
	{
		if ((fd[0] > 0 && close(fd[0]) == -1)
			|| dup2(fd[1], STDOUT) == -1)
			return (-1);
		shell->redir.pipe[1] = fd[1];
		shell->redir.out_pipe = fd[1];
		shell->redir.pid = -1;
		shell->parent = 0;
		return (1);
	}
	else
	{
		if ((fd[1] > 0 && close(fd[1]) == -1) || (dup2(fd[0], STDIN) == -1))
			return (-1);
		shell->redir.in_pipe = fd[0];
		shell->redir.pipe[0] = fd[0];
		return (2);
	}
}

static int	ft_input(t_shell *shell, char *str)
{
	if (shell->redir.in_fd > 0)
	{
		if (close(shell->redir.in_fd) == -1)
			return (ERROR);
	}
	shell->redir.in_fd = open(str, O_RDONLY);
	if (shell->redir.in_fd == -1)
	{
		error_redir(shell, str);
		return (SUCCESS);
	}
	if (dup2(shell->redir.in_fd, STDIN) == -1)
		return (ERROR);
	return (SUCCESS);
}

static int	out_redir(t_shell *shell, t_final_command *cmd)
{
	int	i;

	i = -1;
	while (cmd->redir_out[++i].redir && shell->exec)
	{
		if (shell->redir.out_fd > 0)
			if (close(shell->redir.out_fd) == -1)
				return (ERROR);
		if (cmd->redir_out[i].type == simple)
			shell->redir.out_fd = open(cmd->redir_out[i].redir,
					O_CREAT | O_WRONLY | O_TRUNC,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		else
			shell->redir.out_fd = open(cmd->redir_out[i].redir,
					O_CREAT | O_WRONLY | O_APPEND,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if (shell->redir.out_fd == -1)
		{
			error_redir(shell, cmd->redir_out[i].redir);
			return (SUCCESS);
		}
		if (dup2(shell->redir.out_fd, STDOUT) == -1)
			return (ERROR);
	}
	return (SUCCESS);
}

int	redir(t_shell *shell, t_final_command *cmd)
{
	int		i;

	i = 0;
	while (cmd->redir_in[i].redir && shell->exec)
	{
		if (cmd->redir_in[i].type == simple)
		{
			if (ft_input(shell, cmd->redir_in[i].redir) == ERROR)
				return (ERROR);
		}
		else
		{
			if (ft_heredoc(cmd->redir_in[i].redir) == ERROR)
				return (ERROR);
		}
		i++;
	}
	return (out_redir(shell, cmd));
}
