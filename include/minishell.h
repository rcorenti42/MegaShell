/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcorenti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 16:18:24 by rcorenti          #+#    #+#             */
/*   Updated: 2022/02/16 15:09:59 by rcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/libft.h"
# include "colors.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <limits.h>

# define SUCCESS 0
# define ERROR 1

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define EMPTY 0
# define REDIR 1
# define APPEND 2
# define INPUT 3
# define PIPE 4
# define DOC 5
# define CMD 6
# define FILES 7

typedef struct s_char
{
	char			c;
	char			inhib;
}				t_char;

typedef struct s_token
{
	int			type;
	char		*str;
	t_char			*token;
	struct s_token		*next;
}				t_token;

typedef struct s_command
{
	int					type;
	struct s_token		**command;
	struct s_command	*next;
}				t_command;

typedef struct s_env
{
	char			*val;
	struct s_env		*next;
}				t_env;

typedef struct s_redir
{
	pid_t		pid;
	int		*fd;
	int		pipe_nbr;
	int		in;
	int		in_pipe;
	int		out;
	int		out_pipe;
}			t_redir;

typedef struct s_shell
{
	int		ret;
	int		exit;
	t_env	*env;
	t_redir	redir;
}			t_shell;

//lexer.c
t_command		*lexer(char *str, t_env *env);
int			get_token_size(char *str, int pos);
void	display_cmd(t_command *cmd);

//lexer_utils.c
int			skip_spaces(char *str);
int			treat_quote(char c, int quote);
char		*show_type(int type);
void		free_tokens(t_token *token);
char		*find_env(char *str, t_char *word);

//lexer_first_pass.c
t_token		*lexer_first_pass(char *str);
t_char		*get_token(char *str, int *pos);

//utils.c
int	char_len(t_char *str);

//list.c
t_token		*ft_lstnew(t_char *token, int type);
void		ft_lstadd_back(t_token **alst, t_token *new);
void		ft_lstadd_front(t_token **alst, t_token *new);
int			ft_charcmp(t_char *s1, const char *s2);

//lexer_second_pass.c
t_token		*lexer_second_pass(t_token *head);

//list2.c
void    ft_lstadd_back_cmd(t_command **command, t_command *new);
t_command *ft_lstnew_cmd(void);

//expand.c
t_command *lexer_expand(t_command *head, t_env *env);

//lexer_remove_quotes.c
t_command *lexer_remove_quote(t_command *tk_head);

//lexer_split_cmd.c
t_command	*lexer_split_cmd(t_token *tk_head);

//expand_utils.c
char		*get_var(t_char *word);
int			get_expand_size(t_char *word);
char		*ft_strstr(char *str, char *to_find);
char		*ft_strchr(const char *s, int c);
t_char		*char_chr(t_char *str, int c);

//EXECUTION
void	execution(t_shell *shell, t_command *cmd_prev, t_command *cmd);
char	*get_path(char *arg, t_env *env);
int		redir(t_shell *shell, t_command *cmd, int type);
void	bin_exe(t_shell *shell, t_command *cmd);


//ENV
int		init_env(t_shell *shell, char **envp);
char	*get_val_env(char *arg, t_env *env);

//BUILTINS
void	ft_unset(t_shell *shell, t_command *cmd);
int		ft_pwd(void);
int		ft_export(t_shell *shell, t_command *cmd);
void	ft_env(t_shell *shell);
void	ft_echo(t_shell *shell, t_command *cmd);
int		ft_cd(t_shell *shell, t_command *cmd);
void	ft_exit(t_shell *shell, t_command *cmd);
int		is_builtin(t_command *cmd);
int		builtin_exe(t_shell *shell, t_command *cmd);

//TOOLS
int		ft_env_size(t_env *env);
char	**tenv_to_tab(t_env *env);
void	free_tab(char **tab);
void	free_env(t_env *env);

#endif
