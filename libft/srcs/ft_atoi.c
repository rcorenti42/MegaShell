/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcorenti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 08:31:12 by rcorenti          #+#    #+#             */
/*   Updated: 2022/02/11 16:10:57 by rcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_arg(char *arg)
{
	int	i;

	i = 1;
	if (arg[0] != '+' && arg[0] != '-' && (arg[0] > '9' || arg[0] < '0'))
		return (1);
	while (arg[i])
	{
		if (arg[i] > '9' && arg[i] < '0')
			return (1);
		i++;
	}
	return (0);
}

int	ft_atoi(char *str)
{
	int	i;
	int	neg;
	int	ret;

	i = 0;
	neg = 0;
	ret = 0;
	if (!str || check_arg(str))
		return (0);
	if (str[0] == '-' || str[0] == '+')
	{	
		if (str[0] == '-')
			neg++;
		i++;
	}
	while (str[i])
	{
		ret *= 10;
		ret += str[i] - '0';
		i++;
	}
	if (neg)
		ret = -ret;
	return (ret);
}
