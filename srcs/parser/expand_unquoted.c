/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_unquoted.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 22:04:52 by sobouatt          #+#    #+#             */
/*   Updated: 2022/02/21 22:07:07 by sobouatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand(t_command *cmd, size_t pos, t_char *word, t_env *env)
{
	t_char	*new;
	size_t	new_size;
	size_t	i;
	size_t	new_total_size;
	t_char	*replace_t_chars;
	t_token	*repl;
	t_token	**new_tokens;
	t_token	*cp;
	size_t	old_cursor;
	size_t	new_cursor;

	if (word->inhib == '\"')
	{
		new = expand_quoted(cmd->command[pos]->token, word, env);
		if (new == NULL)
			return (-1);
		free(cmd->command[pos]->token);
		cmd->command[pos]->token = new;
		return (0);
	}
	else
	{
		new_size = 0;
		replace_t_chars = expand_quoted(cmd->command[pos]->token, word, env);
		if (replace_t_chars == NULL)
			return (-1);
		repl = lexer_first_pass(t_char_to_char(replace_t_chars), env);
		free(replace_t_chars);
		repl = lexer_second_pass(repl);
		{
			cp = repl;
			while (cp != NULL)
			{
				cp = cp->next;
				new_size++;
			}
		}
		if (new_size == 0)
		{
			free(cmd->command[pos]->token);
			free(cmd->command[pos]);
			if (pos == 0)
				cmd->command[pos] = cmd->command[pos + 1];
			else
				pos--;
			i = pos;
			while (cmd->command[pos + 1] != NULL)
			{
				cmd->command[pos + 1] = cmd->command[pos + 2];
				cmd->command[pos]->next = cmd->command[pos + 1];
				i++;
			}
		}
		else if (new_size == 1)
		{
			free(cmd->command[pos]->token);
			free(cmd->command[pos]);
			cmd->command[pos] = repl;
			cmd->command[pos]->next = cmd->command[pos + 1];
			if (pos > 0)
				cmd->command[pos - 1]->next = cmd->command[pos];
		}
		else
		{
			new_total_size = 0;
			while (cmd->command[new_total_size] != NULL)
				new_total_size += 1;
			new_total_size += new_size;
			new_tokens = malloc(sizeof(*new_tokens) * new_total_size);
			if (new_tokens == NULL)
			{
				free_tokens(repl);
				return (-1);
			}
			old_cursor = 0;
			new_cursor = 0;
			while (old_cursor < pos)
			{
				new_tokens[new_cursor] = cmd->command[old_cursor];
				old_cursor++;
				new_cursor++;
			}
			while (repl != NULL)
			{
				new_tokens[new_cursor] = repl;
				repl = repl->next;
				new_cursor++;
			}
			free(cmd->command[old_cursor]->token);
			free(cmd->command[old_cursor]);
			old_cursor++;
			while (cmd->command[old_cursor] != NULL)
			{
				new_tokens[new_cursor] = cmd->command[old_cursor];
				old_cursor++;
				new_cursor++;
			}
			new_tokens[new_cursor] = NULL;
			i = 0;
			while (i < new_total_size - 1)
			{
				new_tokens[i]->next = new_tokens[i + 1];
				i++;
			}
			free(cmd->command);
			cmd->command = new_tokens;
		}
	}
	return (0);
}