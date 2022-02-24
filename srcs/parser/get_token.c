/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:17:39 by sobouatt          #+#    #+#             */
/*   Updated: 2022/02/24 11:50:36 by sobouatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cut_operand(t_char *token, char *str, size_t *pos)
{
	int	i;

	i = 0;
	if (token == NULL)
		return (-1);
	if (str[*pos] == '|')
		return (treat_pipe(pos, token));
	token[i++].c = str[(*pos)++];
	if ((str[*pos] == '<' && str[*pos - 1] == '<')
		|| (str[*pos] == '>' && str[*pos - 1] == '>'))
		token[i++].c = str[(*pos)++];
	token[i].c = '\0';
	return (0);
}

int	get_token(t_char **token, char *str, size_t *pos)
{
	size_t		i;
	int			quote;

	*token = NULL;
	*pos += skip_spaces(str + *pos);
	quote = get_token_size(str, *pos);
	if (quote == 0)
		return (0);
	*token = malloc(sizeof(t_char) * (quote + 1));
	if (!(*token))
		return (ERROR);
	if (str[*pos] == '<' || str[*pos] == '>'
		|| str[*pos] == '|' || token == NULL)
		return (cut_operand(*token, str, pos));
	i = 0;
	quote = 0;
	while (str[*pos])
	{
		quote = treat_quote(str[*pos], quote);
		if ((str[*pos] == ' ' || str[*pos] == '|'
				|| str[*pos] == '<' || str[*pos] == '>') && quote == 0)
			break ;
		(*token)[i++].c = str[(*pos)++];
	}
	(*token)[i].c = '\0';
	*pos += skip_spaces(str + *pos);
	return (0);
}
