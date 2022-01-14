/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 20:11:36 by balkis            #+#    #+#             */
/*   Updated: 2022/01/11 22:36:41 by ddecourt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_sigint(int sig)
{
	(void)sig;
	rl_redisplay();
	ft_putstr_fd("  \b\b", 1);
	write(1, "\n", 1);
	ft_putstr_fd("\033[1;35m~Minishell$\033[0m ", 0);
	rl_on_new_line();
	rl_redisplay();
	g_exit_value = 130;
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
	{
		signal(SIGINT, ft_ignore);
		signal(SIGQUIT, ft_ignore);
	}	
}

void	ft_launch_signal(void)
{
	signal(SIGINT, ft_sigint);
	signal(SIGQUIT, ft_sigquit);
}
