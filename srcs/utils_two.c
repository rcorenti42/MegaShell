/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 04:14:37 by rcorenti          #+#    #+#             */
/*   Updated: 2022/02/28 02:22:10 by sobouatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_pwd2(void)
{
	char	*cwd;

	cwd = (char *)malloc(sizeof(char) * (PATH_MAX + 5));
	if (!cwd)
		return (NULL);
	if (!getcwd(cwd, PATH_MAX + 5))
	{
		cwd = ft_memdel(cwd);
		return (NULL);
	}
	return (cwd);
}

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
	if (!ret)
		return (NULL);
	while (env)
	{
		ret[i] = (char *)malloc(sizeof(char) * (ft_strlen(env->val) + 1));
		if (!ret[i])
			return (NULL);
		j = -1;
		while (env->val[++j])
			ret[i][j] = env->val[j];
		ret[i++][j] = '\0';
		env = env->next;
	}
	ret[i] = NULL;
	return (ret);
}
