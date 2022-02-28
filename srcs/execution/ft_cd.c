/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 18:35:54 by rcorenti          #+#    #+#             */
/*   Updated: 2022/02/27 23:02:38 by sobouatt         ###   ########.fr       */
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

static int	add_env_2(char *str, t_env *env)
{
	t_env	*new;
	t_env	*tmp;

	while (env->next)
	{
		if (!ft_strncmp(env->val, str, ft_strlen(str)))
			return (SUCCESS);
		env = env->next;
	}
	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (ERROR);
	new->val = ft_strdup(str);
	if (!new->val)
		return (ERROR);
	tmp = env->next;
	env->next = new;
	new->next = tmp;
	return (SUCCESS);
}

static int	ft_chang_env(t_env *env, char *val, char *new)
{
	if (add_env_2("PWD=", env) == ERROR || add_env_2("OLDPWD=", env) == ERROR)
		return (ERROR);
	while (env)
	{
		if (!ft_strncmp(env->val, val, ft_strlen(val)))
		{
			env->val = ft_memdel(env->val);
			env->val = malloc(sizeof(char)
					* (ft_strlen(val) + ft_strlen(new) + 1));
			if (!env->val)
				return (ERROR);
			env->val[0] = '\0';
			env->val = ft_strcat(env->val, val);
			env->val = ft_strcat(env->val, new);
			return (SUCCESS);
		}
		env = env->next;
	}
	return (SUCCESS);
}

static char	*update_pwd(t_shell *shell)
{
	char	*tmp;
	char	*pwd;

	pwd = get_val_env("PWD", shell->env);
	if (!pwd)
		return (NULL);
	tmp = ft_pwd2();
	if (!tmp)
		return (NULL);
	if (ft_strcmp(pwd, tmp))
		if (ft_chang_env(shell->env, "OLDPWD=", pwd) == ERROR
			|| ft_chang_env(shell->env, "PWD=", tmp) == ERROR)
			return (NULL);
	free(tmp);
	free(pwd);
	return ("");
}

int	ft_cd(t_shell *shell, t_final_command *cmd)
{
	int		ret;
	char	*str;

	ret = SUCCESS;
	g_signal = 0;
	if (!cmd->args[1])
	{
		str = get_val_env("HOME", shell->env);
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
	if (!update_pwd(shell))
		return (ERROR);
	return (ret);
}
