/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:23:30 by sobouatt          #+#    #+#             */
/*   Updated: 2022/02/25 00:44:22 by sobouatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	proxy(char *str)
{
	int	i;
	int	quote;
	int	last;

	i = 0;
	quote = 0;
	if (str == NULL)
		return (0);
	last = 0;
	while (str[i])
	{
		if ((str[i] == '"' || str[i] == '\'') && quote == 0)
			last = i;
		quote = treat_quote(str[i], quote);
		i++;
	}
	return (quote);
}

t_token	*dispatch_tokens(char *str)
{
	t_token		*tk_head;
	int			ret;

	ret = lexer_first_pass(str, &tk_head);
	if (ret == ERROR)
		return (NULL);
	tk_head = lexer_second_pass(tk_head);
	return (tk_head);
}

t_command	*dispatch_cmd(t_token *tk_head, t_env *env)
{
	t_command	*cmd_head;

	cmd_head = lexer_split_cmd(tk_head);
	if (cmd_head == NULL)
		return (NULL);
	cmd_head = lexer_expand(cmd_head, env);
	cmd_head = lexer_remove_quote(cmd_head);
	return (cmd_head);
}

int	create_node_final(t_final_command **final_head,
t_final_command **final_tmp, t_command *cmd_head)
{
	if (cmd_head == NULL)
	{
		*final_head = ft_lstnew_final();
		if (*final_head == NULL)
			return (cmd_free_broke(cmd_head));
	}
	else
	{
		*final_tmp = ft_lstnew_final();
		if (*final_tmp == NULL)
			return (cmd_free_broke(cmd_head));
		ft_lstadd_back_final(final_head, *final_tmp);
	}
	return (SUCCESS);
}
