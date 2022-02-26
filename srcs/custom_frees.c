/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_frees.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcorenti <rcorenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 12:52:36 by sobouatt          #+#    #+#             */
/*   Updated: 2022/02/26 01:56:35 by rcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	ft_free_exit(t_shell *shell)
{
	close_redir(shell);
	init_redir(shell);
	close(STDIN);
	close(STDOUT);
	close(STDERR);
	rl_clear_history();
	free_env(shell->env);
	perror("Error : ");
	return (ERROR);
}
