/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcorenti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 18:35:54 by rcorenti          #+#    #+#             */
/*   Updated: 2022/02/16 14:37:02 by rcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_error_cd(char *str)
{
	ft_putstr_fd("cd: ", STDERR);
	ft_putstr_fd(str, STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putendl_fd(strerror(errno), STDERR);
}

int	ft_cd(t_shell *shell, t_final_command *cmd)
{
	int		ret;
	char	*str;
	t_env	*env;

	ret = SUCCESS;
	env = shell->env;
	if (!cmd->args[1])
	{
		str = get_val_env("HOME", env);
		if (!str)
			ft_putstr_fd("cd: HOME not set\n", STDERR);
		else if (!ft_strcmp(str, ""))
			ret = ERROR;
		else
		{
			if (chdir(str) == -1)
				ft_error_cd(str);
		}
		str = ft_memdel(str);
	}
	else
	{
		if (chdir(cmd->args[1]) == -1)
			ft_error_cd(cmd->args[1]);
	}
	return (ret);
}
