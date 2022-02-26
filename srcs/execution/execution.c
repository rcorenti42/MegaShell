/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcorenti <rcorenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:33:09 by rcorenti          #+#    #+#             */
/*   Updated: 2022/02/26 21:57:06 by rcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	executor(t_shell *shell, t_final_command *cmd)
{
	if (!cmd->args[0])
		return (SUCCESS);
	else if (!ft_strcmp(cmd->args[0], "exit") && shell->redir.pipe_nbr == 0)
	{
		ft_exit(shell, cmd);
		return (ERROR);
	}
	else if (is_builtin(cmd))
	{
		if (builtin_exe(shell, cmd) == ERROR)
			return (ERROR);
	}
	else if (shell->parent)
	{
		if (bin_exe_fork(shell, cmd) == ERROR)
			return (ERROR);
	}
	else if (bin_exe(shell, cmd) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

static int	exec_redir(t_shell *shell, t_final_command *cmd, int child)
{
	if (redir(shell, cmd) == ERROR)
		return (ERROR);
	if (!shell->exec)
		return (SUCCESS);
	if (child == 2)
	{
		if (execution(shell, cmd->next) == ERROR)
			return (ERROR);
	}
	else if (executor(shell, cmd) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	execution(t_shell *shell, t_final_command *cmd)
{
	int	child;

	child = 0;
	if (cmd->next)
	{
		if (shell->redir.in_pipe > 0)
		{
			if (close(shell->redir.in_pipe) == -1)
				return (ERROR);
		}
		if (shell->redir.out_pipe > 0)
		{
			if (close(shell->redir.out_pipe) == -1)
				return (ERROR);
		}
		shell->redir.in_pipe = -1;
		shell->redir.out_pipe = -1;
		child = ft_pipe(shell);
		if (child < 0)
			return (ERROR);
	}
	return (exec_redir(shell, cmd, child));
}
