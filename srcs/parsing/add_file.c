



                //////HEADER/////////



#include "../../inc/minishell.h"

int	ft_add_file(t_parsing *param, int *i, char *argv, char *line)
{
	while (argv[(*i)] == '<' || argv[(*i)] == '>' || argv[(*i)] == ' ')
		(*i)++;
	while (argv[(*i)] != ' ' && argv[(*i)])
	{
		line = ft_line(line, argv[(*i)]);
		if (!line)
			return (0);
		(*i)++;
	}
	if (!ft_add_to_fstack(param, line))
		return (0);
	free(line);
	return (1);
}

int	ft_add_to_fstack(t_parsing *param, char *line)
{
	t_file		*tmp;
	t_file		*new;
	t_parsing	*prm;
	char	*new_name;

	tmp = param->file;
	prm = param;
	new = (t_file *)malloc(sizeof(t_file));
	new_name = malloc(sizeof(char) * (ft_strlen(line) + 1));
	if (!new || !new_name)
		return (0);
	if (!param->file)
	{
		new->next = NULL;
		ft_strcpy(new_name, line);
		new->name = new_name;
		param->file = new;
	}
	else if (param->file)
	{
		while (tmp->next)
			tmp = tmp->next;
		new->next = NULL;
		ft_strcpy(new_name, line);
		new->name = new_name;
		tmp->next  = new;
	}
	return (1);
}