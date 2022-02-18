/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_final.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 04:42:28 by sobouatt          #+#    #+#             */
/*   Updated: 2022/02/18 13:24:14 by rcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_final_command	*ft_lstnew_final(void)
{
	t_final_command	*new;

	new = malloc(sizeof(t_final_command));
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back_final(t_final_command **command, t_final_command *new)
{
	t_final_command	*tmp;

	tmp = *command;
	if (*command == NULL)
		*command = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

int	get_tk_nb_tmp(t_token **command)
{
	int	i;

	i = 0;
	while (command[i] != NULL)
	{
		i++;
	}
	return (i);
}

int	get_redir_in_nb(t_token **command)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (!command)
		return (i);
	while (command[i] != NULL)
	{
		if (command[i]->type == token_operand && (ft_charcmp(command[i]->token, "<") == 0 || ft_charcmp(command[i]->token, "<<") == 0))
		{
			j++;
			if (command[i + 1] != NULL)
				if (command[i + 1]->type != token_word)
					return (-1);
		}
		i++;
	}
	return (j);	
}

int	get_redir_out_nb(t_token **command)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (!command)
		return (0);
	while (command[i] != NULL)
	{
		if (command[i]->type == token_operand && (ft_charcmp(command[i]->token, ">") == 0 || ft_charcmp(command[i]->token, ">>") == 0))
		{
			j++;
			if (command[i + 1] != NULL)
				if (command[i + 1]->type != token_word)
					return (-1);
		}
		i++;
	}
	return (j);	
}

char	*to_string(t_char *token)
{
	int		i;
	char	*str;

	i = 0;
	str = malloc(sizeof(char) * (char_len(token) + 1));
	while (token[i].c != '\0')
	{
		str[i] = token[i].c;
		i++;
	}
	str[i] = '\0';
	return (str);
}

char **fill_args(t_token **command)
{
	char **args;
	int ac;
	int i;
	int j;
	
	ac = get_tk_nb_tmp(command) - (get_redir_in_nb(command) * 2 + get_redir_out_nb(command) * 2);
	//printf("ac=%d\n", ac);
	args = malloc(sizeof(char *) * (ac + 1));
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

t_operand *fill_in(t_token **command)
{
	t_operand *in;
	int ac;
	int i;
	int j;
	
	ac = get_redir_in_nb(command);
	if (ac < 0)
		return (NULL);
//	printf("in_redir = %d\n", ac);
	in = malloc(sizeof(t_operand) * (ac + 1));
	i = 0;
	j = 0;
	while (command[i] != NULL)
	{
		if (command[i]->type == token_operand && (ft_charcmp(command[i]->token, "<") == 0 || ft_charcmp(command[i]->token, "<<") == 0))
		{
			if (ft_charcmp(command[i]->token, "<") == 0)
				in[j].type = 0;
			else
				in[j].type = 1;
			i++;
			in[j].redir = to_string(command[i]->token);
			j++;
		}
		else
			i++;
	}
	in[j].redir = NULL;
	return (in);
}

t_operand *fill_out(t_token **command)
{
	t_operand *out;
	int ac;
	int i;
	int j;
	
	ac = get_redir_out_nb(command);
	if (ac < 0)
		return (NULL);
	//printf("out_redir = %d\n", ac);
	out = malloc(sizeof(t_operand) * (ac + 1));
	i = 0;
	j = 0;
	while (command[i] != NULL)
	{
		if (command[i]->type == token_operand && (ft_charcmp(command[i]->token, ">") == 0 || ft_charcmp(command[i]->token, ">>") == 0))
		{
			if (ft_charcmp(command[i]->token, ">") == 0)
				out[j].type = simple;
			else
				out[j].type = doubles;
			i++;
			out[j].redir = to_string(command[i]->token);
			j++;
		}
		else
			i++;
	}
	//printf("j=%d\n", j);
	out[j].redir = NULL;
	return (out);
}

t_final_command	*lexer_fill_final(t_command *cmd_head)
{
	t_final_command	*final_head;
	t_final_command	*final_tmp;
	t_command		*cmd_tmp;
	
	cmd_tmp = cmd_head;
	final_head = NULL;
	while (cmd_tmp)
	{
		if (cmd_head == NULL)
		{
			final_head = ft_lstnew_final();
		}
		else
		{
			final_tmp = ft_lstnew_final();
			ft_lstadd_back_final(&final_head, final_tmp);
		}
		final_tmp->args = fill_args(cmd_tmp->command);
		final_tmp->redir_in = fill_in(cmd_tmp->command);
		final_tmp->redir_out = fill_out(cmd_tmp->command);
		cmd_tmp = cmd_tmp->next;
	}
	return (final_head);
}