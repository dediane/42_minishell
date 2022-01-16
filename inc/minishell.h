/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 23:26:15 by ddecourt          #+#    #+#             */
/*   Updated: 2022/01/16 14:31:01 by ddecourt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include "../libft/libft.h"

# define STDIN 0
# define STDOUT 1
# define STDERR 2

typedef enum e_filetype
{
	NONE,
	IN,
	OUT,
	DOUBLEOUT,
	DOUBLEIN,
}t_filetype;

typedef struct s_file
{
	char			*name;
	t_filetype		ftype;
	struct s_file	*next;
}				t_file;

typedef struct s_env
{
	char			*variable;
	char			*var_def;
	struct s_env	*next;
}				t_env;

typedef struct s_parsing
{
	int					nb_cmd;
	char				**tabs;
	int					pipe;
	int					index;
	int					fd_stdout;
	int					fd_stdin;
	int					heredoc;
	int					stop;
	int					is_built_in;
	int					fork;
	int					pipe_fd[2];
	t_filetype			type;
	t_file				*file;
	struct s_parsing	*next;
}			t_parsing;

extern int		g_exit_value;

////////main
char			**ft_copy_tab(char	**envp);

////////exec
char			**ft_exec_all_cmd(t_parsing *params, char **envp);
char			**ft_exec(t_parsing *params, char **envp);
int				open_file(t_parsing *params, char *file);

//exec_utils.c
int				open_file(t_parsing *params, char *file);
char			*get_right_path(t_parsing *params, char **envp);
char			**get_cmd_path(char **envp);
void			ft_free_params(t_parsing *params);
void			ft_free_file(t_file *file);
void			free_first_maillon(t_parsing *params);


//redirection.c
t_parsing		*ft_redir(t_parsing *params, char**envp);
t_parsing		*ft_exec_redir(t_parsing *params, char **envp);

//build_in.c
int				exec_built_in(t_parsing *params, char *cmd, char ***envp);
void			is_built_in(t_parsing *params);

//pipe.c
t_parsing		*ft_pipe(t_parsing *params, char **envp);

////////parsing
//parsing.c
int				parsing(char *argv, t_parsing *param, char **envp);
void			ft_fill2(char *argv, char *line, t_parsing *tmp, int *i);
int				ft_fill(char *argv, int *i, char *buf, char *line);
int				mdquote(char *argv, char *line, int *i, t_parsing *tmp);
void			mdquote2(char *line, char **envp, t_parsing *param);
int				mdquote3(char *argv, int *i);

//parsing2.c
int				ft_mredoc(char *line, int *i, char *argv, t_parsing *tmp);
char			*ft_mdolar(char *argv, int *i, char *line, t_parsing *param);
char			*ft_mdolar2(char *argv, int *i, char *line, char **envp);
int				ft_mpipe(char *argv, int *i, t_parsing *tmp, t_parsing *param);
void			ft_mspace(char *argv, int *i, t_parsing *tmp, char *line);

//parsing_utils.c
int				init_param(t_parsing *param);
char			*ft_line(char *line, char buf);
char			ft_strcpy(char *dest, char *src);
int				ft_init(t_parsing *param, int *i, char *argv);
void			ft_pass_space(char *argv, int *i);

//parsing_tabs.c
int				ft_paste_tab(t_parsing *param, char **new, char *line);
void			free_tabs(char **tabs);
char			**ft_malloc_tab(t_parsing *param, int len_tab, char *line);
int				ft_len_tabs(char **tab);
int				ft_tabs(t_parsing *parsing, char *line);

//parsing_quote.c
char			*ft_add_double_quote(t_parsing *param, int *i, char *argv, \
char *line);
int				ft_add_simple_quote(t_parsing *param, int *i, char *argv, \
char *line);
int				ft_check_quote(char *line, int a);
char			*ft_double_quote(char *line, int *i, char *argv, \
t_parsing *param);
void			ft_pass_dquote(char *argv, int *i);

//parsing_quote2.c
int				ft_simple_quote(char *line, int *i, char *argv, \
t_parsing *param);
void			ft_pass_squote(char *argv, int *i);
int				pos_dolar(char *line);
char			*ft_copy(char *var, char *line, char *exp, int pos);
void			ft_copy2(char *line, int pos, char *var, int i);

//check_redoc.c
void			ft_define_redicretcion(char *argv, int *i, t_parsing *param);
int				ft_check_redoc(char *argv, int i);

//stack_alloc.c
int				alloue_elem(t_parsing *param);
int				ft_add_maillon(t_parsing *param);
void			t_index(t_parsing *param);
void			ft_nb_cmd(t_parsing *param, int i);

//add_file.c
int				ft_add_file(t_parsing *param, int *i, char *argv, char *line);
int				ft_add_to_fstack(t_parsing *param, char *line);
void			ft_add_to_fstack2(t_file *tmp, char *new_name, t_file *new, \
t_parsing *param);

//env_liste.c
int				env_list(t_env  **env, char **envp);
int				ft_malloc_env(t_env	**env);
int				ft_find_variable(t_env *env, char *envp);
void			free_env(t_env **env);
void			ft_def_env(t_env *tmp, t_env *new);

//varaible_env.c
char			*find_var(char **envp, char *line);
int				dolar_quotes(char *line);
int				ft_change(char *argv);
char			*ft_replace_var(char *line, char **envp);
char			*ft_search_var(char *var, char **envp, char *line, int pos);

//variable_env2.c
char			*ft_copy_line(char *line, char **envp, int i, int j);
char			*ft_copy_var(char *var, char **envp, int j, int i);

////////built_in
char			*get_path(char **envp, char *to_find, int *i);
char			*ft_get_home(char **envp);
//cd
int				ft_cd(char **envp, char *path, t_parsing *params);
char			*ft_get_home(char **envp);
int				change_env(char **envp, char *path, char *new_path);

int				ft_env(int fd, char **envp);
int				ft_pwd(int fd);
void			ft_exit(char *exit_line);
int				ft_echo(int fd, t_parsing *params);
//export
char			**set_in_env(char *line, char **env);
void			ft_print_export(char **env);
int				ft_check_arg(char	*arg);
char			**ft_export(int fd, char **tabs, char **env);

//export2
int				ft_parse_env(char *tab, char **key, char **value);
int				ft_is_in_env(char *key, char **envp);
void			ft_print_tab(char **tab);

//unset
char			**ft_unset(int fd, char **tabs, char **env);
char			*ft_strtrim_first_letter(char *line);

//heredoc
int				ft_heredoc(char *eof, t_parsing *params);

////////signal

//signal.c
void			ft_sigint(int sig);
void			ft_sigquit(int sig);
void			ft_ignore(int sig);
void			ft_disable(int pid);
void			ft_launch_signal(void);

#endif
