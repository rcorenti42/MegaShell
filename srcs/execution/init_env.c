/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcorenti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 22:55:08 by rcorenti          #+#    #+#             */
/*   Updated: 2022/02/15 07:47:59 by rcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_env(t_shell *shell, char **envp)
{
	int		i;
	t_env	*env;
	t_env	*new;

	i = 1;
	if (!envp)
		return (ERROR);
	env = (t_env *)malloc(sizeof(t_env));
	if (!env)
		return (ERROR);
	env->val = ft_strdup(envp[0]);
	env->next = NULL;
	shell->env = env;
	while (envp && envp[i])
	{
		new = (t_env *)malloc(sizeof(t_env));
		if (!new)
			return (ERROR);
		new->val = ft_strdup(envp[i]);
		new->next = NULL;
		env->next = new;
		env = new;
		i++;
	}
	return (SUCCESS);
}
