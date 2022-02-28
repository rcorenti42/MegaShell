/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 23:40:55 by sobouatt          #+#    #+#             */
/*   Updated: 2022/02/27 23:40:57 by sobouatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_free_shlvl(char **shlvl_str, char **shlvl_final, int shlvl, t_env *env)
{
	char	*tmp;

	if (!shlvl_final)
	{
		shlvl_str = ft_memdel(shlvl_str);
		return (ERROR);
	}
	*shlvl_final[0] = '\0';
	*shlvl_final = ft_strcat(*shlvl_final, "SHLVL=");
	tmp = ft_itoa(shlvl);
	if (!tmp)
	{
		*shlvl_str = ft_memdel(*shlvl_str);
		*shlvl_final = ft_memdel(*shlvl_final);
		return (ERROR);
	}
	*shlvl_final = ft_strcat(*shlvl_final, tmp);
	tmp = ft_memdel(tmp);
	env->val = ft_memdel(env->val);
	env->val = ft_strdup(*shlvl_final);
	*shlvl_str = ft_memdel(*shlvl_str);
	*shlvl_final = ft_memdel(*shlvl_final);
	return (SUCCESS);
}

int	init_shlvl(char *str)
{
	int	shlvl_int;

	shlvl_int = ft_atoi(str);
	if (shlvl_int < 0)
		return (0);
	else
		return (shlvl_int + 1);
}

int	ft_shlvl(t_env *env)
{
	char	*shlvl_str;
	char	*shlvl_final;
	char	*tmp;
	int		shlvl_int;

	while (env)
	{
		if (!ft_strncmp("SHLVL=", env->val, 6))
		{
			shlvl_str = get_val_env("SHLVL", env);
			if (!shlvl_str)
				return (ERROR);
			shlvl_int = ft_atoi(shlvl_str);
			shlvl_int = init_shlvl(shlvl_str);
			tmp = ft_itoa(shlvl_int);
			if (!tmp)
				return (ERROR);
			shlvl_final = (char *)malloc(sizeof(char) * (ft_strlen(tmp) + 7));
			tmp = ft_memdel(tmp);
			return (ft_free_shlvl(&shlvl_str, &shlvl_final, shlvl_int, env));
		}
		env = env->next;
	}
	return (SUCCESS);
}
