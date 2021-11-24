


                //////HEADER////////



#include "../../inc/minishell.h"

int ft_simple_quote(char *line, int *i, char *argv, t_parsing *param)
{
	if (line)										//->pour gerer les cas d'interpretation si on a a='ls -la'
	{
		if (!ft_tabs(param, line))
			return (0);								//->secure malloc
		line = NULL;
	}
	if (!ft_add_simple_quote(param, i, argv, line))
		return (0);
	return (1);
}

void	ft_pass_squote(char *argv, int *i)
{
	if (argv[(*i) + 1] == 34)							//pour gerer le cas de "bonjour"'cava'"comment"
		(*i)++;
	else if (argv[(*i) + 1] == ' ')					//->on pass tout les espaces
	{
		(*i)++;
		while (argv[(*i)] == ' ')
			(*i)++;
	}
}

