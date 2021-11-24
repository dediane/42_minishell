



            ////////HEADER/////////




#include "../../inc/minishell.h"

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
		if (c == 34 && line[i] == 39)
			p++;
		i++;
	}
	if (p % 2)
		return (0);
	else
		return (1);
}