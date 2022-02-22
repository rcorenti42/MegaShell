/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_pass.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcorenti <rcorenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 20:01:34 by sobouatt          #+#    #+#             */
/*   Updated: 2022/02/21 22:13:35 by rcorenti         ###   ########.fr       */
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

enum e_type	get_token_type(t_char *str)
{
	if (!ft_charcmp(str, "<") || !ft_charcmp(str, "<<")
		|| !ft_charcmp(str, ">") || !ft_charcmp(str, ">>"))
		return (token_operand);
	if (str[0].c == '|')
		return (token_pipe);
	else
		return (token_word);
}

t_char	*treat_pipe(int *pos, t_char *token)
{
	token[0].c = '|';
	(*pos)++;
	token[1].c = '\0';
	return (token);
}

t_char *cut_operand(char *str, int *pos, t_char *token)
{
	int i;

	i = 0;
	token[i++].c = str[(*pos)++];
	if (ft_strncmp(str + *pos, "<<", 2) == 0 || ft_strncmp(str + *pos, ">>", 2) == 0)
		token[i++].c = str[(*pos)++];
	token[i].c = '\0';
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
	if (str[*pos] == '<' || str[*pos] == '>')
	{
		token[i++].c = str[(*pos)++];
		if ((str[*pos] == '<' && str[*pos - 1] == '<') || (str[*pos] == '>' && str[*pos - 1] == '>'))
			token[i++].c = str[(*pos)++];
		token[i].c = '\0';
		return (token);
	}
	if (str[*pos] == '|')
		return (treat_pipe(pos, token));
	while (str[*pos])
	{
		quote = treat_quote(str[*pos], quote);
		if ((str[*pos] == ' ' || str[*pos] == '|' || str[*pos] == '<' || str[*pos] == '>') && quote == 0)
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

t_token	*lexer_first_pass(char *str)
{
	int				pos;
	t_char			*token;
	enum e_type		type;
	t_token			*head;
	t_token			*node;

	head = NULL;
	node = NULL;
	token = NULL;
	pos = 0;
	while ((size_t)pos < ft_strlen(str))
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
	if (head == NULL)
		return (NULL);
	if (pipe_proxy(head))
	{
		write(2, "megashell: syntax error\n",
			ft_strlen("megashell: syntax error\n"));
		free_tokens(head);
		head = NULL;
	}
	return (head);
}