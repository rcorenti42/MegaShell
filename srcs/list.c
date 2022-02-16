/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 00:57:18 by sobouatt          #+#    #+#             */
/*   Updated: 2022/02/16 13:49:31 by rcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_lstnew(t_char *token, int type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	new->type = type;
	new->token = token;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*tmp;

	if (!lst)
		return ;
	tmp = *lst;
	if (*lst == NULL)
		*lst = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	ft_lstadd_front(t_token **lst, t_token *new)
{
	if (lst && new)
	{
		new->next = *lst;
		*lst = new;
	}
}
