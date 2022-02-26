/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_unquoted.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 22:04:52 by sobouatt          #+#    #+#             */
/*   Updated: 2022/02/25 11:02:46 by sobouatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	double_quote(t_command *cmd, t_char *word, t_env *env, size_t pos)
{
	t_char	*new;

	new = expand_quoted(cmd->command[pos]->token, word, env);
	if (new == NULL)
		return (-1);
	free(cmd->command[pos]->token);
	cmd->command[pos]->token = new;
	return (0);
}

void	size_zero(t_command *cmd, size_t *pos)
{
	size_t	i;

	free(cmd->command[*pos]->token);
	free(cmd->command[*pos]);
	if (*pos == 0)
		cmd->command[*pos] = cmd->command[*pos + 1];
	else
		(*pos)--;
	i = *pos;
	while (cmd->command[i + 1] != NULL)
	{
		cmd->command[i + 1] = cmd->command[i + 2];
		cmd->command[i]->next = cmd->command[i + 1];
		i++;
	}
}

void	size_one(t_command *cmd, t_token *repl, size_t pos)
{
	free(cmd->command[pos]->token);
	free(cmd->command[pos]);
	cmd->command[pos] = repl;
	cmd->command[pos]->next = cmd->command[pos + 1];
	if (pos > 0)
		cmd->command[pos - 1]->next = cmd->command[pos];
}

//new_total_size
//new_cursor
//old_cursor
//i

int	size_other(t_command *cmd, t_token *repl, size_t new_size, size_t pos)
{
	size_t	cursors[4];
	t_token	**new_tokens;

	if (init_cursors(cmd, &new_tokens, cursors, new_size) == ERROR)
		return (-1);
	while (cursors[2] < pos)
		new_tokens[cursors[1]++] = cmd->command[cursors[2]++];
	while (repl != NULL)
	{
		new_tokens[cursors[1]++] = repl;
		repl = repl->next;
	}
	free(cmd->command[cursors[2]]->token);
	free(cmd->command[cursors[2]++]);
	while (cmd->command[cursors[2]] != NULL)
		new_tokens[cursors[1]++] = cmd->command[cursors[2]++];
	new_tokens[cursors[1]] = NULL;
	cursors[3] = 0;
	while (cursors[3]++ < cursors[0] - 1)
		new_tokens[cursors[3] - 1]->next = new_tokens[cursors[3]];
	free(cmd->command);
	cmd->command = new_tokens;
	return (SUCCESS);
}

int	expand(t_command *cmd, size_t pos, t_char *word, t_env *env)
{
	size_t	new_size;
	t_char	*replace_t_chars;
	t_token	*repl;

	if (word->inhib == '\"')
		return (double_quote(cmd, word, env, pos));
	new_size = 0;
	replace_t_chars = expand_quoted(cmd->command[pos]->token, word, env);
	if (replace_t_chars == NULL)
		return (-1);
	if (lexer_first_pass(t_char_to_char(replace_t_chars), &repl) != SUCCESS)
	{
		free(replace_t_chars);
		return (-1);
	}
	free(replace_t_chars);
	repl = lexer_second_pass(repl);
	new_size = count_tokens(repl);
	if (new_size == 0)
		size_zero(cmd, &pos);
	else if (new_size == 1)
		size_one(cmd, repl, pos);
	else if (size_other(cmd, repl, new_size, pos) == ERROR)
		return (broke_free2(repl, ERROR));
	return (SUCCESS);
}
