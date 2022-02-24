/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 04:56:37 by sobouatt          #+#    #+#             */
/*   Updated: 2022/02/24 02:23:24 by sobouatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	to_malloc(long n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		len++;
		n = -n;
	}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

int	init_nb(int n)
{
	int	nb;

	if (n < 0)
		nb = n * -1;
	else
		nb = n;
	return (nb);
}

char	*ft_itoa(int n)
{
	unsigned int	nb;
	int				len;
	char			*str;

	nb = init_nb(n);
	len = to_malloc(n);
	str = malloc(len * sizeof(char) + 1);
	if (str == NULL)
		return (NULL);
	str[len--] = '\0';
	if (n == 0)
	{
		str[0] = '0';
		return (str);
	}
	while (nb > 0)
	{
		str[len--] = nb % 10 + 48;
		nb = nb / 10;
	}
	return (str);
}
