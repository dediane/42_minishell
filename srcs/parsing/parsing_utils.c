

//////////HEADER///////////



#include "../../inc/minishell.h"

int	init_param(t_parsing *param)
{
	param->nb_cmd = 0;
	param->tabs = NULL;
	param->pipe = 0;
	param->ret = 0;
	param->type = NONE;
	param->file = NULL;
	return (1);
}

char	*ft_line(char *line, char buf)
{
	int		i;
	char	*new;

	if (line == NULL)
	{
		if(!(new = malloc(sizeof(char) * 2))) // buf + '\0'
			return (0);
		new[0] = buf;
		new[1] = '\0';
		return (new);
	}
	i = ft_strlen(line);
	if (!(new = malloc(sizeof(char) * (i + 2)))) //line + buf + '\0'
		return (0);
	i = 0;
	while(line[i])
	{
		new[i] = line[i];
		i++;
	}
	new[i] = buf;
	new[++i] = '\0';
	free(line);
	return (new);
}

char	ft_strcpy(char *dest, char *src)
{
	int i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	if (*dest)
		dest[i] = '\0';
	return (*dest);
}

