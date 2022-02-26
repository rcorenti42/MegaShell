/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcorenti <rcorenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 11:26:41 by rcorenti          #+#    #+#             */
/*   Updated: 2022/02/26 22:04:35 by rcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_error(char *arg)
{
	g_signal = 127;
	ft_putstr_fd("megashell: ", STDERR);
	ft_putstr_fd(arg, STDERR);
	ft_putendl_fd(": command not found", STDERR);
}

static int	bin_exe_quit(char **tenv, char *path, char *arg)
{
	exec_error(arg);
	free_tab(tenv);
	path = ft_memdel(path);
	return (SUCCESS);
}

static int	bin_execution(char *path, char **args, char **tenv)
{
	if (execve(path, args, tenv) == -1)
	{
		free_tab(tenv);
		path = ft_memdel(path);
		return (ERROR);
	}
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
		path = ft_memdel(path);
	if (!tenv)
		return (ERROR);
	else if (!ft_strcmp(path, ""))
		return (bin_exe_quit(tenv, path, cmd->args[0]));
	if (bin_execution(path, cmd->args, tenv) == ERROR)
	{
		if (shell->redir.out > 0)
			close(shell->redir.out);
		if (shell->redir.in > 0)
			close(shell->redir.in);
		return (ERROR);
	}
	return (SUCCESS);
}

int	bin_exe_fork(t_shell *shell, t_final_command *cmd)
{
	shell->redir.pid = fork();
	if (shell->redir.pid == -1)
		return (ERROR);
	else if (shell->redir.pid == 0)
	{
		shell->parent = 0;
		return (bin_exe(shell, cmd));
	}
	return (SUCCESS);
}
