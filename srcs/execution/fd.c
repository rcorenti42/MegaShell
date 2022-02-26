/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcorenti <rcorenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 11:51:12 by rcorenti          #+#    #+#             */
/*   Updated: 2022/02/26 07:06:14 by rcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_redir(t_shell *shell)
{
	shell->redir.in_fd = -1;
	shell->redir.out_fd = -1;
	shell->redir.in_pipe = -1;
	shell->redir.out_pipe = -1;
	shell->redir.pid = -1;
}

void	init_pipe(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->redir.pipe_nbr)
	{
		shell->redir.pid_pipe[i] = -1;
		i++;
	}
}

int	init_std(t_shell *shell)
{
	if (dup2(shell->redir.in, STDIN) == -1)
		return (ERROR);
	if (dup2(shell->redir.out, STDOUT) == -1)
		return (ERROR);
	return (SUCCESS);
}

void	close_redir(t_shell *shell)
{
	if (shell->redir.in_fd > 0)
		close(shell->redir.in_fd);
	if (shell->redir.out_fd > 0)
		close(shell->redir.out_fd);
	if (shell->redir.in_pipe > 0)
		close(shell->redir.in_pipe);
	if (shell->redir.out_pipe > 0)
		close(shell->redir.out_pipe);
}
