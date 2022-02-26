/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcorenti <rcorenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 23:46:10 by rcorenti          #+#    #+#             */
/*   Updated: 2022/02/26 02:27:12 by rcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	return_export(char *str)
{
	g_signal = 1;
	ft_putstr_fd("megashell: export: `", STDERR);
	ft_putstr_fd(str, STDERR);
	ft_putendl_fd("': not a valid identifier", STDERR);
	return (SUCCESS);
}

static int	error_export(char *name)
{
	int	i;

	i = 0;
	if (!ft_isalpha(name[i]) && name[i] != '_')
		return (0);
	while (name[++i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
	}
	return (1);
}

static int	add_env(char *str, t_env *env)
{
	t_env	*new;
	t_env	*tmp;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (ERROR);
	new->val = ft_strdup(str);
	if (!new->val)
		return (ERROR);
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
	if (ft_check_char(str) == ERROR)
		return (0);
	while (env)
	{
		name = (char *)malloc(sizeof(char) * (ft_size_env(str) + 1));
		if (!name)
			return (-1);
		name = ft_name_env(str, name);
		if (!error_export(name))
			i = 1;
		else if (!ft_strncmp(name, env->val, ft_strlen(name))
			&& (env->val[ft_strlen(name)] == '='))
		{
			env->val = ft_memdel(env->val);
			env->val = ft_strdup(str);
			i = 2;
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
	g_signal = 0;
	env = shell->env;
	if (!cmd->args[i])
		ft_env(shell);
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
		else if (status == 1)
			return (return_export(cmd->args[i]));
		i++;
	}
	return (SUCCESS);
}
