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

char	*get_path(t_shell *shell, t_command *cmd)
{
	int		i;
	char	*path;
	char	*bin;
	char	*arg
	char	**path_split;
	t_env	*env;

	i = -1;
	bin = NULL;
	env = shell->env;
	arg = cmd->command[0];
	path = get_val_env("PATH", env);
	if (!path)
		path = ft_strdup("/bin:/usr/local/bin:/usr/bin:/bin:/usr/local/sbin");
	if ((arg[0] != '/') && (ft_strncmp(arg, "./", 2) != 0))
	{
		path_split = ft_split(path, ':');
		ft_memdel(path);
		while (path_split[++i])
		{
			bin = (char *)calloc(sizeof(char), (ft_strlen(path_split[i])
						+ ft_strlen(arg) + 2));
			if (!bin)
				break ;
			bin = ft_strcat(bin, path_split[i]);
			bin = ft_strcat(bin, "/");
			bin = ft_strcat(bin, arg);
			if (!access(bin, F_OK))
				break ;
			bin = ft_memdel(bin);
		}
		free_tab(path_split);
	}
	else
	{
		ft_memdel(path);
		bin = ft_strdup(arg);
	}
	return (bin);
}
