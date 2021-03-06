/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 23:26:15 by ddecourt          #+#    #+#             */
/*   Updated: 2022/01/21 11:56:54 by ddecourt         ###   ########.fr       */
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

typedef struct s_param
{
	char	*argv;
	int		i;
	char	*line;
	char	**envp;
	char	*buf;
	int		ret;
	int		ret2;
}				t_param;

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
	int					calldoc;
	int					pipe_fd[2];
	t_filetype			type;
	t_file				*file;
	struct s_parsing	*next;
}			t_parsing;

extern int		g_exit_value;

////////main
char			**ft_copy_tab(char	**envp);
char			*ft_readline_signal(char *line, char **env);
void			line_hyst(char *line);

////////----------------------exec--------------------

//exec.c
int				exec_process(char **cmd, char *path, char **envp, \
				t_parsing *params);
char			**ft_exec(t_parsing *params, char **envp);
char			**ft_exec_1(t_parsing *params, t_parsing *prev, char **envp);
void			ft_exec_2(t_parsing *params, t_parsing *prev);
char			**ft_exec_all_cmd(t_parsing *params, char **envp);

//exec2.c
int				check_pipe_built(t_parsing *params, int pid);
char			*look_for_relative_path(t_parsing *params, char **envp);
void			wait_process(t_parsing *params, int status);
void			ft_init_exec( int *pid, int *status);
void			ft_continue(t_parsing *params, t_parsing *head);

//exec_utils.c
void			ft_command_not_found(char **path_array, char *title, \
				t_parsing *params);
char			**get_cmd_path(char **envp);
char			*get_right_path(t_parsing *params, char **envp);
int				open_file(t_parsing *params, char *file, char **env);

//redirection.c
t_parsing		*ft_redir(t_parsing *params, char**envp);
void			exec_in_redir(t_parsing*params, char **envp);
int				get_nb_files(t_file *file);
int				ft_multiple_redir(int nb, t_file *file, \
				t_parsing *params, char **envp);
t_parsing		*ft_exec_redir(t_parsing *params, char **envp);

//fd.c
void			save_in_out(t_parsing *params);
void			set_fd(t_parsing *params, int fd);
void			close_fd(t_parsing *params);
void			close_heredoc(int pipe_fd[2], t_parsing *params, char *line);
void			print_heredoc(int pipe_fd[2], char *line);

//heredoc.c
int				check_eof(char *line, char *eof);
int				ft_heredoc(char *eof, t_parsing *params, char **env);

//heredoc2.c
int				ft_nb_files(t_file *file, int nb);
int				ft_break(t_file *file, int eof, int nb, t_file *head);
void			ft_print_heredoc(int pipe_fd[2], char *line, int eof, int nb);

//build_in.c
int				exec_built_in(t_parsing *params, char *cmd, char ***envp);
int				exec_built_in2(t_parsing *params, char *cmd, char ***envp);
void			is_built_in(t_parsing *params);

////////---------------------parsing-----------------------

//parsing.c
void			ft_init_param(char*argv, char **envp, t_param *arg);
int				parsing(char *argv, t_parsing *param, char **envp);
int				ft_first_if(t_parsing *param, t_parsing *tmp, t_param *arg);
int				ft_second_if(t_param *arg, t_parsing *tmp);
void			ft_third_if(t_param *arg, t_parsing *tmp);

//parsing2.c
int				ft_mredoc(char *line, int *i, char *argv, t_parsing *tmp);
char			*ft_mdolar(char *argv, int *i, char *line, t_parsing *param);
char			*ft_mdolar2(char *argv, int *i, char *line, char **envp);
int				ft_mpipe(char *argv, int *i, t_parsing *tmp, t_parsing *param);
void			ft_mspace(char *argv, int *i, t_parsing *tmp, char *line);

//parsing3.c
int				ft_fill(char *argv, int *i, char *buf, char *line);
void			ft_fill2(char *argv, char *line, t_parsing *tmp, int *i);
void			mdquote2(char *line, char **envp, t_parsing *param);
int				mdquote3(char *argv, int *i);
int				s_quote(t_param *arg, t_parsing *tmp);

