/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 00:57:28 by sobouatt          #+#    #+#             */
/*   Updated: 2022/02/15 08:23:59 by sobouatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_spaces(char *str)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]) == 1)
		i++;
	return (i);
}

int	treat_quote(char c, int quote)
{
	if (c == '\'' && quote != 2)
	{
		if (quote == 0)
			return (1);
		else
			return (0);
	}
	if (c == '"' && quote != 1)
	{
		if (quote == 0)
			return (2);
		else
			return (0);
	}
	return (quote);
}

void	free_tokens(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token;
		token = token->next;
		free(tmp->token);
		free(tmp);
	}
}

int	get_token_size(char *str, int pos)
{
	int	token_size;
	int	quote;

	token_size = pos;
	quote = 0;
	if (str[pos] == '|')
		return (1);
	while (str[pos] != '\0')
	{
		quote = treat_quote(str[pos], quote);
		if ((str[pos] == ' ' || str[pos] == '|') && quote == 0)
			return (pos - token_size);
		pos++;
	}
	return (pos - token_size);
}

char	*find_env(char *str, t_char *word)
{
	int		i;
	char	*to_find;

	i = 0;
	to_find = get_var(word);
	while (to_find[i] && str[i])
	{
		if (str[i] != to_find[i])
		{
			free(to_find);
			return (NULL);
		}
		i++;
	}
	free(to_find);
	return (str + i);
}
