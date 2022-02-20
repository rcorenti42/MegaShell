/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 21:51:25 by sobouatt          #+#    #+#             */
/*   Updated: 2022/02/20 13:46:42 by rcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	handler(int code)
{
	(void)code;
	write(STDOUT, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	quit_handler(int code)
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

static void	minishell(t_shell *shell, t_final_command *cmd)
{
	int	status;
	int	i;

	i = 0;
	status = 0;
	shell->redir.pipe_nbr = count_pipes(cmd);
	shell->redir.pid_pipe = (pid_t *)malloc(sizeof(pid_t) * shell->redir.pipe_nbr);
	init_pipe(shell);
	shell->parent = 1;
	execution(shell, cmd);
	if (shell->parent)
	{
		while (i < shell->redir.i_pipe)
		{
			waitpid(shell->redir.pid_pipe[i], NULL, 0);
			i++;
		}
		waitpid(shell->redir.pid, &status, 0);
	}
	init_std(shell);
	close_redir(shell);
	init_redir(shell);
	if (!shell->parent)
	{
		close(STDIN);
		close(STDOUT);
		if (shell->redir.in > 0)
			close(shell->redir.in);
		if (shell->redir.out > 0)
			close(shell->redir.out);
		exit(shell->ret);
	}
	if (WIFEXITED(status))
	{
		status = WEXITSTATUS(status);
		if (!shell->ret)
			shell->ret = status;
	}
	shell->redir.pid_pipe = ft_memdel(shell->redir.pid_pipe);
}

static char	*ft_readline(void)
{
	char	*ret;

	ret = NULL;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &handler);

	//ret = readline("Megashell: ");

	rl_outstream = stderr;
	ret = readline(M E G A S H E L L ": ");



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
	shell.ret = 0;
	shell.exit = 0;
	shell.redir.in = dup(STDIN);
	shell.redir.out = dup(STDOUT);
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
			shell.env->ret = shell.ret;
			head = lexer(input, shell.env);
			shell.ret = shell.env->ret;

			if (head != NULL)
			{
				minishell(&shell, head);
				free_final(head);
			}
		}
		input = ft_memdel(input);
	}
	free_env(shell.env);
	close(STDIN);
	close(STDOUT);
	close(STDERR);
	if (shell.redir.in > 0)
		close(shell.redir.in);
	if (shell.redir.out > 0)
		close(shell.redir.out);
	return (shell.ret);
}
