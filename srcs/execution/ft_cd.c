/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcorenti <rcorenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 18:35:54 by rcorenti          #+#    #+#             */
/*   Updated: 2022/02/21 08:35:34 by rcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_error_cd(char *str)
{
	ft_putstr_fd("megashell: cd: ", STDERR);
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
	shell->ret = 0;
	env = shell->env;
	if (!cmd->args[1])
	{
		str = get_val_env("HOME", env);
		if (!str)
		{
			shell->ret = 1;
			ft_putendl_fd("megashell: cd: HOME not set", STDERR);
		}
		else if (!ft_strcmp(str, ""))
			ret = ERROR;
		else
		{
			if (chdir(str) == -1)
			{
				shell->ret = 1;
				ft_error_cd(str);
			}
		}
		str = ft_memdel(str);
	}
	else
	{
		if (chdir(cmd->args[1]) == -1)
		{
			shell->ret = 1;
			ft_error_cd(cmd->args[1]);
		}
	}
	return (ret);
}
