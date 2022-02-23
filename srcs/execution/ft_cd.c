/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcorenti <rcorenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 18:35:54 by rcorenti          #+#    #+#             */
/*   Updated: 2022/02/23 07:52:59 by rcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_error_cd(char *str, int index)
{
	g_signal = 1;
	if (index == 1)
	{
		ft_putstr_fd("megashell: cd: ", STDERR);
		ft_putstr_fd(str, STDERR);
		ft_putstr_fd(": ", STDERR);
		ft_putendl_fd(strerror(errno), STDERR);
	}
	else
		ft_putendl_fd("megashell: cd: HOME not set", STDERR);
}

int	ft_cd(t_shell *shell, t_final_command *cmd)
{
	int		ret;
	char	*str;
	t_env	*env;

	ret = SUCCESS;
	g_signal = 0;
	env = shell->env;
	if (!cmd->args[1])
	{
		str = get_val_env("HOME", env);
		if (!str)
			ret = ERROR;
		else if (!ft_strcmp(str, ""))
			ft_error_cd(NULL, 2);
		else
		{
			if (chdir(str) == -1)
				ft_error_cd(str, 1);
			str = ft_memdel(str);
		}
	}
	else
		if (chdir(cmd->args[1]) == -1)
			ft_error_cd(cmd->args[1], 1);
	return (ret);
}
