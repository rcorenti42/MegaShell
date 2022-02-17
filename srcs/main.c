/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 21:51:25 by sobouatt          #+#    #+#             */
/*   Updated: 2022/02/17 09:05:41 by rcorenti         ###   ########.fr       */
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
		tmp = head;
		while (head->args[i] != NULL)
			free(head->args[i++]);
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
	int	first;

	first = 1;
	shell->redir.pipe_nbr = count_pipes(cmd);
	while (cmd)
	{
		shell->parent = 1;
		execution(shell, cmd, first);
		close_redir(shell);
		init_redir(shell);
		init_std(shell);
		waitpid(-1, &status, 0);
		status = WEXITSTATUS(status);
		if (shell->ret == 0)
			shell->ret = status;
		if (shell->parent == 0)
			exit(shell->ret);
		first = 0;
		cmd = cmd->next;
	}
}

static char	*ft_readline(void)
{
	char	*ret;

	ret = NULL;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &handler);
	ret = readline(M E G A S H E L L ": \e[0m");
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
	shell.redir.in = dup(STDOUT);
	shell.redir.out = dup(STDIN);
	init_redir(&shell);
	if (init_env(&shell, envp) == ERROR)
		return (ERROR);
	while (!shell.exit)
	{
		input = ft_readline();
		if (ft_strcmp(input, ""))
		{
			head = lexer(input, shell.env);
			input = ft_memdel(input);
			if (head != NULL)
			{
				minishell(&shell, head);
				free_final(head);
			}
		}	
	}
	free_env(shell.env);
	return (shell.ret);
}
