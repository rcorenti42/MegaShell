/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcorenti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 11:26:41 by rcorenti          #+#    #+#             */
/*   Updated: 2022/02/17 08:02:50 by rcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_error(char *arg)
{
	ft_putstr_fd("megashell: ", STDERR);
	ft_putstr_fd(arg, STDERR);
	ft_putendl_fd(": command not found", STDERR);
}

int		bin_exe(t_shell *shell, t_final_command *cmd)
{
	char	*path;
	t_env	*env;

	env = shell->env;
	path = get_path(shell, cmd);
	if (!path)
		return (ERROR);
	else if (!ft_strcmp(path, ""))
	{
		exec_error(cmd->args[0]);
		return (SUCCESS);
	}
	execve(path, cmd->args, tenv_to_tab(env));
	path = ft_memdel(path);
	return (SUCCESS);
}

int    bin_exe_fork(t_shell *shell, t_final_command *cmd)
{
	char	*path;
	int	status;
	t_env	*env;

	env = shell->env;
	path = get_path(shell, cmd);
	if (!path)
		return (ERROR);
	else if (!ft_strcmp(path, ""))
	{
		path = ft_memdel(path);
		exec_error(cmd->args[0]);
		return (SUCCESS);
	}
	shell->redir.pid = fork();
	if (shell->redir.pid == -1)
	{
		path = ft_memdel(path);
		return (ERROR);
	}
	else if (shell->redir.pid == 0)
	{
		shell->parent = 0;
		if (!path)
			path = ft_strdup(cmd->args[0]);
		execve(path, cmd->args, tenv_to_tab(env));
	}
	path = ft_memdel(path);
	return (SUCCESS);
}
