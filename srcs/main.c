/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcorenti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 12:28:55 by rcorenti          #+#    #+#             */
/*   Updated: 2022/01/26 07:11:43 by rcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_shell(t_shell *shell)
{
	t_shell tmp;

	tmp = *shell;
	tmp.exit = 0;
	tmp.ret = 0;
	tmp.in = dup(STDIN);
	tmp.out = dup(STDOUT);
}

int		main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	(void)envp;
	init_shell(&shell);
	while (!shell.exit)
	{
		if(!readline("$> "))
			exit(0);
	}
	return (shell.ret);
}
