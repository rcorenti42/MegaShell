/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcorenti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 03:34:59 by rcorenti          #+#    #+#             */
/*   Updated: 2022/02/17 08:35:38 by rcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_heredoc(t_shell *shell, t_command *cmd)
{
	
}

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
	shell->redir.in = open(cmd->redir_in[i]->redir, O_RDONLY, S_IRWXU);
	if (shell->redir.in == -1)
	{
		ft_putstr_fd("bash: ", STDERR);
		ft_putstr_fd(cmd->args[0], STDERR);
		ft_putendl_fd(": No such file or directory", STDERR);
		shell->ret = 1;
		return (ERROR);
	}
	dup2(shell->redir.in, STDIN);
	return (SUCCESS);
}

int			redir(t_shell *shell, t_command *cmd)
{
	int		i;

	i = 0;
	while (cmd->redir_in[i])
	{
		if (cmd->redir_in[i]->type == simple)
		{
			if (ft_input(shell, cmd) == ERROR)
				return (ERROR);
		}
		else
		{
			if (ft_heredoc(shell, cmd) == ERROR)
				return (ERROR);
		}
		i++;
	}
	i = 0;
	while (cmd->redir_out[i])
	{
		if (shell->redir.out > 0)
			close(shell->redir.out);
		if (cmd->redir_out[i]->type == simple)
			shell->redir.out = open(cmd->redir_out[i]->redir, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
		else
			shell->redir.out = open(cmd->redir_out[i]->redir, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
		if (shell->redir.out == -1)
		{
			ft_putstr_fd("bash: ", STDERR);
			ft_putstr_fd(cmd->redir_out[i]->redir, STDERR);
			ft_putendl_fd(": No such file or directory", STDERR);
			shell->ret = 1;
			return (ERROR);
		}
		dup2(shell->redir.out, STDOUT)
		i++;
	}
	return (SUCCESS);
}


















