

//////////HEADER///////////



#include "../../inc/minishell.h"

int	init_param(t_parsing *param)
{
	param->nb_cmd = 0;
	param->tabs = malloc(sizeof(char *) * 1);
	if (!param->tabs)
		return (0);
	param->tabs[0] = NULL;
	param->pipe = 0;
	return (1);
}
