/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 21:51:30 by rcorenti          #+#    #+#             */
/*   Updated: 2022/02/25 15:08:21 by sobouatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

int		ft_isspace(int c);
int		ft_isalpha(int c);
int		ft_isalnum(int c);
int		ft_atoi(char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strcat(char *dest, const char *src);
void	ft_putstr_fd(char*str, int fd);
void	ft_putendl_fd(char *str, int fd);
void	*ft_memdel(void *ptr);
char	*ft_strdup(const char *s);
char	**ft_split(const char *s, char c);
void	*ft_memcpy(void *dest, const void *src, size_t n);
size_t	ft_strlen(const char *str);

#endif
