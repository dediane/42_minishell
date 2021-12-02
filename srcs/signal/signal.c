

        ////HEADER////



#include "../../inc/minishell.h"

void	ft_sigint(int sig)
{
	(void)sig;
	printf("le signal est ctrl C\n");
	printf("afficher un nouveau prompt\n");
	// free all here
	exit (0);
}
void	ft_sigquit(int sig)
{
	(void)sig;
	printf("le signal est Ctrl \\\n");
}