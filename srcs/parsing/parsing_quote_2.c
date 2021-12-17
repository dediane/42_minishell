


                //////HEADER////////



#include "../../inc/minishell.h"

int ft_simple_quote(char *line, int *i, char *argv, t_parsing *param)
{
	if (line)										//->pour gerer les cas d'interpretation si on a a='ls -la'
	{
		if (!
		ft_tabs(param, line))
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

int		pos_dolar(char *line)
{
	int i;
	int len;

	i = 0;
	len = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			i++;
			while (line[i] && line[i] != ' ')
			{
				i++;
				len++;
			}
			return (len);
		}
		i++;
	}
	return (0);
}

char	*ft_copy(char *var, char *line, char *exp, int pos)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = pos_dolar(line);
	while (line[i] && i < (pos - 1))
	{
		var[i] = line[i];
		i++;
	}
	while (exp[j])
	{
		var[i] = exp[j];
		j++;
		i++;
	}
	if (line[pos + len])
	{
		while (line[pos + len])
		{
			var[i] = line[len + pos];
			i++;
			len++;
		}
	}
	var[i] = '\0';
	free(line);
	return (var);
}
