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

void    bin_exe(t_shell *shell, t_command *cmd)
{
	char	*path;
	int	status;
	t_env	*env;

	env = shell->env;
	path = get_path(shell, cmd);
	if (!path)
	{
		exec_error(cmd->args[0]);
		return (SUCCESS);
	}
	shell->redir->pid = fork();
	if (pid == -1)
	{
		path = ft_memdel(path);
		return (ERROR);
	}
	else if (pid == 0)
	{
		if (!path)
			path = ft_strdup(cmd->args[0]);
		if (execve(path, cmd->args, tenv_to_tab(env)))
		{
			if (path)
			{
				if (ft_strcmp(path, cmd->args[0]))
					path = ft_memdel(path);
			}
			return (ERROR);
		}
		if (path)
			path = ft_memdel(path);
	}
	else
	{
		if (path)
			path = ft_memdel(path);
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	}
	return (SUCCESS);
}
