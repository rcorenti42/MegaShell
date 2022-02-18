/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcorenti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 04:14:37 by rcorenti          #+#    #+#             */
/*   Updated: 2022/02/17 08:26:36 by rcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	char_len(t_char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i].c != '\0')
		i++;
	return (i);
}

int	ft_env_size(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	**tenv_to_tab(t_env *env)
{
	char	**ret;
	int		i;
	int		j;

	i = 0;
	ret = (char **)malloc(sizeof(char *) * (ft_env_size(env) + 1));
	while (env)
	{
		ret[i] = (char *)malloc(sizeof(char) * (ft_strlen(env->val) + 1));
		j = 0;
		while (env->val[j])
		{
			ret[i][j] = env->val[j];
			j++;
		}
		ret[i][j] = '\0';
		i++;
		env = env->next;
	}
	ret[i] = NULL;
	return (ret);
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	if (env)
	{
		while (env)
		{
			env->val = ft_memdel(env->val);
			tmp = env->next;
			env = ft_memdel(env);
			env = tmp;
		}
	}
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			tab[i] = ft_memdel(tab[i]);
			i++;
		}
		tab = ft_memdel(tab);
	}
}

int	count_pipes(t_final_command *cmd)
{
	int	ret;

	ret = 0;
	while (cmd)
	{
		ret++;
		cmd = cmd->next;
	}
	return (ret - 1);
}