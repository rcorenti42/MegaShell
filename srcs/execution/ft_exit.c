/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcorenti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 04:45:16 by rcorenti          #+#    #+#             */
/*   Updated: 2022/02/17 05:06:47 by rcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_isnumber(char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-' && str[0] != '+' && (str[0] > '9' || str[0] < '0'))
		return (1);
	while (str[i])
	{
		if (str[i] > '9' || str[i] < '0')
			return (1);
		i++;
	}
	return (0);
}

void	ft_exit(t_shell *shell, t_final_command *cmd)
{
	ft_putendl_fd("exit", STDOUT);
	if (cmd->args[1])
	{
		if (ft_isnumber(cmd->args[1]))
		{
			ft_putstr_fd("megashell: exit: ", STDERR);
			ft_putstr_fd(cmd->args[1], STDERR);
			ft_putendl_fd(": numeric argument required", STDERR);
			shell->ret = 2;
		}
		else if (cmd->args[2])
		{
			ft_putendl_fd("megashell: exit: too many arguments", STDERR);
			shell->ret = 1;
			return ;
		}
		shell->ret = ft_atoi(cmd->args[1]);
	}
	shell->exit = 1;
}
