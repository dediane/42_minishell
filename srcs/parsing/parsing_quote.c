



            ////////HEADER/////////




#include "../../inc/minishell.h"
char	*ft_double_quote(char *line, int *i, char *argv, t_parsing *param)
{
	if (line)											//->pour gérer les cas d'interpretation si on a a="ls -la"
	{
		if (!ft_tabs(param, line))
			return (0);									//->secure malloc
		line = NULL;
	}
	return (ft_add_double_quote(param, i, argv, line));
}

void	ft_pass_dquote(char *argv, int *i)
{
	if (argv[(*i) + 1] && (argv[(*i) + 1] == 34 || argv[(*i) + 1] == 39))			//pour gerer le cas de "bonjour"'cava'"comment"
		(*i)++;
	else if (argv[(*i) + 1] && argv[(*i) + 1] == ' ')						//->on pass tout les espaces
	{
		(*i)++;
		while (argv[(*i)] == ' ')
			(*i)++;
	}
	else if (argv[(*i) + 1] && (argv[(*i) + 1] == '<' || argv[(*i) + 1] == '>'))	//c'est si la cmd = echo "hello">map.txt
		(*i)++;
	else if (argv[(*i)] == 34 && argv[(*i) + 1] && argv[(*i) + 1] != ' ')
		(*i)++;
}

char	*ft_add_double_quote(t_parsing *param, int *i, char *argv, char *line)
{
	(void)param;
	if (!ft_check_quote(&argv[*i], 34))
	{
		printf("les doubles quotes ne sont pas fermees\n");
		param->stop = 1;
		exit_value = 1;
		return (0);
	}
	(*i)++;
	while(argv[(*i)] != 34 && argv[(*i)])
	{
		if (!(line = ft_line(line, argv[(*i)])))
			return (0);
		(*i)++;
	}
	return (line);								///->et comme ca je peux checker directement pour la variable si elle exite
}

int	ft_add_simple_quote(t_parsing *param, int *i, char *argv, char *line)
{
	int	start;

	start = (*i);
	(*i)++;
	while(argv[(*i)] != 39 && argv[(*i)])
	{
		if (!(line = ft_line(line, argv[(*i)])))
			return (0);
		(*i)++;
	}
	if (!ft_check_quote(&argv[start], 39))
	{
		free (line);
		printf("les simples quotes ne sont pas fermees\n");
		exit_value = 1;
		return (0);
	}
	if (line)
		ft_tabs(param, line);
	return (1);
}

int	ft_check_quote(char *argv, int a)
{
	char c;
	int i;
	int p;

	i = 0;
	c = a;
	p = 0;
	if (argv[0] == c)
	while (argv[i])
	{
		if (i != 0 && argv[i + 1] && argv[i + 1] == c)
		{
			p++;
			break ;
		}
		if (argv[i] == c)
			p++;
		i++;
	}
	if (p % 2)
		return (0);
	else
		return (1);
}