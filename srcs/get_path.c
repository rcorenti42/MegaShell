/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcorenti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:47:51 by rcorenti          #+#    #+#             */
/*   Updated: 2022/02/17 08:18:24 by rcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path(t_shell *shell, t_final_command *cmd)
{
	int		i;
	char	*path;
	char	*bin;
	char	*arg;
	char	**path_split;

	i = -1;
	bin = NULL;
	arg = cmd->args[0];
	path = get_val_env("PATH", shell->env);
	if (!path)
		return (NULL);
	if (arg[0] != '/' && ft_strncmp(arg, "./", 2) && ft_strcmp(arg, "") && ft_strcmp(path, ""))
	{
		path_split = ft_split(path, ':');
		while (path_split[++i])
		{
			bin = (char *)calloc(sizeof(char), (ft_strlen(path_split[i])
						+ ft_strlen(arg) + 2));
			if (!bin)
				return (NULL);
			bin = ft_strcat(bin, path_split[i]);
			bin = ft_strcat(bin, "/");
			bin = ft_strcat(bin, arg);
			if (!access(bin, F_OK))
				break ;
			bin = ft_memdel(bin);
		}
		if (!bin)
		{
			bin = ft_strdup("");
			return (bin);
		}
		free_tab(path_split);
	}
	else
		bin = ft_strdup(arg);
	path = ft_memdel(path);
	return (bin);
}
