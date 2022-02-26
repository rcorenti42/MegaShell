/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 07:55:34 by sobouatt          #+#    #+#             */
/*   Updated: 2022/02/24 14:38:33 by sobouatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_nb_of_quotes(t_char *token)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (token[i].c != '\0')
	{
		if ((token[i].c == '"' || token[i].c == '\'')
			&& token[i].inhib == 'x')
			quote++;
		i++;
	}
	return (quote);
}

t_char	*remove_quote(t_char *token, int i, int j)
{
	t_char	*new;
	int		quote;

	quote = get_nb_of_quotes(token);
	if (quote == 0)
		return (token);
	new = malloc(sizeof(t_token) * char_len(token));
	if (new == NULL)
	{
		free(token);
		return (NULL);
	}
	while (token[i].c != '\0')
	{
		if ((token[i].c == '"' || token[i].c == '\'') && token[i].inhib == 'x')
			i++;
		else
		{
			new[j].c = token[i].c;
			new[j++].inhib = token[i++].inhib;
		}
	}
	new[j].c = '\0';
	free(token);
	return (new);
}

t_command	*lexer_remove_quote(t_command *head)
{
	t_command	*node;
	int			i;

	node = head;
	while (node)
	{
		i = 0;
		while (node->command[i] != NULL)
		{
			node->command[i]->token
				= remove_quote(node->command[i]->token, 0, 0);
			if (node->command[i]->token == NULL)
			{
				free_cmd(head);
				return (NULL);
			}
			i++;
		}
		node = node->next;
	}
	return (head);
}
