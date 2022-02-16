/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_val_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcorenti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 04:28:41 by rcorenti          #+#    #+#             */
/*   Updated: 2022/02/12 07:12:32 by rcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_val_env(char *arg, t_env *env)
{
	int		i;
	int		j;
	char	*ret;

	ret = NULL;
	while (env && (ft_strncmp(arg, env->val, ft_strlen(arg))
			|| env->val[ft_strlen(arg)] != '='))
		env = env->next;
	if (!env)
		return (ret);
	i = 0;
	j = 0;
	while (env->val[i] && env->val[i] != '=')
		i++;
	i++;
	ret = (char *)malloc(sizeof(char) * (ft_strlen(env->val) - i + 1));
	if (!ret)
		return ("");
	while (env->val[i])
		ret[j++] = env->val[i++];
	ret[j] = '\0';
	return (ret);
}
