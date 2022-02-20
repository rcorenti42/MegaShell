/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcorenti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 23:46:10 by rcorenti          #+#    #+#             */
/*   Updated: 2022/02/16 14:37:59 by rcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_size_env(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

static char	*ft_name_env(char *str, char *name)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		name[i] = str[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}

static int	add_env(char *str, t_env *env)
{
	t_env	*new;
	t_env	*tmp;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (ERROR);
	new->val = ft_strdup(str);
	while (env->next)
		env = env->next;
	tmp = env->next;
	env->next = new;
	new->next = tmp;
	return (SUCCESS);
}

static int	is_in_env(char *str, t_env *env)
{
	char	*name;
	int		i;

	i = 0;
	while (env)
	{
		name = (char *)malloc(sizeof(char) * (ft_size_env(str) + 1));
		if (!name)
			return (-1);
		name = ft_name_env(str, name);
		if (!ft_strncmp(name, env->val, ft_size_env(env->val))
			&& !ft_strncmp(name, env->val, ft_strlen(name))
			&& str[ft_strlen(name)])
		{
			i = 1;
			env->val = ft_memdel(env->val);
			env->val = ft_strdup(str);
			name = ft_memdel(name);
			break ;
		}
		name = ft_memdel(name);
		env = env->next;
	}
	return (i);
}

int	ft_export(t_shell *shell, t_final_command *cmd)
{
	int		i;
	int		status;
	t_env	*env;

	i = 1;
	env = shell->env;
	while (cmd->args[i])
	{
		status = is_in_env(cmd->args[i], env);
		if (status == 0)
		{
			if (add_env(cmd->args[i], env) == ERROR)
				return (ERROR);
		}
		else if (status == -1)
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}
