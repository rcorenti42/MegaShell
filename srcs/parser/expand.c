/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 07:56:33 by sobouatt          #+#    #+#             */
/*   Updated: 2022/02/26 05:52:49 by sobouatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_tchar(t_char *c, char newchar, char newinhib, int *incr)
{
	c->c = newchar;
	c->inhib = newinhib;
	(*incr)++;
}

t_char	*expand_unknown(t_char *token, t_char *word, char *var)
{
	int		i;
	int		j;
	t_char	*new;

	i = 0;
	new = malloc(sizeof(t_char) * ((char_len(token) + 1) - (ft_strlen(var))));
	if (new == NULL)
		return (NULL);
	while (token + i != word)
		fill_tchar(&new[i], token[i].c, token[i].inhib, &i);
	j = get_expand_size(word);
	while (token[i + j].c != '\0')
		fill_tchar(&new[i], token[i + j].c, token[i + j].inhib, &i);
	new[i].c = '\0';
	return (new);
}

void	fill_expanded(t_char *new, t_char *tk, t_char *word, char *exp)
{
	int	i;
	int	j;
	int	exp_size;

	i = 0;
	j = 0;
	exp_size = get_expand_size(word);
	while (tk + i != word)
		fill_tchar(&new[i], tk[i].c, tk[i].inhib, &i);
	while (exp[j] != '\0')
		fill_tchar(&new[i + j], exp[j], '"', &j);
	while (tk[i + exp_size].c != '\0')
		fill_tchar(&new[i + j], tk[i + exp_size].c, tk[i + exp_size].inhib, &i);
	new[i + j].c = '\0';
	if (word[1].c == '?')
		free(exp);
}

t_char	*expand_quoted(t_char *tk, t_char *word, t_env *env)
{
	char	*var;
	t_char	*new;
	char	*exp;

	var = get_var(word);
	while (env)
	{
		exp = find_env(env->val, var);
		if (exp != NULL)
		{
			new = malloc(sizeof(t_token) * (char_len(tk) + ft_strlen(exp)
						- ft_strlen(var) + 1));
			if (new == NULL)
				return (broke_free(var, NULL));
			fill_expanded(new, tk, word, exp);
			break ;
		}
		env = env->next;
	}
	if (exp == NULL)
		new = expand_unknown(tk, word, var);
	free(var);
	return (new);
}

char	*t_char_to_char(t_char *t_chars)
{
	size_t	i;

	i = 0;
	while (t_chars[i].c != '\0')
	{
		((char *) t_chars)[i] = t_chars[i].c;
		i++;
	}
	((char *) t_chars)[i] = '\0';
	return ((char *) t_chars);
}
