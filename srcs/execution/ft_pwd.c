/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcorenti <rcorenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 17:27:34 by rcorenti          #+#    #+#             */
/*   Updated: 2022/02/23 08:11:03 by rcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(void)
{
	char	*cwd;

	g_signal = 0;
	cwd = (char *)malloc(sizeof(char) * (PATH_MAX + 5));
	if (!cwd)
		return (ERROR);
	if (!getcwd(cwd, PATH_MAX))
	{
		ft_putstr_fd("pwd: error retrieving current directory: ", STDERR);
		ft_putstr_fd("getcwd: cannot access parent directories: ", STDERR);
		ft_putendl_fd(strerror(errno), STDERR);
		cwd = ft_memdel(cwd);
		g_signal = 1;
		return (SUCCESS);
	}
	ft_putendl_fd(cwd, STDOUT);
	cwd = ft_memdel(cwd);
	return (SUCCESS);
}
