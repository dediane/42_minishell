

        ////HEADER////



#include "../../inc/minishell.h"

void	ft_sigint(int sig)
{
	(void)sig;
	rl_redisplay();
	ft_putstr_fd("  \b \b", 0);
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
void	ft_sigquit(int sig)
{
	(void)sig;
}
// controle backslash ne fait rien

void	ft_ignore(int sig)
{
	if (sig == SIGINT)
		write(1, "\n", 1);
}
void	ft_disable(int pid)
{
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else
	{
		signal(SIGINT, ignore);
		signal(SIGQUIT, ignore);
	}
}

void	ft_launch_signal(void);
{
	signal(SIGINT, ft_sigint);
	signal(SIGQUIT, ft_sigquit);
}