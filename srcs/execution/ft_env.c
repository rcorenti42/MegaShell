/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcorenti <rcorenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 17:16:07 by rcorenti          #+#    #+#             */
/*   Updated: 2022/02/22 20:38:20 by rcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	if_valid_valenv(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	ft_env(t_shell *shell)
{
	t_env	*env;

	g_signal = 0;
	env = shell->env;
	while (env)
	{
		if (if_valid_valenv(env->val))
			ft_putendl_fd(env->val, STDOUT);
		env = env->next;
	}
}
