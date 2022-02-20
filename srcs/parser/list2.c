/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 04:24:59 by sobouatt          #+#    #+#             */
/*   Updated: 2022/02/15 02:17:38 by sobouatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*ft_lstnew_cmd(void)
{
	t_command	*new;

	new = malloc(sizeof(t_command));
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
