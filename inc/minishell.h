#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

typedef	struct s_parsing
{
	int		nb_cmd;
	char	**tabs; //il y a la commande et les arguments dedans
	int		pipe;
}			t_parsing;

////////exec
void	ft_exec(char *line, char **envp);

////////parsing
//parsing.c
int	parsing(char *argv);

//parsing_utils.c
int 	init_param(t_parsing *param);
char	*ft_line(char *line, char buf);
int		ft_tabs(t_parsing *parsing, char *line);
int		ft_len_tabs(char **tab);

//parsing_tabs.c
int		ft_paste_tab(t_parsing *param, char **new, char *line);
void	free_tabs(char **tabs);
char	ft_strcpy(char *dest, char *src);




////////built_in
int	ft_env(int fd, char **envp);
int	ft_pwd(int fd, char** envp);

#endif
