



    ///////HEADER///////




#include "../../inc/minishell.h"

int		alloue_elem(t_parsing *param)
{
	t_parsing	*new;

	new = (t_parsing *)malloc(sizeof(t_parsing));
	if (!new)
		return (0);
	if (!param)
	{
		param = new;
		printf("ICI WSH\n");
		if (!init_param(new))
			return (0);
		new->next = NULL;
		printf("PARAM existe normalement\n");
	}
	return (1);
}