/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcorenti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:33:09 by rcorenti          #+#    #+#             */
/*   Updated: 2022/02/16 15:10:23 by rcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_error(char *arg)
{
	ft_putstr_fd("bash: ", STDERR);
	ft_putstr_fd(arg, STDERR);
	ft_putendl_fd(": command not found", STDERR);
}

static int	if_pipe(t_command *cmd)
{
	while (cmd)
	{
		if (cmd->type == PIPE)
			return (1);
		cmd = cmd->next;
	}
	return (0);
}

static void	executor(t_shell *shell, t_command *cmd)
{
	if (ft_strcmp(cmd->command[0]->str, "exit") && !if_pipe(cmd))
		ft_exit(shell, cmd);
	else if (is_builtin(cmd))
		builtin_exe(shell, cmd);
	else
		bin_exe(shell, cmd);
	if (shell->redir.in_pipe > 0)
		close(shell->redir.in_pipe);
	if (shell->redir.out_pipe > 0)
		close(shell->redir.out_pipe);
	shell->redir.in_pipe = -1;
	shell->redir.out_pipe = -1;
}

void		execution(t_shell *shell ,t_command *cmd_prev, t_command *cmd)
{
	int	pipe;

	pipe = 0;
	if (cmd_prev)
	{
		if (cmd_prev->type == REDIR || cmd_prev->type == APPEND ||
				cmd_prev->type == INPUT || cmd_prev->type == PIPE)
			pipe = redir(shell, cmd, cmd_prev->type);
			if (pipe < 0)
				return ;
	}
	if (cmd)
	{
		if (cmd->next)
		{
			if (cmd->next->next && !pipe)
				execution(shell, cmd->next, cmd->next->next);
		}
	}
	if (cmd_prev)
	{
		if (cmd || cmd_prev->type == PIPE)
			executor(shell, cmd);
	}
	else
		executor(shell, cmd);
}
