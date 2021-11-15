



            ////////HEADER/////////




#include "../../inc/minishell.h"

int		ft_add_double_quote(t_parsing *param, int *i, char *argv, char *line)
{
	printf("here argv[i] %c\n", argv[(*i)]);
	if (!(line = ft_line(line, argv[(*i)])))
			return (0);
	(*i)++;
	printf("here argv[++i] %c\n", argv[(*i)]);
	while(argv[(*i)] != 34 && argv[(*i)])
	{
		if (!(line = ft_line(line, argv[(*i)])))
			return (0);
		printf("boucle argv[i] %c\n", argv[(*i)]);
		(*i)++;
	}
	if (!(line = ft_line(line, argv[(*i)])))
			return (0);
	printf("line dans quote une fois fini vaut %s\n", line);
	if (!ft_tabs(param, line))
		return (0);
	return (1);
}