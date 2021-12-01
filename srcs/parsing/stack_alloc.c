



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
	new->nb_cmd = 0;
	new->tabs = NULL;
	new->pipe = 0;
	new->index = 0;
	new->fd_stdout = 0; 
	new->fd_stdin = 0; 
	new->type = NONE;
	new->file = NULL;
	//new->b_cmd = NONE;
	//new->a_cmd = NONE;
	return (1);
}

void    ft_index(t_parsing *param)
{
	t_parsing	*tmp;
	int			i;

    tmp = param;
    i = 0;
	while (tmp)
	{
		param->nb_cmd = i;
		i++;
		tmp = tmp->next;
	}
}
 