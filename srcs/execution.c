/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcorenti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:33:09 by rcorenti          #+#    #+#             */
/*   Updated: 2022/02/17 07:15:07 by rcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_error(char *arg)
{
	ft_putstr_fd("bash: ", STDERR);
	ft_putstr_fd(arg, STDERR);
	ft_putendl_fd(": command not found", STDERR);
}

static void	executor(t_shell *shell, t_command *cmd)
{
	if (ft_strcmp(cmd->args, "exit") && shell->redir->pipe_nbr)
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

void		execution(t_shell *shell, t_command *cmd, int first)
{
	if (!first)
	{
		if (ft_pipe(shell) < 0)
			return ;
	}
	if (redir(shell, cmd) == ERROR)
		return ;
	else
		executor(shell, cmd);
}
