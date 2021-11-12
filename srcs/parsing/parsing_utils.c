

//////////HEADER///////////



#include "../../inc/minishell.h"

int	init_param(t_parsing *param)
{
	param->nb_cmd = 0;
	param->tabs = NULL;
	param->pipe = 0;
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

int	ft_len_tabs(char **tab)
{
	int i;

	i = 0;
	if (!tab)
		return (0);
	while(tab[i])
		i++;
	return (i);
}

char	**ft_malloc_tab(t_parsing *param, int len, char *line)
{
	char	**new;
	if (len == 0)
	{
		if (!(new = malloc(sizeof(char *) * 2))) //line + NULL
			return (0);
		printf("la\n");
		new[0] = line;
		new[1] = NULL;
		return (new);
	}
	if (!(new = malloc(sizeof(char *) * len + 2))) //line + NULL
		return (0);
	ft_paste_tab(param, new, line);
	//copier old tabs in new + mettre line dans le dernier tab[i] et tab[++i] = NULL 
	//free_tabs(param->tab);
	return (new);
}

int	ft_tabs(t_parsing *param, char *line)
{
	(void)line;
	int	len;

	len = ft_len_tabs(param->tabs);								//len de tabs
	printf("len de tabs %d\n", len);
	if (!(param->tabs = ft_malloc_tab(param, len, line)))		//aloue tab + 1
		return (0);
	//copier old tabs in new + mettre line dans le dernier tab[i] et tab[++i] = NULL
	//->je copie dans ft_malloc_tab
	//free(line)--> faux, on free apres l'execution a la fin du main//
	return (1);
}