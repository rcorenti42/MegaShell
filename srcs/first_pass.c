/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_pass.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 20:01:34 by sobouatt          #+#    #+#             */
/*   Updated: 2022/02/16 14:01:21 by rcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_charcmp(t_char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i].c != '\0' || s2[i])
	{
		if (s1[i].c != s2[i])
			return ((unsigned char)s1[i].c - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int	get_token_type(t_char *str)
{
	if (!ft_charcmp(str, ">"))
		return (REDIR);
	if (!ft_charcmp(str, ">>"))
		return (APPEND);
	if (!ft_charcmp(str, "<"))
		return (INPUT);
	if (!ft_charcmp(str, "<<"))
		return (DOC);
	if (str[0].c == '|')
		return (PIPE);
	return (CMD);
}

t_char	*treat_pipe(int *pos, t_char *token)
{
	token[0].c = '|';
	(*pos)++;
	token[1].c = '\0';
	return (token);
}

t_char	*get_token(char *str, int *pos)
{
	int		i;
	t_char	*token;
	int		quote;

	*pos += skip_spaces(str + *pos);
	quote = get_token_size(str, *pos);
	if (quote == 0)
		return (NULL);
	token = malloc(sizeof(t_char) * (quote + 1));
	quote = 0;
	i = 0;
	if (str[*pos] == '|')
		return (treat_pipe(pos, token));
	while (str[*pos])
	{
		quote = treat_quote(str[*pos], quote);
		if ((str[*pos] == ' ' || str[*pos] == '|') && quote == 0)
			break ;
		token[i].c = str[(*pos)];
		i++;
		(*pos)++;
	}
	token[i].c = '\0';
	return (token);
}

t_token	*lexer_first_pass(char *str)
{
	int				pos;
	t_char			*token;
	int				type;
	t_token			*head;
	t_token			*node;

	head = NULL;
	node = NULL;
	token = NULL;
	pos = 0;
	while (pos < ft_strlen(str))
	{
		token = get_token(str, &pos);
		if (token == NULL)
			break ;
		type = get_token_type(token);
		if (head == NULL)
			head = ft_lstnew(token, type);
		else
		{
			node = ft_lstnew(token, type);
			ft_lstadd_back(&head, node);
		}
	}
	return (head);
}
