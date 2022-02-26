/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 08:11:52 by sobouatt          #+#    #+#             */
/*   Updated: 2022/02/24 20:37:39 by sobouatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_tk_nb(t_token *node)
{
	int	i;

	i = 1;
	while (node)
	{
		if (node->type == token_pipe)
			return (i);
		node = node->next;
		i++;
	}
	return (i);
}

int	prepare_node(t_command **cmd_head, t_command **cmd_node)
{
	if (*cmd_head == NULL)
	{
		*cmd_head = ft_lstnew_cmd();
		if (*cmd_head == NULL)
			return (ERROR);
		*cmd_node = *cmd_head;
	}
	else
	{
		*cmd_node = ft_lstnew_cmd();
		if (*cmd_node == NULL)
		{
			free_cmd(*cmd_head);
			return (ERROR);
		}
		ft_lstadd_back_cmd(cmd_head, *cmd_node);
	}
	return (SUCCESS);
}

void	init_things(t_token **tk_node, t_command **cmd_head,
t_command **cmd_node, t_token **tk_head)
{
	*cmd_head = NULL;
	*cmd_node = NULL;
	*tk_node = *tk_head;
}

int	next_break(t_token **tk_node)
{
	if ((*tk_node)->type == token_pipe)
	{
		(*tk_node) = (*tk_node)->next;
		return (1);
	}
	return (0);
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
		if (prepare_node(&cmd_head, &cmd_node) == ERROR)
			return (free_tokens(tk_head));
		i = get_tk_nb(tk_node);
		cmd_node->command = malloc(sizeof(t_token *) * (i + 1));
		if (cmd_node == NULL)
			return (free_tokens(tk_head));
		i = 0;
		while (tk_node)
		{
			if (next_break(&tk_node) == 1)
				break ;
			cmd_node->command[i++] = tk_node;
			tk_node = tk_node->next;
		}
		cmd_node->command[i] = NULL;
	}
	return (cmd_head);
}
