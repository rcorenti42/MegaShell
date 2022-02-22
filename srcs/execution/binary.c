/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcorenti <rcorenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 11:26:41 by rcorenti          #+#    #+#             */
/*   Updated: 2022/02/22 03:43:30 by rcorenti         ###   ########.fr       */
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
	char	**tenv;

	shell->ret = 0;
	env = shell->env;
	tenv = tenv_to_tab(env);
	if (!tenv)
		return (ERROR);
	path = get_path(shell, cmd);
	if (!path)
	{
		free_tab(tenv);
		return (ERROR);
	}
	else if (!ft_strcmp(path, ""))
	{
		shell->ret = 127;
		exec_error(cmd->args[0]);
		free_tab(tenv);
		path = ft_memdel(path);
		return (SUCCESS);
	}
	if (execve(path, cmd->args, tenv) == -1)
		return (ERROR);
	free_tab(tenv);
	path = ft_memdel(path);
	return (SUCCESS);
}

int    bin_exe_fork(t_shell *shell, t_final_command *cmd)
{
	char	*path;
	int	status;
	t_env	*env;

	shell->ret = 0;
	env = shell->env;
	path = get_path(shell, cmd);
	if (!path)
		return (ERROR);
	else if (!ft_strcmp(path, ""))
	{
		path = ft_memdel(path);
		exec_error(cmd->args[0]);
		shell->ret = 127;
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
		if (execve(path, cmd->args, tenv_to_tab(env)) == -1)
			return (ERROR);
	}
	path = ft_memdel(path);
	return (SUCCESS);
}
