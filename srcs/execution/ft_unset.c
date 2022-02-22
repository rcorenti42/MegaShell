/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcorenti <rcorenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 10:03:27 by rcorenti          #+#    #+#             */
/*   Updated: 2022/02/22 20:38:32 by rcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	if_valid_unset(char *str, char *val)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && val[i] && str[i] == val[i])
		i++;
	if (!str[i] && val[i] == '=')
		return (1);
	return (0);
}

static void	ft_delenv(t_env *env)
{
	t_env	*tmp;

	tmp = env->next->next;
	env->next->val = ft_memdel(env->next->val);
	env->next = ft_memdel(env->next);
	env->next = tmp;
}

void	ft_unset(t_shell *shell, t_final_command *cmd)
{
	int		i;
	t_env	*env;

	i = 0;
	g_signal = 0;
	while (cmd->args[++i])
	{
		env = shell->env;
		if (if_valid_unset(cmd->args[i], env->val))
		{
			shell->env = shell->env->next;
			env->val = ft_memdel(env->val);
			env = ft_memdel(env);
		}
		else
		{
			while (env && env->next)
			{
				if (if_valid_unset(cmd->args[i], env->next->val))
					ft_delenv(env);
				env = env->next;
			}
		}
	}
}
