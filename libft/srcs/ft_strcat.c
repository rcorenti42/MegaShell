/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcorenti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 15:08:08 by rcorenti          #+#    #+#             */
/*   Updated: 2022/01/24 15:30:53 by rcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dest, const char *src)
{
	char	*ret;
	int		i;
	int		j;

	ret = (char *)malloc(sizeof(char) * (ft_strlen(dest)
				+ ft_strlen((char *)src) + 1));
	i = -1;
	if (dest)
		while (dest[++i])
			ret[i] = dest[i];
	j = -1;
	if (src)
	{
		while (src[++j])
		{
			ret[i] = src[j];
			i++;
		}
	}
	ret[i] = '\0';
	return (ret);
}
