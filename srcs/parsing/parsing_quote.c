



            ////////HEADER/////////




#include "../../inc/minishell.h"
int ft_double_quote(char *line, int *i, char *argv, t_parsing *param)
{
	if (line)											//->pour gls erer les cas d'interpretation si on a a="ls -la"
	{
		if (!ft_tabs(param, line))
			return (0);									//->secure malloc
		line = NULL;
	}
	if (!ft_add_double_quote(param, i, argv, line))	//-> pck on malloc
		return (0);
	return (1);
	///////tout les cas apres avoir mis les doubles quotes dans le tabs//////
}

void	ft_pass_dquote(char *argv, int *i)
{
	if (argv[(*i) + 1] == 34 || argv[(*i) + 1] == 39)			//pour gerer le cas de "bonjour"'cava'"comment"
		(*i)++;
	else if (argv[(*i) + 1] == ' ')						//->on pass tout les espaces
	{
		(*i)++;
		while (argv[(*i)] == ' ')
			(*i)++;
	}
	if (argv[(*i) + 1] == '<' || argv[(*i) + 1] == '>')	//c'est si la cmd = echo "hello">map.txt
		(*i)++;
}

int	ft_add_double_quote(t_parsing *param, int *i, char *argv, char *line)
{
	if (!(line = ft_line(line, argv[(*i)])))
			return (0);
	(*i)++;
	while(argv[(*i)] != 34 && argv[(*i)])
	{
		if (!(line = ft_line(line, argv[(*i)])))
			return (0);
		(*i)++;
	}
	if (!(line = ft_line(line, argv[(*i)])))
			return (0);
	if (!ft_check_quote(line, 34))
	{
		free (line);
		printf("les doubles quotes ne sont pas fermees\n");
		return (0);
	}
	if (!ft_tabs(param, line))
		return (0);
	return (1);
}

int	ft_add_simple_quote(t_parsing *param, int *i, char *argv, char *line)
{
	if (!(line = ft_line(line, argv[(*i)])))
			return (0);
	(*i)++;
	while(argv[(*i)] != 39 && argv[(*i)])
	{
		if (!(line = ft_line(line, argv[(*i)])))
			return (0);
		(*i)++;
	}
	if (!(line = ft_line(line, argv[(*i)])))
			return (0);
	if (!ft_check_quote(line, 39))
	{
		free (line);
		printf("les simples quotes ne sont pas fermees\n");
		return (0);
	}
	if (!ft_tabs(param, line))
		return (0);
	return (1);
}

int	ft_check_quote(char *line, int a)
{
	char c;
	int i;
	int p;

	i = 0;
	c = a;
	p = 0;
	while (line[i])
	{
		if (line[i] == c)
			p++;
		i++;
	}
	if (p % 2)
		return (0);
	else
		return (1);
}