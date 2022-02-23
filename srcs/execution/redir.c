/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcorenti <rcorenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 03:34:59 by rcorenti          #+#    #+#             */
/*   Updated: 2022/02/23 13:34:24 by rcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	doc_handler(int code)
{
	(void)code;
	g_signal = 130;

		write(STDOUT, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		write(STDOUT, "\n", 1);
		write(STDOUT, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		write(STDOUT, "\n", 1);

}

static void	error_redir(char *str)
{
	ft_putstr_fd("megashell: ", STDERR);
	ft_putstr_fd(str, STDERR);
	ft_putendl_fd(strerror(errno), STDERR);
	g_signal = 1;
}

static int	ft_heredoc(char *str)
{
	char	*line;
	int		fd[2];

	pipe(fd);
	rl_outstream = stderr;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &doc_handler);
	while (1)
	{
		line = readline("> ");
		if (g_signal == 130)
			break ;
		if (!line)
		{
			ft_putstr_fd("bash: warning: here-document at line 1 delimited by end-of-file (wanted `", STDERR);
			ft_putstr_fd(str, STDERR);
			ft_putendl_fd("')", STDERR);
			break;
		}
		if (!ft_strcmp(line, str))
			break ;
		ft_putendl_fd(line, fd[1]);
		line = ft_memdel(line);
	}
	line = ft_memdel(line);
	if (dup2(fd[0], STDIN) == -1)
		return (ERROR);
	if (fd[0] > 0)
	{
		if (close(fd[0]) == -1)
			return (ERROR);
	}
	if (fd[1] > 0)
	{
		if (close(fd[1]) == -1)
			return (ERROR);
	}
	return (SUCCESS);
}

int	ft_pipe(t_shell *shell)
{
	int		fd[2];

	pipe(fd);
	(shell->redir.i_pipe)++;
	(shell->redir.pid_pipe)[shell->redir.i_pipe] = fork();
	if (shell->redir.pid_pipe[shell->redir.i_pipe] == -1)
		return (-1);
	else if (shell->redir.pid_pipe[shell->redir.i_pipe] == 0)
	{
		if (fd[0] > 0)
		{
			if (close(fd[0]) == -1)
				return (-1);
		}
		if (dup2(fd[1], STDOUT) == -1)
			return (-1);
		shell->redir.pipe[1] = fd[1];
		shell->redir.out_pipe = fd[1];
		shell->redir.pid = -1;
		shell->parent = 0;
		return (1);
	}
	else
	{
		if (fd[1] > 0)
		{
			if (close(fd[1]) == -1)
				return (-1);
		}
		if (dup2(fd[0], STDIN) == -1)
			return (-1);
		shell->redir.in_pipe = fd[0];
		shell->redir.pipe[0] = fd[0];
		return (2);
	}
}

static int	ft_input(t_shell *shell, char *str)
{
	if (shell->redir.in_fd > 0)
	{
		if (close(shell->redir.in_fd) == -1)
			return (ERROR);
	}
	shell->redir.in_fd = open(str, O_RDONLY, S_IRWXU);
	if (shell->redir.in_fd == -1)
		return (SUCCESS);
	if (dup2(shell->redir.in_fd, STDIN) == -1)
		return (ERROR);
	return (SUCCESS);
}

int			redir(t_shell *shell, t_final_command *cmd)
{
	int		i;

	i = 0;
	while (cmd->redir_in[i].redir)
	{
		if (cmd->redir_in[i].type == simple)
		{
			if (ft_input(shell, cmd->redir_in[i].redir) == ERROR)
				return (ERROR);
		}
		else
		{
			if (ft_heredoc(cmd->redir_in[i].redir) == ERROR)
				return (ERROR);
		}
		i++;
	}
	i = 0;
	while (cmd->redir_out[i].redir)
	{
		if (shell->redir.out_fd > 0)
		{	
			if (close(shell->redir.out_fd) == -1)
				return (ERROR);
		}
		if (cmd->redir_out[i].type == simple)
			shell->redir.out_fd = open(cmd->redir_out[i].redir, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
		else
			shell->redir.out_fd = open(cmd->redir_out[i].redir, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
		if (shell->redir.out_fd == -1)
		{
			error_redir(cmd->redir_out[i].redir);
			return (ERROR);
		}
		if (dup2(shell->redir.out_fd, STDOUT) == -1)
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}