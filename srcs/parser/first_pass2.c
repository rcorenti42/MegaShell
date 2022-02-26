/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_pass2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 00:50:45 by sobouatt          #+#    #+#             */
/*   Updated: 2022/02/25 00:05:56 by sobouatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_charcmp(t_char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (s1 && s2)
	{
		while (s1[i].c != '\0' && s2[i])
		{
			if (s1[i].c != s2[i])
				return ((unsigned char)s1[i].c - (unsigned char)s2[i]);
			i++;
		}
	}
	return ((unsigned char)s1[i].c - (unsigned char)s2[i]);
}

enum e_type	get_token_type(t_char *str)
{
	if (ft_charcmp(str, "<") == 0 || ft_charcmp(str, "<<") == 0
		|| ft_charcmp(str, ">") == 0 || ft_charcmp(str, ">>") == 0)
		return (token_operand);
	if (str[0].c == '|')
		return (token_pipe);
	else
		return (token_word);
}

int	treat_pipe(size_t *pos, t_char *token)
{
	token[0].c = '|';
	(*pos)++;
	token[1].c = '\0';
	return (0);
}
