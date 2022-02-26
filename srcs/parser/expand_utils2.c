/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 19:04:24 by sobouatt          #+#    #+#             */
/*   Updated: 2022/02/24 14:08:57 by sobouatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

char	*finish_var(char *str, int i, char c)
{
	str[i - 1] = c;
	str[i] = '\0';
	return (str);
}

int	init_cursors(t_command *cmd, t_token ***new_tokens,
size_t *cursors, size_t new_size)
{
	cursors[0] = 0;
	while (cmd->command[cursors[0]] != NULL)
		cursors[0] += 1;
	cursors[0] += new_size;
	cursors[1] = 0;
	cursors[2] = 0;
	cursors[3] = 0;
	*new_tokens = malloc(sizeof(**new_tokens) * cursors[0]);
	if (*new_tokens == NULL)
		return (free_cmd(cmd));
	return (SUCCESS);
}

int	count_tokens(t_token *token)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = token;
	if (!token)
		return (0);
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}
