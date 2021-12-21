/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balkis <balkis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 20:11:36 by balkis            #+#    #+#             */
/*   Updated: 2021/12/21 20:56:00 by balkis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_sigint(int sig)
{
	(void)sig;
	rl_redisplay();
	ft_putstr_fd("  \b \b", 0);
	write(1, "\n", 1);
	//rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ft_sigquit(int sig)
{
	(void)sig;
}
// controle backslash ne fait rien

void	ft_ignore(int pid)
{
	if (pid == 0)
		printf("diseable\n");//diseable
	else
		printf("ignore\n");//ignore
}

void	ft_relaunch(int pid)
{
	if (pid > 0)
		printf("relaunche signal\n");
	//signal(SIGINT, ft_sigint);
	//signal(SIGQUIT, ft_sigquit);
}
