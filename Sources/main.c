/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmunoz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 18:14:14 by jmunoz            #+#    #+#             */
/*   Updated: 2016/10/14 15:10:21 by jmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static int		do_cmd(char **cmd, int *i)
{
	char	**tab;
	int		j;
	int		ac;

	j = -1;
	if (cmd)
		while (cmd[++j])
		{
			tab = ft_strsplit3(cmd[j], ' ', '\t', '"');
			if (tab && *tab)
			{
				ac = cmd_exit(tab, i);
				if (*i  == 2)
				{
					ft_freetab(&tab);
					return (ac);
				}
				ac = builtins(tab);
				if (ac < 0)
					launch_bin(tab, g_env, 0);
			}
			ft_freetab(&tab);
		}
	return (0);
}

static char		**ft_get_cmd(void)
{
	char	*str;
	char	**tab;
	int		i;

	i = 0;
	str = NULL;
	get_next_line(1, &str);
	tab = ft_strsplit(str, ';');
	free(str);
	return (tab);
}

int				main(int ac, char **av, char **envp)
{
	char	**cmd;
	int		i;
	int		exit;

	av[ac] = 0;
	i = 0;
	g_envtmp = NULL;
	g_env = ft_tabdup(envp);
	set_signals(0);
	while (i < 2)
	{
		g_pid = 0;
		ft_putstr("$> ");
		cmd = ft_get_cmd();
		exit = do_cmd(cmd, &i);
		ft_freetab(&cmd);
	}
	ft_freetab(&g_env);
	return (exit);
}
