/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 21:51:25 by sobouatt          #+#    #+#             */
/*   Updated: 2022/02/16 15:49:08 by rcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		free_cmd(t_command *head)
{
	t_command	*tmp;

	while (head)
	{
		head->command = ft_memdel(head->command);
		tmp = head;
		head = head->next;
		tmp = ft_memdel(tmp);
	}	
}

static void	handler(int code)
{
	(void)code;
	write(1, "\n", STDOUT);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	quit_handler(int code)
{
	if (code == SIGQUIT)
	{
		ft_putstr_fd("Quit (core dumped)\n", 1);
		rl_redisplay();
	}
	if (code == SIGINT)
	{
		write(1, "\n", STDOUT);
		rl_redisplay();
	}
}

static void	minishell(t_shell *shell, t_command *cmd)
{
	int			status;
	t_command	*prev;

	prev = NULL;
	while (cmd)
	{
		execution(shell, prev, cmd);
		waitpid(-1, &status, 0);
		status = WEXITSTATUS(status);
		if (shell->ret == 0)
			shell->ret = status;
		prev = cmd;
		cmd = cmd->next;
	}
}

static char	*ft_readline(void)
{
	char	*ret;

	ret = NULL;
	//signal(SIGQUIT, SIG_IGN);
	//signal(SIGINT, &handler);
	ret = readline(M E G A S H E L L ": \e[0m");
	if (!ret)
		ret = ft_strdup("exit");
	if (ft_strcmp(ret, ""))
		add_history(ret);
	//signal(SIGQUIT, &quit_handler);
	//signal(SIGINT, &quit_handler);
	return (ret);
}

static void	print_head(t_command *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		while (cmd->command[i])
		{
			printf("%s\n", cmd->command[i]->str);
			i++;
		}
		cmd = cmd->next;
	}
}

int		main(int ac, char **av, char **envp)
{
	t_command	*head;
	char		*input;
	t_shell		shell;

	(void)ac;
	(void)av;
	shell.ret = 0;
	shell.exit = 0;
	shell.redir.in = dup(STDIN);
	shell.redir.out = dup(STDOUT);
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
				print_head(head);
				//minishell(&shell, head);
				free_cmd(head);
			}
		}	
	}
	free_env(shell.env);
	return (shell.ret);
}
