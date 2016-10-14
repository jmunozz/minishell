/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmunoz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/01 14:24:03 by jmunoz            #+#    #+#             */
/*   Updated: 2016/10/10 18:02:08 by jmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int				builtins(char **tab)
{
	int	overwrite;

	if (!(ft_strcmp(tab[0], "cd")))
		return (cmd_cd(tab));
	if (!(ft_strcmp(tab[0], "echo")))
		return (ft_echo(tab));
	if (!(ft_strcmp(tab[0], "setenv")) && tab[1])
	{
		overwrite = (ft_size_tab(tab) >= 5) ? ft_atoi(tab[3]) : 0;
		cmd_setenv(tab[1], tab[2], overwrite, ENV);
		return (1);
	}
	if (!(ft_strcmp(tab[0], "unsetenv")) && tab[1])
		return (cmd_unsetenv(&tab[1], g_env));
	if (!(ft_strcmp(tab[0], "env")))
		return (cmd_env(tab));
	if (!(ft_strcmp(tab[0], "exit")))
		return (2);
	else
		return (-1);
}

int		cmd_exit(char **tab, int *i)
{
	int		size;

	if (!(ft_strcmp(tab[0], "exit")))
	{
		*i = 2;
		size = ft_size_tab(tab);
		if (size == 2)
		   return (0);
		else if (size == 3)
			return (ft_atoi(tab[1]));
		else 
		{
			*i = 0;
			ft_err(EREXIT, NULL);
			return (0);
		}
	}
	return (0);
}
			
