/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcorenti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 21:51:30 by rcorenti          #+#    #+#             */
/*   Updated: 2022/01/25 21:56:31 by rcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

#include <stdlib.h>
#include <unistd.h.h>

int	ft_strlen(char *str);
int	ft_strcmp(const char *s1, const char *s2);
char	*ft_strcat(char *dest, const char *src);
void	ft_putstr_fd(char*str, int fd);
void	ft_putendl_fd(char *str, int fd);
void	*ft_memdel(void *ptr);

#endif
