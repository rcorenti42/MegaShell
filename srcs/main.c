/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcorenti <rcorenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 21:51:25 by sobouatt          #+#    #+#             */
/*   Updated: 2022/02/23 01:25:09 by rcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_signal;

void	free_final(t_final_command *head)
{
	t_final_command *tmp;
	int i;

	i = 0;
	tmp = head;
	while (head)
	{
		i = 0;
		tmp = head;
		if (head->args != NULL)
			while (head->args[i] != NULL)
				free(head->args[i++]);
		i = 0;
		if (head->redir_in != NULL)
			while (head->redir_in[i].redir != NULL)
				free(head->redir_in[i++].redir);
		i = 0;
		if (head->redir_out != NULL)
			while (head->redir_out[i].redir != NULL)
				free(head->redir_out[i++].redir);
		free(head->redir_in);
		free(head->redir_out);
		free(head->args);
		head = head->next;
		free(tmp);
	}
}

void	handler(int code)
{
	(void)code;
	
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
		ft_putendl_fd("Quit (core dumped)", STDERR);
		rl_redisplay();
	}
	if (code == SIGINT)
	{
		write(STDOUT, "\n", 1);
		rl_redisplay();
	}
}

int	minishell(t_shell *shell, t_env *env, t_final_command *cmd)
{
	int	status;
	int	i;

	i = -1;
	status = 0;
	shell->redir.pipe_nbr = count_pipes(cmd);
	shell->redir.pid_pipe = (pid_t *)malloc(sizeof(pid_t) * shell->redir.pipe_nbr);
	init_pipe(shell);
	shell->parent = 1;
	if (execution(shell, cmd) == ERROR)
		return (ERROR);
	close_redir(shell);
	init_redir(shell);
	init_pipe(shell);
	if (init_std(shell) == ERROR)
		return (ERROR);
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
	if (WIFEXITED(status))
	{
		status = WEXITSTATUS(status);
		if (g_signal == 0)
			g_signal = status;
	}
	shell->redir.pid_pipe = ft_memdel(shell->redir.pid_pipe);
	if (!shell->parent)
	{
		if (close(STDIN) == -1)
			return (ERROR);
		if (close(STDOUT) == -1)
			return (ERROR);
		if (shell->redir.in > 0)
		{
			if (close(shell->redir.in) == -1)
				return (ERROR);
		}
		if (shell->redir.out > 0)
		{
			if (close(shell->redir.out) == -1)
				return (ERROR);
		}
		free_env(env);
		free_final(cmd);
		close_redir(shell);
		init_redir(shell);
		clear_history();
		close(STDIN);
		close(STDOUT);
		close(STDERR);
		exit(g_signal);
	}
	return (SUCCESS);
}

char	*ft_readline(void)
{
	char	*ret;

	ret = NULL;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &handler);
	rl_outstream = stderr;
	ret = readline(M E G A S H E X L _ " ");
	if (!ret)
		ret = ft_strdup("exit");
	else if (ft_strcmp(ret, ""))
		add_history(ret);
	signal(SIGQUIT, &quit_handler);
	signal(SIGINT, &quit_handler);
	return (ret);
}

int		main(int ac, char **av, char **envp)
{
	t_final_command	*head;
	char		*input;
	t_shell		shell;

	(void)ac;
	(void)av;
	shell.exit = 0;
	g_signal = 0;
	shell.redir.in = dup(STDIN);
	if (shell.redir.in == -1)
		return (ERROR);
	shell.redir.out = dup(STDOUT);
	if (shell.redir.out == -1)
		return (ERROR);
	shell.redir.pipe_nbr = 0;
	init_redir(&shell);
	if (init_env(&shell, envp) == ERROR)
		return (ERROR);
	while (!shell.exit)
	{
		shell.redir.i_pipe = -1;
		input = ft_readline();
		if (ft_strcmp(input, ""))
		{
			shell.env->ret = g_signal;
			g_signal = 0;
			head = lexer(input, shell.env);
			if (shell.env->ret != 0)
				g_signal = shell.env->ret;	
			//display_final(head);
			if (head != NULL)
			{
				if (minishell(&shell, shell.env, head) == ERROR)
					return (ERROR);
				free_final(head);
			}
		}
		input = ft_memdel(input);
	}
	clear_history();
	free_env(shell.env);
	if (close(STDIN) == -1 || close(STDOUT) == -1 || close(STDERR) == -1)
		return (ERROR);
	if (shell.redir.in > 0)
	{
		if (close(shell.redir.in) == -1)
			return (ERROR);
	}
	if (shell.redir.out > 0)
	{
		if (close(shell.redir.out) == -1)
			return (ERROR);
	}
	return (g_signal);
}
