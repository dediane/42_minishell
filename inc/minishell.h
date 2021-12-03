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

typedef enum	e_filetype
{
	NONE,
	IN,
	OUT,
	DOUBLEOUT,
	DOUBLEIN,
}t_filetype;

/*typedef enum	e_cmdtype
{
	NOTHING,
	PIPE,
	REDIREC,
}				t_cmdtype;*/

typedef struct s_file
{
	char			*name;
	t_filetype		ftype;
	struct s_file	*next;
}				t_file;

typedef struct s_env
{
  char          *variable;
  char          *var_def; //interpretation de la variable
  struct s_env  *next;
}				t_env;

typedef	struct s_parsing
{
	int					nb_cmd;		//== nombre de maillon
	char				**tabs;		//il y a la commande et les arguments dedans
//	t_cmdtype			b_cmd;		//commande before maillon (le premier maillon sera forcement NONE/0)
	int					pipe;
	int					index;
	int					fd_stdout;
	int					fd_stdin;
	t_filetype			type;		//je pense qu'il sert a rien lui quoique je m'en sert dans le parsing
	t_file				*file;
//	t_cmdtype			a_cmd;		//commande after maillon (le dernier maillon sera forcement NONE/0)
	struct s_parsing	*next;
}			t_parsing;

////////exec
int		ft_exec_all_cmd(t_parsing *params, char **envp);
void	ft_exec(t_parsing *params, char **envp);
int open_file(t_parsing *params, char *file);

//exec_utils.c
int		open_file(t_parsing *params, char *file);
char	*get_right_path(t_parsing *params, char **envp);
char	**get_cmd_path(char **envp);
void	ft_free_params(t_parsing *params);
void	ft_free_file(t_file *file);

//redirection.c
t_parsing	*ft_redir(t_parsing *params, char**envp);
t_parsing	*ft_exec_redir(t_parsing *params, char **envp);

//build_in.c
int	is_built_in(t_parsing *params, char *cmd, char **envp);

//pipe.c
t_parsing	*ft_pipe(t_parsing *params, char **envp);

////////parsing
//parsing.c
int		parsing(char *argv, t_parsing *param, char **envp);

//parsing_utils.c
int 	init_param(t_parsing *param);
char	*ft_line(char *line, char buf);
char	ft_strcpy(char *dest, char *src);
int		ft_init(t_parsing *param);
void	ft_pass_space(char *argv, int *i);

//parsing_tabs.c
int		ft_paste_tab(t_parsing *param, char **new, char *line);
void	free_tabs(char **tabs);
char	**ft_malloc_tab(t_parsing *param, int len_tab, char *line);
int		ft_len_tabs(char **tab);
int		ft_tabs(t_parsing *parsing, char *line);

//parsing_quote.c
char	*ft_add_double_quote(t_parsing *param, int *i, char *argv, char *line);
int		ft_add_simple_quote(t_parsing *param, int *i, char *argv, char *line);
int		ft_check_quote(char *line, int a);
char	*ft_double_quote(char *line, int *i, char *argv, t_parsing *param);
void	ft_pass_dquote(char *argv, int *i);

//parsing_quote2.c
int 	ft_simple_quote(char *line, int *i, char *argv, t_parsing *param);
void	ft_pass_squote(char *argv, int *i);


//check_redoc.c
void	ft_define_redicretcion(char *argv, int *i, t_parsing *param);
int		ft_check_redoc(char *argv, int i);

//stack_alloc.c
int		alloue_elem(t_parsing *param);
int		ft_add_maillon(t_parsing *param);
void    ft_index(t_parsing *param);
void	ft_nb_cmd(t_parsing *param, int i);


//add_file.c
int		ft_add_file(t_parsing *param, int *i, char *argv, char *line);
int		ft_add_to_fstack(t_parsing *param, char *line);

//env_liste.c
int		env_list(t_env  **env, char **envp);
int		ft_malloc_env(t_env	**env);
int		ft_find_variable(t_env *env, char *envp);
void	free_env(t_env **env);

//varaible_env.c
char	*find_var(char **envp, char *line);
char	*ft_check_dolar(char *line, char **envp);


////////built_in
char	*get_path(char **envp, char *to_find, int *i);
char	*ft_get_home(char **envp);
int		ft_cd(char **envp, char *path);
int		ft_env(int fd, char **envp);
int		ft_pwd(int fd);
void	ft_exit(char *exit_line);
int		ft_echo(int fd, char **arg);


////////signal

//signal.c
void	ft_sigint(int sig);
void	ft_sigquit(int sig);

#endif
