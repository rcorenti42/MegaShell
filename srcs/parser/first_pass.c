/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_pass.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 20:01:34 by sobouatt          #+#    #+#             */
/*   Updated: 2022/02/25 01:01:35 by sobouatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			if ((tmp->type == token_pipe || tmp->type == token_operand)
				&& (node->type == token_pipe || node->type == token_operand))
				return (1);
		}
		tmp = node;
		node = node->next;
	}
	if (tmp->type == token_pipe || tmp->type == token_operand)
		return (1);
	return (0);
}

int	create_tokens(t_token **head, t_token **node, char *str, size_t pos)
{
	t_char	*token;

	token = NULL;
	while (pos < ft_strlen(str))
	{
		if (get_token(&token, str, &pos) == ERROR)
			return (ERROR);
		if (token == NULL)
			continue ;
		if (*head == NULL)
		{
			*head = ft_lstnew(token, get_token_type(token));
			if (*head == NULL)
				return (ERROR);
		}
		else
		{
			*node = ft_lstnew(token, get_token_type(token));
			if (*node == NULL)
				return (ERROR);
			ft_lstadd_back(head, *node);
		}
	}
	return (SUCCESS);
}

void	init_for_first_passs(t_char **token, t_token **head,
t_token **node, size_t *pos)
{
	*pos = 0;
	*head = NULL;
	*node = NULL;
	*token = NULL;
}

int	lexer_first_pass(char *str, t_token **tokens)
{
	size_t			pos;
	t_char			*token;
	t_token			*head;
	t_token			*node;

	init_for_first_passs(&token, &head, &node, &pos);
	if (create_tokens(&head, &node, str, pos) != 0)
	{	
		free_tokens(head);
		return (ERROR);
	}
	if (pipe_proxy(head) != 0)
	{
		free_tokens(head);
		display_syntax_error();
		return (ERROR);
	}
	*tokens = head;
	return (SUCCESS);
}
