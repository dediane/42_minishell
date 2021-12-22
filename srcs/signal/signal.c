/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-yaa <bben-yaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 20:11:36 by balkis            #+#    #+#             */
/*   Updated: 2021/12/22 13:27:16 by bben-yaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_sigint(int sig)
{
	(void)sig;
	rl_redisplay();
	write(1, "\n", 1);
	#if __LINUX__
		rl_replace_line("", 0);
	#endif
	#if __APPLE__
		ft_putstr_fd("\033[1;35m~Minishell$\033[0m ", 0);
	#endif
	rl_on_new_line();
	rl_redisplay();
}

void	ft_sigquit(int sig)
{
	(void)sig;
}

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
		printf("ignore\n");//ignore
}

void	ft_launch_signal(void);
{
	if (pid > 0)
		printf("relaunche signal\n");
	//signal(SIGINT, ft_sigint);
	//signal(SIGQUIT, ft_sigquit);
}
