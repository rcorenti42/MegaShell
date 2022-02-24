/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 00:57:28 by sobouatt          #+#    #+#             */
/*   Updated: 2022/02/24 02:37:06 by sobouatt         ###   ########.fr       */
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

void	*free_tokens(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token;
		token = token->next;
		free(tmp->token);
		free(tmp);
	}
	return (NULL);
}

int	get_token_size(char *str, int pos)
{
	int	token_size;
	int	quote;

	token_size = pos;
	quote = 0;
	if ((ft_strncmp(str + pos, ">>", 2) == 0)
		|| ft_strncmp(str + pos, "<<", 2) == 0)
		return (2);
	if (str[pos] == '|' || str[pos] == '<' || str[pos] == '>')
		return (1);
	while (str[pos] != '\0')
	{
		quote = treat_quote(str[pos], quote);
		if ((str[pos] == '<' || str[pos] == '>') && quote == 0)
			return (pos - token_size);
		if ((str[pos] == ' ' || str[pos] == '|') && quote == 0)
			return (pos - token_size);
		pos++;
	}
	return (pos - token_size);
}

char	*find_env(char *str, char *var)
{
	int		i;

	i = 0;
	if (var[i] == '?')
		return (ft_itoa(g_signal));
	while (var[i] && str[i])
	{
		if (str[i] != var[i])
			return (NULL);
		i++;
	}
	return (str + i);
}
