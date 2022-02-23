/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcorenti <rcorenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 11:26:41 by rcorenti          #+#    #+#             */
/*   Updated: 2022/02/23 08:36:27 by rcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_error(char *arg)
{
	ft_putstr_fd("megashell: ", STDERR);
	ft_putstr_fd(arg, STDERR);
	ft_putendl_fd(": command not found", STDERR);
}

static int	bin_exe_quit(char **tenv, char *path, char *arg)
{
		g_signal = 127;
		exec_error(arg);
		free_tab(tenv);
		path = ft_memdel(path);
		return (SUCCESS);
}

int	bin_exe(t_shell *shell, t_final_command *cmd)
{
	char	*path;
	t_env	*env;
	char	**tenv;

	g_signal = 0;
	env = shell->env;
	path = get_path(shell, cmd);
	if (!path)
		return (ERROR);
	tenv = tenv_to_tab(env);
	if (!tenv)
		return (ERROR);
	else if (!ft_strcmp(path, ""))
		return (bin_exe_quit(tenv, path, cmd->args[0]));
	if (execve(path, cmd->args, tenv) == -1)
		return (ERROR);
	free_tab(tenv);
	path = ft_memdel(path);
	return (SUCCESS);
}



int	bin_exe_fork(t_shell *shell, t_final_command *cmd)
{
	//char	*path;
	//t_env	*env;
/*
	g_signal = 0;
	env = shell->env;
	path = get_path(shell, cmd);
	if (!path)
		return (ERROR);
	else if (!ft_strcmp(path, ""))
	{
		path = ft_memdel(path);
		exec_error(cmd->args[0]);
		g_signal = 127;
		return (SUCCESS);
	}*/
	shell->redir.pid = fork();
	if (shell->redir.pid == -1)
	{
		//path = ft_memdel(path);
		return (ERROR);
	}
	else if (shell->redir.pid == 0)
	{
		shell->parent = 0;

		return (bin_exe(shell, cmd));
		
		//if (!path)
		//	path = ft_strdup(cmd->args[0]);
		//if (execve(path, cmd->args, tenv_to_tab(env)) == -1)
		//	return (ERROR);
	}
	//path = ft_memdel(path);
	return (SUCCESS);
}
