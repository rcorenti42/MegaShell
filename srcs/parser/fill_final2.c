/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_final2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 03:55:35 by sobouatt          #+#    #+#             */
/*   Updated: 2022/02/24 20:55:12 by sobouatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_final_command	*ft_lstnew_final(void)
{
	t_final_command	*new;

	new = malloc(sizeof(t_final_command));
	if (!new)
		return (NULL);
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back_final(t_final_command **command, t_final_command *new)
{
	t_final_command	*tmp;

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

int	get_tk_nb_tmp(t_token **command)
{
	int	i;

	i = 0;
	while (command[i] != NULL)
		i++;
	return (i);
}

int	get_redir_type(t_char *token)
{
	if (ft_charcmp(token, ">>") == 0 || ft_charcmp(token, "<<") == 0)
		return (doubles);
	return (simple);
}

char	*to_string(t_char *token)
{
	int		i;
	char	*str;

	i = 0;
	str = malloc(sizeof(char) * (char_len(token) + 1));
	if (!str)
	{
		free(token);
		return (NULL);
	}
	while (token[i].c != '\0')
	{
		str[i] = token[i].c;
		i++;
	}
	str[i] = '\0';
	return (str);
}
