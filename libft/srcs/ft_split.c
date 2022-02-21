/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcorenti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 03:07:06 by rcorenti          #+#    #+#             */
/*   Updated: 2022/02/21 10:28:43 by rcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_sep(const char *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (*s)
	{
		if (*s == c)
			j = 0;
		else if (!j)
		{
			j = 1;
			i++;
		}
		s++;
	}
	return (i);
}

static int	ft_len_split(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char	**ft_spliting(char **tab, const char *s, char c)
{
	int	i;
	int	len;

	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			len = ft_len_split(s, c);
			tab[i] = (char *)malloc(sizeof(char) * (len + 1));
			if (!tab[i])
				return (NULL);
			ft_memcpy(tab[i], s, (size_t)len);
			tab[i][len] = '\0';
			s += len;
			i++;
		}
	}
	return (tab);
}

char	**ft_split(const char *s, char c)
{
	char	**tab;
	int		count;

	count = ft_count_sep(s, c);
	tab = (char **)malloc(sizeof(char *) * (count + 1));
	if (!tab)
		return (NULL);
	tab[count] = NULL;
	tab = ft_spliting(tab, s, c);
	return (tab);
}
