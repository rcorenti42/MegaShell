/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcorenti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 17:00:42 by rcorenti          #+#    #+#             */
/*   Updated: 2022/02/16 14:37:27 by rcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	if_valid_n(char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-')
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	ft_echo(t_shell *shell, t_final_command *cmd)
{
	int	i;
	int	n;

	n = 0;
	i = 1;
	while (cmd->args[i])
	{
		if (!if_valid_n(cmd->args[i]))
			break ;
		i++;
		n = 1;
	}
	while (cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i], 1);
		if (cmd->args[i + 1])
			write(1, " ", STDOUT);
		i++;
	}
	if (!n)
		write(1, "\n", STDOUT);
}