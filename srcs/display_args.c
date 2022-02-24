/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcorenti <rcorenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 06:45:26 by rcorenti          #+#    #+#             */
/*   Updated: 2022/02/24 06:46:19 by rcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_args(char **args)
{
	int	i;

	i = 0;
	if (args[i] != NULL)
		printf("args = {\"%s\"", args[i++]);
	while (args[i] != NULL)
	{
		printf(", \"%s\"", args[i++]);
	}
	printf("}\n");
}

void	display_in(t_operand *in)
{
	int	i;

	i = 0;
	printf("redir_in = {");
	if (in[i].redir == NULL)
		printf("NULL}");
	else
	{
		printf("\"%s\", %d}", in[i].redir, in[i].type);
		i++;
	}
	while (in[i].redir != NULL)
	{
		printf("redir_in = {\"%s\", %d}", in[i].redir, in[i].type);
		i++;
	}
	printf("\n");
}

void	display_out(t_operand *out)
{
	int	i;

	i = 0;
	printf("redir_out = {");
	if (out[i].redir == NULL)
		printf("NULL}");
	else
	{
		printf("\"%s\", %d}", out[i].redir, out[i].type);
		i++;
	}
	while (out[i].redir != NULL)
	{
		printf("{\"%s\", %d}", out[i].redir, out[i].type);
		i++;
	}
	printf("\n");
}

void	display_final(t_final_command *head)
{
	t_final_command	*tmp;

	tmp = head;
	while (tmp)
	{
		display_args(tmp->args);
		display_in(tmp->redir_in);
		display_out(tmp->redir_out);
		tmp = tmp->next;
	}
}