//parsing_utils.c
int				init_parsing(t_parsing *param);
char			*ft_line(char *line, char buf);
char			ft_strcpy(char *dest, char *src);
int				ft_init(t_parsing *param, t_param *arg, \
				char *argv, char **envp);
int				ft_pass_space(char *argv, int *i);

//parsing_tabs.c
int				ft_paste_tab(t_parsing *param, char **new, char *line);
void			free_tabs(char **tabs);
char			**ft_malloc_tab(t_parsing *param, int len_tab, char *line);
int				ft_len_tabs(char **tab);
int				ft_tabs(t_parsing *parsing, char *line);

//parsing_quote.c
char			*ft_double_quote(char *line, int *i, char *argv, \
				t_parsing *param);
void			ft_pass_dquote(char *argv, int *i);
char			*ft_add_double_quote(t_parsing *param, int *i, char *argv, \
char *line);
int				ft_add_simple_quote(t_parsing *param, int *i, char *argv, \
char *line);
int				ft_check_quote(char *line, int a);

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
int				env_list(t_env **env, char **envp);
int				ft_malloc_env(t_env	**env);
int				ft_find_variable(t_env *env, char *envp);
void			free_env(t_env **env);
void			ft_def_env(t_env *tmp, t_env *new);

//variable_env.c
char			*find_var(char **envp, char *line);
int				dolar_quotes(char *line);
int				ft_change(char *argv);
char			*ft_replace_var(char *line, char **envp);
char			*ft_search_var(char *var, char **envp, char *line, int pos);

//variable_env2.c
char			*ft_copy_line(char *line, char **envp, int i, int j);
char			*ft_copy_var(char *var, char **envp, int j, int i);
void			ft_la(int *i, char *name);
char			*ft_var(char *var);

//ft_free.c
void			ft_free_file(t_file *file);
void			ft_free_params(t_parsing *params);
void			free_first_maillon(t_parsing *params);

//parsing_dolar.c
int				ft_dolar_q(t_param *arg, t_parsing *tmp);
int				ft_dolar_v(t_param *arg);

////////----------------------built_in----------------------------

//cd.c
char			*ft_get_home(char **envp);
char			*get_path(char **envp, char *to_find, int *i);
int				change_env(char **envp, char *path, char *new_path);
int				ft_cd(char **envp, char *path, t_parsing *params);

//env.c
int				ft_env(int fd, char **envp);

//pwd.c
int				wrong_file(char *path);
int				wrong_file2(char *s);
int				check_cd_arg(t_parsing *params);
int				ft_pwd(int fd);

//exit.c
void			ft_exit(t_parsing *params, char **env);
void			ft_exit_mess(void);
int				ft_num(char *s);

//echo.c
int				check_n(char *arg);
int				check_size(int size, int fd, char **tabs);
void			ft_write(int fd, t_parsing *params, int *i, int *space);
void			ft_plus(int *i, int *size);
int				ft_echo(int fd, t_parsing *params, int space);

//export
char			**set_in_env(char *line, char **env);
void			ft_print_export(char **env);
int				ft_check_arg(char	*arg);
char			**ft_export(char **tabs, char **env);

//export2
int				ft_parse_env(char *tab, char **key, char **value);
int				ft_is_in_env(char *key, char **envp);
void			ft_print_tab(char **tab);

//unset
char			*ft_strtrim_first_letter(char *line);
char			*ft_get_key(char *arg);
char			**unset_in_env(char *line, char **env);
int				ft_is_in_env2(char *key, char **envp);
char			**ft_unset(int fd, char **tabs, char **env);

////////----------------------signal----------------------------

//signal.c
void			ft_sigint(int sig);
void			ft_sigquit(int sig);
void			ft_ignore(int sig);
void			ft_disable(int pid);
void			ft_launch_signal(void);

#endif