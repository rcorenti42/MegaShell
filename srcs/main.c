/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcorenti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 12:28:55 by rcorenti          #+#    #+#             */
/*   Updated: 2022/01/24 13:04:55 by rcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_shell(t_shell **shell)
{
	t_shell *tmp;

	tmp = *shell;
	tmp.exit = 0;
	tmp.ret = 0;
}

int		main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	(void)argc;
	(void)argv;
	init_shell(&shell);
	while (!shell.exit)
	{
	}
	return (shell.ret);
}
