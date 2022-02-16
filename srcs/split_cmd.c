/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 08:11:52 by sobouatt          #+#    #+#             */
/*   Updated: 2022/02/16 14:02:52 by rcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_tk_nb(t_token *node)
{
	int	i;

	i = 1;
	while (node)
	{
		if (node->type == PIPE)
			return (i);
		node = node->next;
		i++;
	}
	return (i);
}

void	prepare_node(t_command **cmd_head, t_command **cmd_node)
{
	if (*cmd_head == NULL)
	{
		*cmd_head = ft_lstnew_cmd();
		*cmd_node = *cmd_head;
	}
	else
	{
		*cmd_node = ft_lstnew_cmd();
		ft_lstadd_back_cmd(cmd_head, *cmd_node);
	}
}

void	init_things(t_token **tk_node, t_command **cmd_head,
t_command **cmd_node, t_token **tk_head)
{
	*cmd_head = NULL;
	*cmd_node = NULL;
	*tk_node = *tk_head;
}

t_command	*lexer_split_cmd(t_token *tk_head)
{
	t_token		*tk_node;
	t_command	*cmd_head;
	t_command	*cmd_node;
	int			i;

	init_things(&tk_node, &cmd_head, &cmd_node, &tk_head);
	while (tk_node)
	{
		prepare_node(&cmd_head, &cmd_node);
		i = get_tk_nb(tk_node);
		cmd_node->command = malloc(sizeof(t_token *) * (i + 1));
		i = 0;
		while (tk_node)
		{
			if (tk_node->type == PIPE)
			{
				tk_node = tk_node->next;
				break ;
			}
			cmd_node->command[i++] = tk_node;
			tk_node = tk_node->next;
		}
		cmd_node->command[i] = NULL;
	}
	return (cmd_head);
}
