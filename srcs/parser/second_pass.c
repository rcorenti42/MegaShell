/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_pass.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 20:17:07 by sobouatt          #+#    #+#             */
/*   Updated: 2022/02/24 14:32:07 by sobouatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_char	*bruh(t_token *command)
{
	if (command == NULL)
		return (NULL);
	return (char_chr(command->token, '$'));
}

int	free_cmd(t_command *head)
{
	t_command	*tmp;

	while (head)
	{
		free(head->command);
		tmp = head;
		head = head->next;
		free(tmp);
	}
	return (ERROR);
}

t_char	*inhib_quotes(t_char *token)
{
	int		i;
	char	quote;

	i = 0;
	while (token[i].c != '\0')
	{
		if (token[i].c == '"' || token[i].c == '\'')
		{
			quote = token[i].c;
			token[i].inhib = 'x';
			i++;
			while (token[i].c != quote)
				token[i++].inhib = quote;
			token[i].inhib = 'x';
		}
		else
			token[i].inhib = 'x';
		i++;
	}
	return (token);
}

t_char	*remove_quotes(t_char *token)
{
	int		i;
	int		j;
	t_char	*new;

	i = 0;
	j = 0;
	new = malloc(sizeof(t_char) * (char_len(token) + 1));
	if (!new)
		return (NULL);
	while (token[i].c != '\0')
	{
		if ((token[i].c == '"' || token[i].c == '\'')
			&& token[i].inhib == 'x')
			i++;
		else
		{
			new[j].c = token[i].c;
			new[j].inhib = token[i].inhib;
			j++;
			i++;
		}
	}
	new[j].c = '\0';
	return (new);
}

t_token	*lexer_second_pass(t_token *head)
{
	t_char	*tmp;
	t_token	*node;

	node = head;
	while (node)
	{
		tmp = inhib_quotes(node->token);
		node->token = tmp;
		node = node->next;
	}
	return (head);
}
