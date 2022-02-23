/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_pass.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 20:01:34 by sobouatt          #+#    #+#             */
/*   Updated: 2022/02/22 03:59:36 by sobouatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_char	*cut_operand(t_char *token, char *str, size_t *pos)
{
	int	i;

	i = 0;
	if (token == NULL)
		return (NULL);
	if (str[*pos] == '|')
		return (treat_pipe(pos, token));
	token[i++].c = str[(*pos)++];
	if ((str[*pos] == '<' && str[*pos - 1] == '<')
		|| (str[*pos] == '>' && str[*pos - 1] == '>'))
		token[i++].c = str[(*pos)++];
	token[i].c = '\0';
	return (token);
}

t_char	*get_token(char *str, size_t *pos)
{
	size_t		i;
	int			quote;
	t_char		*token;

	token = NULL;
	*pos += skip_spaces(str + *pos);
	quote = get_token_size(str, *pos);
	if (quote == 0)
		return (NULL);
	token = malloc(sizeof(t_char) * (quote + 1));
	if (str[*pos] == '<' || str[*pos] == '>'
		|| str[*pos] == '|' || token == NULL)
		return (cut_operand(token, str, pos));
	i = 0;
	quote = 0;
	while (str[*pos])
	{
		quote = treat_quote(str[*pos], quote);
		if ((str[*pos] == ' ' || str[*pos] == '|'
				|| str[*pos] == '<' || str[*pos] == '>') && quote == 0)
			break ;
		token[i++].c = str[(*pos)++];
	}
	token[i].c = '\0';
	return (token);
}

int	pipe_proxy(t_token *head)
{
	t_token	*tmp;
	t_token	*node;

	tmp = NULL;
	node = head;
	if (!node)
		return (0);
	if (node->type == token_pipe)
		return (1);
	while (node)
	{
		if (tmp != NULL)
		{
			if (tmp->type == token_pipe && node->type == token_pipe)
				return (1);
		}
		tmp = node;
		node = node->next;
	}
	if (tmp->type == token_pipe)
		return (1);
	return (0);
}

void	init_for_first_passs(t_char **tk, t_token **hd,
t_token **nod, size_t *pos)
{
	*pos = 0;
	*hd = NULL;
	*nod = NULL;
	*tk = NULL;
}

t_token	*lexer_first_pass(char *str, t_env *env)
{
	size_t			pos;
	t_char			*token;
	t_token			*head;
	t_token			*node;

	init_for_first_passs(&token, &head, &node, &pos);
	while (pos < ft_strlen(str))
	{
		token = get_token(str, &pos);
		if (token == NULL)
		{
			free_tokens(head);
			return (NULL);
		}
		if (head == NULL)
			head = ft_lstnew(token, get_token_type(token));
		else
		{
			node = ft_lstnew(token, get_token_type(token));
			ft_lstadd_back(&head, node);
		}
	}
	if (pipe_proxy(head))
		return (display_syntax_error(env));
	return (head);
}
