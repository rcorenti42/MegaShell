/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 21:52:10 by sobouatt          #+#    #+#             */
/*   Updated: 2022/02/25 18:09:24 by sobouatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_final_command	*detect_errors(t_final_command *param)
{
	t_final_command	*ptr;
	int				error;

	ptr = param;
	while (ptr != NULL)
	{
		error = 0;
		if (ptr->redir_in == NULL || ptr->redir_out == NULL
			|| ptr->args == NULL)
		{
			g_signal = 2;
			free_final(param);
			write(2, "megashell: syntax error\n",
				ft_strlen("megashell: syntax error\n"));
			return (NULL);
		}
		ptr = ptr->next;
	}
	return (param);
}

t_command	*lexer_expand(t_command *head, t_env *env)
{
	t_command	*node;
	t_char		*chr_rt;
	int			i;

	node = head;
	while (node)
	{
		i = -1;
		while (node->command[++i] != NULL)
		{
			chr_rt = char_chr(node->command[i]->token, '$');
			while (chr_rt != NULL)
			{
				if (expand(node, i, chr_rt, env) != 0)
				{
					free_cmd(head);
					return (NULL);
				}
				chr_rt = bruh(node->command[i]);
			}
		}
		node = node->next;
	}
	return (head);
}

t_final_command	*lexer_fill_final(t_command *cmd_head)
{
	t_final_command	*final_head;
	t_final_command	*final_tmp;
	t_command		*cmd_tmp;

	cmd_tmp = cmd_head;
	final_tmp = NULL;
	final_head = NULL;
	while (cmd_tmp)
	{
		if (create_node_final(&final_head, &final_tmp, cmd_head) == ERROR)
			return (NULL);
		final_tmp->redir_out = fill_out(cmd_tmp->command);
		final_tmp->redir_in = fill_in(cmd_tmp->command);
		if (final_tmp->redir_in != NULL && final_tmp->redir_out != NULL)
			final_tmp->args = fill_args(cmd_tmp->command);
		else
			final_tmp->args = NULL;
		cmd_tmp = cmd_tmp->next;
	}
	return (final_head);
}

t_final_command	*lexer(char *str, t_env *env)
{
	t_token			*tk_head;
	t_command		*cmd_head;
	t_final_command	*final_head;

	if (proxy(str) != 0)
		return (display_syntax_error());
	tk_head = dispatch_tokens(str);
	if (!tk_head)
		return (NULL);
	cmd_head = dispatch_cmd(tk_head, env);
	if (cmd_head == NULL)
		return (NULL);
	final_head = lexer_fill_final(cmd_head);
	if (final_head == NULL)
		return (NULL);
	free_tokens(cmd_head->command[0]);
	free_cmd(cmd_head);
	return (detect_errors(final_head));
}
