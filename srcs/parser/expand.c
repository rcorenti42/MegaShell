/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 07:56:33 by sobouatt          #+#    #+#             */
/*   Updated: 2022/02/20 06:38:08 by sobouatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_tchar(t_char *c, char newchar, char newinhib, int *incr)
{
	c->c = newchar;
	c->inhib = newinhib;
	(*incr)++;
}

void	put_tchar(t_char *str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i].c != '\0')
	{
		write(1, &str[i].c, 1);
		i++;
	}
}

t_char	*expand_unknown(t_char *token, t_char *word, char *var)
{
	int		i;
	int		j;
	t_char	*new;

	i = 0;
	new = malloc(sizeof(t_char) * (char_len(token) + 1) - (ft_strlen(var)));
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
	//printf("%s\n", exp);
	exp_size = get_expand_size(word);
	//printf("exp_size=%d\n", exp_size);
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

t_char	*expand(t_char *tk, t_char *word, t_env *env)
{
	char	*var;
	t_char	*new;
	char	*exp;

	var = get_var(word);
	while (env)
	{
		exp = find_env(env->val, var, env->ret);
		if (exp != NULL)
		{
			new = malloc(sizeof(t_token)
					* ((char_len(tk) + ft_strlen(exp) - ft_strlen(var) + 1)));
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

t_command	*lexer_expand(t_command *head, t_env *env)
{
	t_char		*chr_rt;
	t_char		*tmp;
	t_command	*node;
	int			i;

	node = head;
	while (node)
	{
		i = -1;
		while (node->command[++i] != NULL)
		{
			chr_rt = char_chr(node->command[i]->token, '$');
			while (chr_rt != NULL)
			{	
				tmp = expand(node->command[i]->token, chr_rt, env);
				if (tmp != NULL)
				{
					free(node->command[i]->token);
					node->command[i]->token = tmp;
				}
				chr_rt = char_chr(node->command[i]->token, '$');
			}
		}
		node = node->next;
	}
	return (head);
}