/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcorenti <rcorenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 21:52:10 by sobouatt          #+#    #+#             */
/*   Updated: 2022/02/23 01:05:34 by rcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(t_command *head)
{
	t_command	*tmp;

	while (head)
	{
		free(head->command);
		tmp = head;
		head = head->next;
		free(tmp);
	}	
}

int	proxy(char *str)
{
	int	i;
	int	quote;
	int	last;

	i = 0;
	quote = 0;
	if (str == NULL)
		return (0);
	last = 0;
	while (str[i])
	{
		if ((str[i] == '"' || str[i] == '\'') && quote == 0)
			last = i;
		quote = treat_quote(str[i], quote);
		i++;
	}
	return (quote);
}

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
			error = 1;
		if (error != 0)
		{
			free_final(param);
			write(2, "megashell: syntax error\n",
				ft_strlen("megashell: syntax error\n"));
			return (NULL);
		}
		ptr = ptr->next;
	}
	return (param);
}

t_final_command	*lexer(char *str, t_env *env)
{
	t_token			*tk_head;
	t_command		*cmd_head;
	t_final_command	*final_head;

	//printf("Salut\n");
	//return (NULL);
	if (proxy(str) != 0)
		return (display_syntax_error(env));
	tk_head = lexer_first_pass(str, env);
	if (tk_head == NULL)
		return (NULL);
	tk_head = lexer_second_pass(tk_head);
	if (tk_head == NULL)
		return (NULL);
	cmd_head = lexer_split_cmd(tk_head);
	if (cmd_head == NULL)
		return (NULL);
	cmd_head = lexer_expand(cmd_head, env);
	if (cmd_head == NULL)
		return (NULL);
	cmd_head = lexer_remove_quote(cmd_head);
	if (cmd_head == NULL)
		return (NULL);
	final_head = lexer_fill_final(cmd_head);
	if (cmd_head == NULL)
		return (NULL);
	free_tokens(cmd_head->command[0]);
	free_cmd(cmd_head);
	return (detect_errors(final_head));
}
