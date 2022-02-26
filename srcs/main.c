/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcorenti <rcorenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 21:51:25 by sobouatt          #+#    #+#             */
/*   Updated: 2022/02/26 23:17:23 by rcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal;

static void	close_child(t_shell *shell, t_env *env, t_final_command *cmd)
{
	if (!shell->parent)
	{
		close(STDIN);
		close(STDOUT);
		if (shell->redir.in > 0)
			close(shell->redir.in);
		if (shell->redir.out > 0)
			close(shell->redir.out);
		free_env(env);
		free_final(cmd);
		close_redir(shell);
		init_redir(shell);
		rl_clear_history();
		close(STDIN);
		close(STDOUT);
		close(STDERR);
		exit(g_signal);
	}
}

int	minishell(t_shell *shell, t_env *env, t_final_command *cmd)
{
	shell->redir.i_pipe = -1;
	shell->redir.pipe_nbr = count_pipes(cmd);
	shell->redir.pid_pipe = (pid_t *)malloc(sizeof(pid_t)
			* (shell->redir.pipe_nbr + 1));
	if (!shell->redir.pid_pipe)
		return (ERROR);
	init_pipe(shell);
	shell->parent = 1;
	signal(SIGQUIT, &quit_handler);
	signal(SIGINT, &quit_handler);
	if (execution(shell, cmd) == ERROR)
	{
		shell->redir.pid_pipe = ft_memdel(shell->redir.pid_pipe);
		return (ERROR);
	}
	close_redir(shell);
	init_redir(shell);
	init_pipe(shell);
	if (something_went_wrong(shell))
		return (ERROR);
	shell->redir.pid_pipe = ft_memdel(shell->redir.pid_pipe);
	if (!shell->parent)
		close_child(shell, env, cmd);
	return (SUCCESS);
}

int	init_shell(t_shell *shell, char **envp)
{
	shell->exit = 0;
	g_signal = 0;
	shell->redir.in = dup(STDIN);
	if (shell->redir.in == -1)
		return (ft_free_exit(shell));
	shell->redir.out = dup(STDOUT);
	if (shell->redir.out == -1)
		return (ft_free_exit(shell));
	shell->redir.pipe_nbr = 0;
	init_redir(shell);
	if (init_env(shell, envp) == ERROR)
		return (ft_free_exit(shell));
	return (SUCCESS);
}

void	do_shell( t_shell *shell)
{
	t_final_command	*head;
	char			*input;

	shell->exec = 1;
	shell->redir.i_pipe = -1;
	input = ft_readline();
	if (ft_strcmp(input, ""))
	{
		head = lexer(input, (*shell).env);
		if (head != NULL)
		{
			if (minishell(shell, (*shell).env, head) == ERROR)
			{
				ft_free_exit(shell);
				free_final(head);
				free(input);
				exit(g_signal);
			}
		}
		free_final(head);
	}
	free(input);
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	(void)ac;
	(void)av;
	if (init_shell(&shell, envp) == ERROR)
		return (ft_free_exit(&shell));
	while (!shell.exit)
		do_shell(&shell);
	close(shell.redir.out);
	close(shell.redir.in);
	ft_free_exit(&shell);
	return (g_signal);
}
