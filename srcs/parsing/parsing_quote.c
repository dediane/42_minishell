



            ////////HEADER/////////




#include "../../inc/minishell.h"

int		ft_add_double_quote(t_parsing *param, int *i, char *argv, char *line)
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
	if (!ft_tabs(param, line))
		return (0);
	return (1);
}

int		ft_add_simple_quote(t_parsing *param, int *i, char *argv, char *line)
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
	if (!ft_tabs(param, line))
		return (0);
	return (1);
}