



        ///////HEADER//////



#include "../../inc/minishell.h"

void	ft_define_redicretcion(char *argv, int *i, t_parsing *param)
{
	if (argv[(*i) + 1] == '<' && argv[(*i)] == '<')
		param->type = DOUBLEIN;
	else if (argv[(*i) + 1] == '>' && argv[(*i)] == '>')
		param->type = DOUBLEOUT;
	else if (argv[(*i) + 1] != '<' && argv[(*i)] == '<')
		param->type = IN;
	else if (argv[(*i) + 1] != '>' && argv[(*i)] == '>')
		param->type = OUT;
}


int	ft_check_redoc(char *argv, int i)
{
	int p;
	int j;

	p = 0;
	j = i;
	while(argv[i] == '>' || argv[i] == '<')
	{
		p++;
		i++;
	}
	if (p == 1 || p == 2)
	{
		if (p == 1)
			return (1);
		else if (p == 2 && argv[j] == argv[j + 1])
			return (1);
		else
			return (0);
	}
	else
		return (0);
}