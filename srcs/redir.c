/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcorenti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 03:34:59 by rcorenti          #+#    #+#             */
/*   Updated: 2022/02/16 15:03:35 by rcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_pipe(t_shell *shell)
{
	pid_t	pid;
	int		fd[2];

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		if (fd[1] > 0)
			close(fd[1]);
		dup2(fd[0], STDIN);
		shell->redir.in_pipe = fd[1];
		shell->redir.pid = -1;
		return (1);
	}
	else
	{
		if (fd[0] > 0)
			close(fd[0]);
		dup2(fd[1], STDOUT);
		shell->redir.out_pipe = fd[0];
		shell->redir.pid = pid;
		return (2);
	}
}

static int	ft_input(t_shell *shell, t_command *cmd)
{
	if (shell->redir.in)
		close(shell->redir.in);
	shell->redir.in = open(cmd->command[0]->str, O_RDONLY, S_IRWXU);
	if (shell->redir.in == -1)
	{
		ft_putstr_fd("bash: ", STDERR);
		ft_putstr_fd(cmd->command[0]->str, STDERR);
		ft_putendl_fd(": No such file or directory", STDERR);
		shell->ret = 1;
		return (-1);
	}
	dup2(shell->redir.in, STDIN);
	return (0);
}

int			redir(t_shell *shell, t_command *cmd, int type)
{
	if (type == PIPE)
		return (ft_pipe(shell));
	else if (type == INPUT)
		return (ft_input(shell, cmd));
	else
	{
			if (shell->redir.out > 0)
				close(shell->redir.out);
			if (type == REDIR)
				shell->redir.out = open(cmd->command[0]->str, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
			else
				shell->redir.out = open(cmd->command[0]->str, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
			if (shell->redir.out == -1)
			{
				ft_putstr_fd("bash: ", STDERR);
				ft_putstr_fd(cmd->command[0]->str, STDERR);
				ft_putendl_fd(": No such file or directory", STDERR);
				shell->ret = 1;
				return (-1);
			}
			dup2(shell->redir.out, STDOUT);
	}
	return (0);
}
