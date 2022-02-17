/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 21:52:10 by sobouatt          #+#    #+#             */
/*   Updated: 2022/02/17 08:27:39 by rcorenti         ###   ########.fr       */
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

	i = 0;
	quote = 0;
	if (str == NULL)
		return (0);
	while (str[i])
	{
		quote = treat_quote(str[i], quote);
		i++;
	}
	return (quote);
}

/*
METHOD FOR LEXER_SPLIT_CMD : TAKE A TK_NODE AND RETURN
EITHER THE NUMBER OF TOKENS OR THE NUMBER OF TOKENS BEFORE 
A TOKEN OF TYPE PIPE
*/

t_final_command	*lexer(char *str, t_env *env)
{
	t_token		*tk_head;
	t_command	*cmd_head;
	t_final_command *final_head;

	if (proxy(str) != 0)
	{
		printf("quoting error o_o\n");
		return (NULL);
	}
	tk_head = lexer_first_pass(str);
	if (tk_head == NULL)
		return (NULL);
	tk_head = lexer_second_pass(tk_head);
	cmd_head = lexer_split_cmd(tk_head);
	cmd_head = lexer_expand(cmd_head, env);
	cmd_head = lexer_remove_quote(cmd_head);
	final_head = lexer_fill_final(cmd_head);
	free_tokens(cmd_head->command[0]);
	free_cmd(cmd_head);
	return (final_head);
}
