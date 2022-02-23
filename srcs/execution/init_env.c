/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcorenti <rcorenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 22:55:08 by rcorenti          #+#    #+#             */
/*   Updated: 2022/02/23 22:50:35 by rcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_env_new(t_shell *shell, t_env *env, char **envp)
{
	int		i;
	t_env	*new;

	i = 1;
	env->next = NULL;
	shell->env = env;
	while (envp[i])
	{
		new = (t_env *)malloc(sizeof(t_env));
		if (!new)
			return (ERROR);
		new->val = ft_strdup(envp[i]);
		if (!new->val)
			return (ERROR);
		new->next = NULL;
		env->next = new;
		env = new;
		i++;
	}
	return (SUCCESS);
}

int	init_env(t_shell *shell, char **envp)
{
	t_env	*env;

	if (!envp)
		return (ERROR);
	env = (t_env *)malloc(sizeof(t_env));
	if (!env)
		return (ERROR);
	if (envp[0])
	{
		env->val = ft_strdup(envp[0]);
		if (!env->val)
			return (ERROR);
	}
	if (!envp[0])
	{
		env->val = (char *)malloc(sizeof(char));
		if (!env->val)
			return (ERROR);
		env->val = ft_strdup("");
		env->next = NULL;
		shell->env = env;
		return (SUCCESS);
	}
	return (init_env_new(shell, env, envp));
}
