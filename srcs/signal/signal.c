

        ////HEADER////



#include "../../inc/minishell.h"

void	ft_sigint(int sig)
{
	(void)sig;
	printf("le signal est ctrl C\n");
}
void	ft_sigquit(int sig)
{
	(void)sig;
	printf("le signal est Ctrl \\\n");
}