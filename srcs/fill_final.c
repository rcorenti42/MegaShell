#include "../include/parsing.h"

t_final_command	*ft_lstnew_final(void)
{
	t_final_command *new;

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

int		get_tk_nb_tmp(t_token **command)
{
	int i;

	i = 0;
	while (command[i] != NULL)
		i++;
	return (i);
}

char	*to_string(t_char *token)
{
	int i;
	char *str;

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

t_final_command *lexer_fill_final(t_command *cmd_head)
{
	t_final_command *final_head;
	t_final_command *final_tmp;
	t_command *cmd_tmp;
	int i;

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
		i = 0;
		while (cmd_tmp->command[i])
		{
			final_tmp->cmd = malloc(sizeof(char *) * (get_tk_nb_tmp(cmd_tmp->command) + 1));
			final_tmp->cmd[i] = to_string(cmd_tmp->command[i]->token);
			final_tmp->redir_in = NULL;
			final_tmp->redir_out = NULL;
			i++;
		}
		final_tmp->cmd[i] = NULL;
		cmd_tmp = cmd_tmp->next;
	}
	return (final_head);
}