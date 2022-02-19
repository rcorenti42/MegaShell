/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcorenti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:33:09 by rcorenti          #+#    #+#             */
/*   Updated: 2022/02/18 14:25:07 by rcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_error(char *arg)
{
	ft_putstr_fd("bash: ", STDERR);
	ft_putstr_fd(arg, STDERR);
	ft_putendl_fd(": command not found", STDERR);
}

static void	executor(t_shell *shell, t_final_command *cmd)
{
	if (!ft_strcmp(cmd->args[0], "exit") && shell->redir.pipe_nbr == 0)
		ft_exit(shell, cmd);
	else if (is_builtin(cmd))
		builtin_exe(shell, cmd);
	else if (shell->parent)
		bin_exe_fork(shell, cmd);
	else
		bin_exe(shell, cmd);
}

void		execution(t_shell *shell, t_final_command *cmd)
{
	int	child;

	child = 0;
	if (cmd->next)
	{
		if (shell->redir.in_pipe > 0)
			close(shell->redir.in_pipe);
		if (shell->redir.out_pipe > 0)
			close(shell->redir.out_pipe);
		shell->redir.in_pipe = -1;
		shell->redir.out_pipe = -1;
		child = ft_pipe(shell);
		if (child < 0)
			return ;
	}
	if (redir(shell, cmd) == ERROR)
		return ;
	if (child == 2)
		execution(shell, cmd->next);
	else
		executor(shell, cmd);
}
