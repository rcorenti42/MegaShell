/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcorenti <rcorenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 21:51:25 by sobouatt          #+#    #+#             */
/*   Updated: 2022/02/24 14:33:48 by rcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal;

void	free_final(t_final_command *head)
{
	t_final_command	*tmp;
	int				i;

	while (head)
	{
		i = -1;
		tmp = head;
		while (head->args && head->args[++i])
			head->args[i] = ft_memdel(head->args[i]);
		i = -1;
		while (head->redir_in && head->redir_in[++i].redir)
			head->redir_in[i].redir = ft_memdel(head->redir_in[i].redir);
		i = -1;
		while (head->redir_out && head->redir_out[++i].redir)
			head->redir_out[i].redir = ft_memdel(head->redir_out[i].redir);
		head->redir_in = ft_memdel(head->redir_in);
		head->redir_out = ft_memdel(head->redir_out);
		head->args = ft_memdel(head->args);
		head = head->next;
		tmp = ft_memdel(tmp);
	}
}

static int	ft_free_exit(t_shell *shell)
{
	close_redir(shell);
	init_redir(shell);
	close(STDIN);
	close(STDOUT);
	close(STDERR);
	free_env(shell->env);
	perror("Error : ");
	return (ERROR);
}

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

static void	close_child(t_shell *shell, t_env *env, t_final_command *cmd)
{
	(void)env;
	if (!shell->parent)
	{
		close(STDIN);
		close(STDOUT);
		if (shell->redir.in > 0)
			close(shell->redir.in);
		if (shell->redir.out > 0)
			close(shell->redir.out);
		free_final(cmd);
		close_redir(shell);
		init_redir(shell);
		clear_history();
		close(STDIN);
		close(STDOUT);
		close(STDERR);
		exit(g_signal);
	}
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
	if (WIFEXITED(status))
	{
		status = WEXITSTATUS(status);
		if (g_signal == 0)
			g_signal = status;
	}
	return (SUCCESS);
}

int	minishell(t_shell *shell, t_env *env, t_final_command *cmd)
{
	shell->redir.i_pipe = -1;
	shell->redir.pipe_nbr = count_pipes(cmd);
	shell->redir.pid_pipe = (pid_t *)malloc(sizeof(pid_t)
			* shell->redir.pipe_nbr + 1);
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
	if (init_std(shell) == ERROR)
	{
		shell->redir.pid_pipe = ft_memdel(shell->redir.pid_pipe); // l'attribution ne fais rien
		return (ERROR);
	}
	if (ft_father(shell) == ERROR)
	{
		shell->redir.pid_pipe = ft_memdel(shell->redir.pid_pipe);
		return (ERROR);
	}
	shell->redir.pid_pipe = ft_memdel(shell->redir.pid_pipe);
	if (!shell->parent)
		close_child(shell, env, cmd);
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
	add_history(ret);
	return (ret);
}

static int	ft_end(t_shell *shell)
{
	clear_history();
	free_env(shell->env);
	if (close(STDIN) == -1 || close(STDOUT) == -1 || close(STDERR) == -1)
		return (ft_free_exit(shell));
	if (shell->redir.in > 0)
	{
		if (close(shell->redir.in) == -1)
			return (ft_free_exit(shell));
	}
	if (shell->redir.out > 0)
	{
		if (close(shell->redir.out) == -1)
			return (ft_free_exit(shell));
	}
	return (g_signal);
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

int	main(int ac, char **av, char **envp)
{
	t_final_command	*head;
	char			*input;
	t_shell			shell;

	(void)ac;
	(void)av;
	if (init_shell(&shell, envp) == ERROR)
		return (ft_free_exit(&shell));
	while (!shell.exit)
	{
		shell.redir.i_pipe = -1;
		input = ft_readline();
		if (ft_strcmp(input, ""))
		{
			head = lexer(input, shell.env);
			display_final(head);
			if (head != NULL)
				if (minishell(&shell, shell.env, head) == ERROR)
					ft_free_exit(&shell);
			free_final(head);
		}
		input = ft_memdel(input);
	}
	return (ft_end(&shell));
}
