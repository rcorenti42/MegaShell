/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 08:21:32 by sobouatt          #+#    #+#             */
/*   Updated: 2022/02/20 04:28:27 by sobouatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_char	*char_chr(t_char *str, int c)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i].c != '\0')
	{
		if (str[i].c == c && str[i].inhib != '\'' && str[i + 1].c != '\0')
		{
			if (str[i + 1].c != '\"' && str[i + 1].c != ' ')
				return (str + i);
		}
		i++;
	}
	return (NULL);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[j])
		j++;
	while (i <= j)
	{
		if (s[i] == c)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}

char	*ft_strstr(char *str, char *to_find)
{
	int		i;
	int		j;

	if (to_find[0] == '\0')
		return (str);
	i = 0;
	while (str[i])
	{
		j = 0;
		if (str[i] == to_find[j])
		{
			while (str[i + j] == to_find[j])
			{
				j++;
				if (!to_find[j])
					return (&str[i]);
			}
		}
		i++;
	}
	return (0);
}

int	get_expand_size(t_char *word)
{
	int	i;

	i = 1;
	if (word[i].c == '?')
		return (2);
	while (word[i].c != '\0' && isdigit(word[i].c))
		i++;
	if (i != 1)
		return (i);
	while (word[i].c != '\0')
	{
		if (word[i].c == '\"' || word[i].c == ' ' || word[i].c == '\''
			|| word[i].c == '$' || word[i].c == '+' || word[i].c == '-'
			|| word[i].c == '=' || word[i].c == '/' || word[i].c == '%'
			|| word[i].c == '?')
			return (i);
		i++;
	}
	return (i);
}

char	*get_var(t_char *word)
{
	char	*str;
	int		i;

	str = malloc(sizeof(char) * ((get_expand_size(word) + 1)));
	i = 1;
	if (word[i].c == '?')
	{
		str[i - 1] = '?';
		str[i] = '\0';
		return (str);
	}	
	while (word[i].c != '\0' && isdigit(word[i].c))
	{
		str[i - 1] = word[i].c;
		i++;
	}
	if (i != 1)
	{
		str[i - 1] = '=';
		str[i] = '\0';
		return (str);
	}
	while (word[i].c != '\0')
	{
		if (word[i].c == '\"' || word[i].c == ' ' || word[i].c == '\''
			|| word[i].c == '$' || word[i].c == '+' || word[i].c == '-'
			|| word[i].c == '=' || word[i].c == '/' || word[i].c == '%'
			|| word[i].c == '_' || word[i].c == '?')
				break ;
		str[i - 1] = word[i].c;
		i++;
	}
	str[i - 1] = '=';
	str[i] = '\0';
	return (str);
}

