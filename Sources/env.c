/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmunoz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 18:46:00 by jmunoz            #+#    #+#             */
/*   Updated: 2016/10/07 19:06:57 by jmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static void		cmd_env_set(char *str)
{
	char *name;

	name = ft_strnew(100);
	name = ft_strncpy(name, str, ft_strlenc(str, '='));
	cmd_setenv(name, (ft_strchr(str, '=') + 1), 1, ENV_TMP);
	free(name);
}

static void		cmd_env_options(char **tab, int size, int *i)
{
	char *name[2];

	name[1] = NULL;
	if (!ft_strcmp(tab[0], "-i") || !ft_strcmp(tab[0], "--i"))
		ft_freetab(&g_envtmp);
	else if (!ft_strcmp(tab[0], "-u") || !ft_strcmp(tab[0], "--u"))
	{
		if (!tab[1])
			ft_err(ERUNSETARG, "u");
		else
		{
			name[0] = ft_strncpy(ft_strnew(100), tab[1], ft_strlenc(tab[1], '='));
			if (g_envtmp)
				cmd_unsetenv(name, g_envtmp);
			free(name[0]);
			(*i)++;
		}
	}
	else
	{
		ft_err(ERUNSETOPT, ft_strrchr(tab[0], '-') + 1);
		*i = size + 1;
	}
}

int				cmd_env(char **tab)
{
	int		size;
	int		i;

	i = 0;
	if (!(g_envtmp = ft_tabdup(g_env)))
		return (write_err("La copie de l'environnement a echoue !"));
	size = ft_size_tab(tab) - 1;
	while (++i < size)
	{
		if (tab[i][0] == '-')
			cmd_env_options(&tab[i], size, &i);
		else if (ft_strchr(tab[i], '='))
			cmd_env_set(tab[i]);
		else
		{
			launch_bin(&(tab[i]), g_envtmp, 1);
			i = size + 1;
		}
	}
	if (i == size && g_envtmp)
		print_env(g_envtmp);
	if (g_envtmp)
		ft_freetab(&g_envtmp);
	g_envtmp = NULL;
	return (1);
}
