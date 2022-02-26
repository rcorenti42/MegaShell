/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcorenti <rcorenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 12:49:53 by sobouatt          #+#    #+#             */
/*   Updated: 2022/02/26 23:22:30 by rcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler(int code)
{
	if (code == SIGINT)
	{
		g_signal = 130;
		write(STDOUT, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	quit_handler(int code)
{
	if (code == SIGQUIT)
	{
		g_signal = 131;
		ft_putendl_fd("Quit (core dumped)", STDERR);
		rl_redisplay();
	}
	if (code == SIGINT)
	{
		g_signal = 130;
		write(STDOUT, "\n", 1);
		rl_redisplay();
	}
}

char	*ft_readline(void)
{
	char	*ret;

	ret = NULL;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &handler);
	rl_outstream = stderr;
	ret = readline(M E G A S H E X L I " ");
	if (!ret)
		ret = ft_strdup("exit");
	if (ft_strcmp(ret, ""))
		add_history(ret);
	return (ret);
}

static int	ft_father(t_shell *shell)
{
	int	i;
	int	status;

	i = -1;
	status = 0;
	if (shell->parent)
	{
		while (i < shell->redir.i_pipe)
		{
			i++;
			waitpid(shell->redir.pid_pipe[i], &status, 0);
		}
		waitpid(shell->redir.pid, &status, 0);
	}
	if (init_std(shell) == ERROR)
		return (ERROR);	
	if (shell->parent)
	{	
		if (WIFEXITED(status))
		{
			status = WEXITSTATUS(status);
			g_signal = status;
		}
	return (SUCCESS);
	}
	return (g_signal);
}

int	something_went_wrong(t_shell *shell)
{
	if (init_std(shell) == ERROR)
	{
		shell->redir.pid_pipe = ft_memdel(shell->redir.pid_pipe);
		return (ERROR);
	}
	if (ft_father(shell) == ERROR)
	{
		shell->redir.pid_pipe = ft_memdel(shell->redir.pid_pipe);
		return (ERROR);
	}
	return (SUCCESS);
}
