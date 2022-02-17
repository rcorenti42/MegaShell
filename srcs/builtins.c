/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcorenti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 17:33:13 by rcorenti          #+#    #+#             */
/*   Updated: 2022/02/17 05:07:09 by rcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_command *cmd)
{
	char	*str;

	str = cmd->args[0];
	if (!ft_strcmp(str, "echo") || !ft_strcmp(str, "cd")
		|| !ft_strcmp(str, "pwd") || !ft_strcmp(str, "export")
		|| !ft_strcmp(str, "unset") || !ft_strcmp(str, "env")
		|| !ft_strcmp(str, "exit"))
		return (1);
	return (0);
}

int	builtin_exe(t_shell *shell, t_command *cmd)
{
	char	*str;
	int		ret;

	ret = SUCCESS;
	str = cmd->args[0];
	if (!ft_strcmp(str, "echo"))
		ft_echo(shell, cmd);
	if (!ft_strcmp(str, "cd"))
		ret = ft_cd(shell, cmd);
	if (!ft_strcmp(str, "pwd"))
		ret = ft_pwd();
	if (!ft_strcmp(str, "export"))
		ret = ft_export(shell, cmd);
	if (!ft_strcmp(str, "unset"))
		ft_unset(shell, cmd);
	if (!ft_strcmp(str, "env"))
		ft_env(shell);
	if (!ft_strcmp(str, "exit"))
		ft_exit(shell, cmd);
	return (ret);
}
