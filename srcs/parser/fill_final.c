/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_final.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 14:50:49 by sobouatt          #+#    #+#             */
/*   Updated: 2022/02/24 20:53:54 by sobouatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_redir_in_nb(t_token **command)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!command)
		return (i);
	while (command[i] != NULL)
	{
		if (command[i]->type == token_operand
			&& (ft_charcmp(command[i]->token, "<") == 0
				|| ft_charcmp(command[i]->token, "<<") == 0))
		{
			j++;
			if (command[i + 1] != NULL)
			{
				if (command[i + 1]->type == token_operand)
					return (-1);
			}
			else
				return (-1);
		}
		i++;
	}
	return (j);
}

int	get_redir_out_nb(t_token **command)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!command)
		return (0);
	while (command[i] != NULL)
	{
		if (command[i]->type == token_operand
			&& (ft_charcmp(command[i]->token, ">") == 0
				|| ft_charcmp(command[i]->token, ">>") == 0))
		{
			j++;
			if (command[i + 1] != NULL)
			{
				if (command[i + 1]->type == token_operand)
					return (-1);
			}
			else
				return (-1);
		}
		i++;
	}
	return (j);
}

char	**fill_args(t_token **command)
{
	char	**args;
	int		ac;
	int		i;
	int		j;

	ac = get_tk_nb_tmp(command)
		- (get_redir_in_nb(command) * 2 + get_redir_out_nb(command) * 2);
	args = malloc(sizeof(char *) * (ac + 1));
	if (!args)
		return (NULL);
	i = 0;
	j = 0;
	while (command[i] != NULL)
	{
		if (command[i]->type == token_operand)
			i ++;
		else
			args[j++] = to_string(command[i]->token);
		i++;
	}
	args[j] = NULL;
	return (args);
}

t_operand	*fill_in(t_token **command)
{
	t_operand	*in;
	int			i;
	int			j;

	i = get_redir_in_nb(command);
	if (i < 0)
		return (NULL);
	in = malloc(sizeof(t_operand) * (i + 1));
	if (!in)
		return (NULL);
	i = 0;
	j = 0;
	while (command[i] != NULL)
	{
		if (command[i]->type == token_operand && (ft_charcmp(command[i]->token,
					"<") == 0 || ft_charcmp(command[i]->token, "<<") == 0))
		{
			in[j].type = get_redir_type(command[i++]->token);
			in[j++].redir = to_string(command[i]->token);
		}
		else
			i++;
	}
	in[j].redir = NULL;
	return (in);
}

t_operand	*fill_out(t_token **command)
{
	t_operand	*out;
	int			i;
	int			j;

	i = get_redir_out_nb(command);
	if (i < 0)
		return (NULL);
	out = malloc(sizeof(t_operand) * (i + 1));
	if (!out)
		return (NULL);
	i = 0;
	j = 0;
	while (command[i] != NULL)
	{
		if (command[i]->type == token_operand && (ft_charcmp(command[i]->token,
					">") == 0 || ft_charcmp(command[i]->token, ">>") == 0))
		{
			out[j].type = get_redir_type(command[i++]->token);
			out[j++].redir = to_string(command[i]->token);
		}
		else
			i++;
	}
	out[j].redir = NULL;
	return (out);
}
