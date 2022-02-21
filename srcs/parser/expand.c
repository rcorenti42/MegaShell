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

void fill_tchar(t_char *c, char newchar, char newinhib, int *incr)
{
	c->c = newchar;
	c->inhib = newinhib;
	(*incr)++;
}

void put_tchar(t_char *str)
{
	int i;

	i = 0;
	if (!str)
		return;
	while (str[i].c != '\0')
	{
		write(1, &str[i].c, 1);
		i++;
	}
}

t_char *expand_unknown(t_char *token, t_char *word, char *var)
{
	int i;
	int j;
	t_char *new;

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

void fill_expanded(t_char *new, t_char *tk, t_char *word, char *exp)
{
	int i;
	int j;
	int exp_size;

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

t_char *expand_quoted(t_char *tk, t_char *word, t_env *env)
{
	char *var;
	t_char *new;
	char *exp;

	var = get_var(word);
	while (env)
	{
		exp = find_env(env->val, var, env->ret);
		if (exp != NULL)
		{
			new = malloc(sizeof(t_token)
						 * ((char_len(tk) + ft_strlen(exp) - ft_strlen(var)
							 + 1)));
			fill_expanded(new, tk, word, exp);
			break;
		}
		env = env->next;
	}
	if (exp == NULL)
		new = expand_unknown(tk, word, var);
	free(var);
	return (new);
}

char *t_char_to_char(t_char *t_chars)
{
	size_t i;

	i = 0;
	while (t_chars[i].c != '\0')
	{
		((char *) t_chars)[i] = t_chars[i].c;
		i++;
	}
	((char *) t_chars)[i] = '\0';
	return ((char *) t_chars);
}

int expand(t_command *cmd, size_t pos, t_char *word, t_env *env)
{
	if (word->inhib == '\"') // if we are quoted
	{ // use regular expansion
		t_char *new = expand_quoted(cmd->command[pos]->token, word, env);
		if (new == NULL)
			return (-1);
		free(cmd->command[pos]->token);
		cmd->command[pos]->token = new;
		return (0);
	}
	else // if unquoted
	{ // use lexed expansion
		size_t new_size = 0; // new size is the number of tokens to be added

		/*
		** We take our variable content and feed it through our lexer
		** resulting in tokens to add.
		*/
		t_char *replace_t_chars = expand_quoted(cmd->command[pos]->token, word, env);
		if (replace_t_chars == NULL)
			return (-1);
		t_token *repl = lexer_first_pass(t_char_to_char(replace_t_chars), env);
		free(replace_t_chars);
		repl = lexer_second_pass(repl);

		{ // count tokens to add
			t_token *cp = repl;
			while (cp != NULL)
			{
				cp = cp->next;
				new_size++;
			}
		}

		if (new_size == 0) // if we have 0 tokens to add (old token to delete)
		{
			free(cmd->command[pos]->token); // free old token
			free(cmd->command[pos]);
			// then move every token to the left
			if (pos == 0)
			{
				cmd->command[pos] = cmd->command[pos + 1];
			}
			else
			{
				pos--;
			}
			size_t i = pos;
			while (cmd->command[pos + 1] != NULL)
			{
				cmd->command[pos + 1] = cmd->command[pos + 2];
				cmd->command[pos]->next = cmd->command[pos + 1];
				i++;
			}
		}
		else if (new_size == 1) // if we have 1 token to add
		{ // (that means we don't have to allocate)
			free(cmd->command[pos]->token); // free old token
			free(cmd->command[pos]);
			cmd->command[pos] = repl; // replace old token by new
			cmd->command[pos]->next = cmd->command[pos + 1]; // relink the list
			if (pos > 0)
				cmd->command[pos - 1]->next = cmd->command[pos];
		}
		else // we have multiple tokens to add
		{ // we must reallocate new room for all the tokens
			size_t new_total_size = 0; // count how many total tokens we will
			// have
			while (cmd->command[new_total_size] != NULL)
				new_total_size += 1;

			new_total_size += new_size;
			// allocate space
			t_token **new_tokens = malloc(
				sizeof(*new_tokens) * new_total_size);
			if (new_tokens == NULL)
			{
				free_tokens(repl);
				return (-1);
			}
			size_t old_cursor = 0;
			size_t new_cursor = 0;
			while (old_cursor < pos) // move token that were before the point
			{ // we are expanding the variable
				new_tokens[new_cursor] = cmd->command[old_cursor];
				old_cursor++;
				new_cursor++;
			}

			while (repl != NULL) // insert the new tokens
			{
				new_tokens[new_cursor] = repl;
				repl = repl->next;
				new_cursor++;
			}

			free(cmd->command[old_cursor]->token); // free previous tokens
			free(cmd->command[old_cursor]);
			old_cursor++;

			while (cmd->command[old_cursor] != NULL) // move to the new array
			{ // the tokens that were after the point we are inserting at
				new_tokens[new_cursor] = cmd->command[old_cursor];
				old_cursor++;
				new_cursor++;
			}
			new_tokens[new_cursor] = NULL; // add a NULL at the end

			size_t i = 0; // relink all the tokens
			while (i < new_total_size - 1)
			{
				new_tokens[i]->next = new_tokens[i + 1];
				i++;
			}

			free(cmd->command); // free old command
			cmd->command = new_tokens; // put new command in place
		}
	}
	return (0);
}

t_command *lexer_expand(t_command *head, t_env *env)
{
	t_char *chr_rt;
	int res;
	t_command *node;
	int i;

	node = head;
	while (node)
	{
		i = -1;
		while (node->command[++i] != NULL)
		{
			chr_rt = char_chr(node->command[i]->token, '$');
			while (chr_rt != NULL)
			{
				res = expand(node, i, chr_rt, env);
				if (res != 0)
				{
					free_cmd(head);
					return (NULL);
				}
				if (node->command[i] == NULL)
					chr_rt = NULL;
				else
					chr_rt = char_chr(node->command[i]->token, '$');
			}
		}
		node = node->next;
	}
	return (head);
}