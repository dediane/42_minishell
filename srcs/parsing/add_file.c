



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
	printf("line dans << vaut %s\n", line);
	if (!ft_add_to_fstack(param->file, line))
		return (0);
	free(line);
	return (1);
}

int	ft_add_to_fstack(t_file *file, char *line)
{
	t_file	*tmp;
	t_file	*new;
	char	*new_name;

	tmp = file;
	new = (t_file *)malloc(sizeof(t_file));
	new_name = malloc(sizeof(char) * (ft_strlen(line) + 1));
	if (!new || !new_name)
		return (0);
	if (!file)
	{
		file = new;
		new->next = NULL;
		ft_strcpy(new_name, line);
		printf("new name = %s\n",new_name);
		new->name = new_name;
	}
	return (1);
}