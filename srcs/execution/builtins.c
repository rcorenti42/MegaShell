/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcorenti <rcorenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 17:33:13 by rcorenti          #+#    #+#             */
/*   Updated: 2022/02/22 19:36:27 by rcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_final_command *cmd)
{
	char	*str;

	str = cmd->args[0];
	if (!ft_strcmp(str, "echo") || !ft_strcmp(str, "cd")
		|| !ft_strcmp(str, "pwd") || !ft_strcmp(str, "export")
		|| !ft_strcmp(str, "unset") || !ft_strcmp(str, "env"))
		return (1);
	return (0);
}

int	builtin_exe(t_shell *shell, t_final_command *cmd)
{
	char	*str;
	int		ret;

	ret = SUCCESS;
	str = cmd->args[0];
	if (!ft_strcmp(str, "echo"))
		ft_echo(cmd);
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
	return (ret);
}
