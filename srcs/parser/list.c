/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 00:57:18 by sobouatt          #+#    #+#             */
/*   Updated: 2022/02/24 06:29:31 by sobouatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_lstnew(t_char *token, enum e_type type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
	{
		free(token);
		return (NULL);
	}
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

t_command	*ft_lstnew_cmd(void)
{
	t_command	*new;

	new = malloc(sizeof(t_command));
	if (!new)
		return (NULL);
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back_cmd(t_command **command, t_command *new)
{
	t_command	*tmp;

	tmp = *command;
	if (*command == NULL)
		*command = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}
