/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmunoz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/10 12:00:54 by jmunoz            #+#    #+#             */
/*   Updated: 2016/10/14 15:13:51 by jmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	set_signals(int mode)
{
	if (!mode)
	{
		signal(SIGINT, &signal_handler);
		signal(SIGQUIT, &signal_handler);
		signal(SIGTERM, &signal_handler);
	}
	else
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGTERM, SIG_DFL);
	}
}

void	signal_handler(int signo)
{
	signo = 0;
	if (!g_pid) 
		ft_putstr("\n$> ");
	else 
		ft_putchar('\n');
}
