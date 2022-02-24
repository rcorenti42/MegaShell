/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 04:14:37 by rcorenti          #+#    #+#             */
/*   Updated: 2022/02/24 11:54:17 by sobouatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	if (env)
	{
		while (env)
		{
			if (env->val)
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

void	*display_syntax_error(void)
{
	write(2, "megashell: syntax error\n",
		ft_strlen("megashell: syntax error\n"));
	g_signal = 2;
	return (NULL);
}
