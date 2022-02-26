/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcorenti <rcorenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:47:51 by rcorenti          #+#    #+#             */
/*   Updated: 2022/02/26 02:25:26 by rcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*absolute_path(char *bin, char *arg)
{
	bin = ft_strdup(arg);
	if (!bin)
		return (NULL);
	if (!access(bin, X_OK) && (bin[0] != '/' || bin[1]))
		return (bin);
	bin = ft_memdel(bin);
	bin = ft_strdup("");
	return (bin);
}

static char	*free_relative(char **path_split, char *bin)
{
	if (!bin)
	{
		free_tab(path_split);
		bin = ft_strdup("");
		return (bin);
	}
	free_tab(path_split);
	return (bin);
}

static char	*relative_path(char *path, char *arg, char *bin)
{
	int		i;
	char	**path_split;

	i = -1;
	path_split = NULL;
	path_split = ft_split(path, ':');
	path = ft_memdel(path);
	if (!path_split)
		return (NULL);
	while (path_split[++i])
	{
		bin = (char *)ft_calloc(sizeof(char), (ft_strlen(path_split[i])
					+ ft_strlen(arg) + 2));
		if (!bin)
			return (NULL);
		bin = ft_strcat(bin, path_split[i]);
		bin = ft_strcat(bin, "/");
		bin = ft_strcat(bin, arg);
		if (!access(bin, X_OK))
			break ;
		bin = ft_memdel(bin);
	}
	return (free_relative(path_split, bin));
}

char	*get_path(t_shell *shell, t_final_command *cmd)
{
	char	*path;
	char	*bin;
	char	*arg;

	bin = NULL;
	path = NULL;
	arg = cmd->args[0];
	path = get_val_env("PATH", shell->env);
	if (!path)
		return (NULL);
	if (arg[0] != '/' && ft_strncmp(arg, "./", 2)
		&& ft_strcmp(arg, "") && ft_strcmp(path, ""))
		return (relative_path(path, arg, bin));
	else
	{
		path = ft_memdel(path);
		return (absolute_path(bin, arg));
	}
	return (bin);
}
