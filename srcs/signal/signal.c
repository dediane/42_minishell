/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-yaa <bben-yaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 20:11:36 by balkis            #+#    #+#             */
/*   Updated: 2022/01/19 13:33:55 by bben-yaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
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
	{
		write(1, "\n", 1);
		g_exit_value = 130;
	}
	else if (sig == SIGQUIT)
	{
		ft_putstr("Quit (core dumped)\n");
		g_exit_value = 131;
	}
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
