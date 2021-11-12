



/////////HEADER///////




#include "../../inc/minishell.h"

int	ft_paste_tab(t_parsing *param, char **new, char *line)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (param->tabs[y])
	{
		if (!(new[y] = malloc(sizeof(char) * ft_strlen(param->tabs[y] + 1)))) //aloue chaque ligne du tabs
			return (0);
		while (param->tabs[y][i])
		{
			new[y][i] = param->tabs[y][i];
			i++;
		}
		new[y][i] = '\0';
		i = 0;
		y++;
	}
	new[y] = line;
	new[++y] = NULL;
	return (1);
}