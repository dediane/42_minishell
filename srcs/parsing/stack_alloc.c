



    ///////HEADER///////




#include "../../inc/minishell.h"

int		alloue_elem(t_parsing *param)
{
	t_parsing	*new;

	new = (t_parsing *)malloc(sizeof(t_parsing));
	if (!new)
		return (0);
	if (!param)
		param = new;
	return (1);
}

int		ft_add_maillon(t_parsing *param)
{
	t_parsing	*tmp;
	t_parsing	*new;

	tmp = param;
	while(tmp->next)
		tmp = tmp->next;
	new = (t_parsing *)malloc(sizeof(t_parsing));
	if (!new)
		return (0);
	tmp->next = new;
	new->next = NULL;
	new->pipe = 0;
	new->index = 0; 
	new->tabs = NULL;
	new->type = NONE;
	new->file = NULL;
	new->nb_cmd = 0;
	return (1);
}
