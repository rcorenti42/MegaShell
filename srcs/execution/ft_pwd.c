/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcorenti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 17:27:34 by rcorenti          #+#    #+#             */
/*   Updated: 2022/02/12 06:59:42 by rcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(void)
{
	char	*cwd;

	cwd = (char *)malloc(sizeof(char) * (PATH_MAX + 5));
	if (!cwd)
		return (ERROR);
	if (!getcwd(cwd, PATH_MAX))
		return (ERROR);
	ft_putendl_fd(cwd, STDOUT);
	cwd = ft_memdel(cwd);
	return (SUCCESS);
}
