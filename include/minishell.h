/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcorenti <rcorenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 16:18:24 by rcorenti          #+#    #+#             */
/*   Updated: 2022/02/26 17:26:39 by rcorenti         ###   ########.fr       */
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
# include <string.h>

# define SUCCESS 0
# define ERROR 1

# define STDIN 0
# define STDOUT 1
# define STDERR 2

extern int	g_signal;

enum	e_type
{
	token_word,
	token_operand,
	token_pipe,
	simple,
	doubles,
};

typedef struct s_char
{
	char					c;
	char					inhib;
}				t_char;

typedef struct s_token
{
	enum e_type				type;
	t_char					*token;
	struct s_token			*next;
}				t_token;

typedef struct s_command
{
	struct s_token			**command;
	struct s_command		*next;
}				t_command;

typedef struct s_operand
{
	char					*redir;
	int						type;
}				t_operand;

typedef struct s_final_command
{
	char					**args;
	t_operand				*redir_in;
	t_operand				*redir_out;
	struct s_final_command	*next;
}				t_final_command;

typedef struct s_env
{
	char			*val;
	int				ret;
	struct s_env	*next;
}				t_env;

typedef struct s_redir
{
	pid_t					pid;
	pid_t					*pid_pipe;
	int						i_pipe;
	int						pipe_nbr;
	int						in;
	int						in_pipe;
	int						in_fd;
	int						out;
	int						out_pipe;
	int						out_fd;
	int						pipe[2];
}			t_redir;

typedef struct s_shell
{
	int						ret;
	int						exit;
	int						parent;
	int						exec;
	t_env					*env;
	t_redir					redir;
}			t_shell;

t_final_command	*lexer(char *str, t_env *env);
int				get_token_size(char *str, int pos);
int				free_cmd(t_command *head);
int				skip_spaces(char *str);
int				treat_quote(char c, int quote);
char			*show_type(int type);
void			*free_tokens(t_token *token);
char			*find_env(char *str, char *var);
int				lexer_first_pass(char *str, t_token **tokens);
int				char_len(t_char *str);
int				count_pipes(t_final_command *cmd);
void			*display_syntax_error(void);
int				count_pipes(t_final_command *cmd);
void			free_tab(char **tab);
void			free_env(t_env *env);
t_token			*ft_lstnew(t_char *token, enum e_type type);
void			ft_lstadd_back(t_token **alst, t_token *new);
void			ft_lstadd_front(t_token **alst, t_token *new);
int				ft_charcmp(t_char *s1, const char *s2);
t_token			*lexer_second_pass(t_token *head);
void			ft_lstadd_back_cmd(t_command **command, t_command *new);
t_command		*ft_lstnew_cmd(void);
t_command		*lexer_expand(t_command *head, t_env *env);
t_command		*lexer_remove_quote(t_command *tk_head);
t_command		*lexer_split_cmd(t_token *tk_head);
char			*get_var(t_char *word);
int				get_expand_size(t_char *word);
char			*ft_strstr(char *str, char *to_find);
char			*ft_strchr(const char *s, int c);
t_char			*char_chr(t_char *str, int c);
int				execution(t_shell *shell, t_final_command *cmd);
char			*get_path(t_shell *shell, t_final_command *cmd);
int				redir(t_shell *shell, t_final_command *cmd);
int				bin_exe(t_shell *shell, t_final_command *cmd);
int				bin_exe_fork(t_shell *shell, t_final_command *cmd);
int				ft_pipe(t_shell *shell);
int				heredoc_loop(char **line, char *str);
int				ft_heredoc(char *str);
int				init_env(t_shell *shell, char **envp);
char			*get_val_env(char *arg, t_env *env);
char			*ft_name_env(char *str, char *name);
int				ft_size_env(char *str);
void			ft_unset(t_shell *shell, t_final_command *cmd);
int				ft_pwd(void);
int				ft_export(t_shell *shell, t_final_command *cmd);
void			ft_env(t_shell *shell);
void			ft_echo(t_final_command *cmd);
int				ft_cd(t_shell *shell, t_final_command *cmd);
void			ft_exit(t_shell *shell, t_final_command *cmd);
int				is_builtin(t_final_command *cmd);
int				builtin_exe(t_shell *shell, t_final_command *cmd);
int				ft_env_size(t_env *env);
char			**tenv_to_tab(t_env *env);
void			free_tab(char **tab);
void			free_env(t_env *env);
void			close_redir(t_shell *shell);
int				init_std(t_shell *shell);
void			init_redir(t_shell *shell);
void			free_final(t_final_command *head);
void			init_pipe(t_shell *shell);
void			handler(int code);
void			quit_handler(int code);
t_final_command	*lexer_fill_final(t_command *cmd_head);
void			display_final(t_final_command *head);
int				expand(t_command *cmd, size_t pos, t_char *word, t_env *env);
t_char			*expand_quoted(t_char *tk, t_char *word, t_env *env);
char			*t_char_to_char(t_char *t_chars);
void			fill_expanded(t_char *new, t_char *tk, t_char *word, char *exp);
int				treat_pipe(size_t *pos, t_char *token);
enum e_type		get_token_type(t_char *str);
char			*ft_itoa(int nb);
char			*finish_var(char *str, int i, char c);
int				ft_isdigit(char c);
int				count_tokens(t_token *token);
int				init_cursors(t_command *cmd, t_token ***new_tokens,
					size_t *cursors, size_t new_size);
t_final_command	*ft_lstnew_final(void);
void			ft_lstadd_back_final(t_final_command **command,
					t_final_command *new);
int				get_tk_nb_tmp(t_token **command);
int				get_redir_type(t_char *token);
char			*to_string(t_char *token);
t_operand		*fill_in(t_token **command);
t_operand		*fill_out(t_token **command);
char			**fill_args(t_token **command);
int				get_redir_out_nb(t_token **command);
int				get_redir_in_nb(t_token **command);
t_char			*bruh(t_token *command);
int				cut_operand(t_char *token, char *str, size_t *pos);
int				get_token(t_char **token, char *str, size_t *pos);
int				pipe_proxy(t_token *head);
void			*broke_free(void *ptr, void *ret);
int				broke_free2(void *ptr, int ret);
void			fill_tchar(t_char *c, char newchar, char newinhib, int *incr);
int				proxy(char *str);
t_token			*dispatch_tokens(char *str);
t_command		*dispatch_cmd(t_token *tk_head, t_env *env);
int				create_node_final(t_final_command **final_head,
					t_final_command **final_tmp, t_command *cmd_head);
int				cmd_free_broke(t_command *cmd_head);
char			*ft_readline(void);
int				ft_free_exit(t_shell *shell);
int				something_went_wrong(t_shell *shell);
void			quit_handler(int code);
void			handler(int code);
void			*ft_calloc(size_t nmemb, size_t size);
int				ft_check_char(char *str);

#endif
