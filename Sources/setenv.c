/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmunoz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 18:43:01 by jmunoz            #+#    #+#             */
/*   Updated: 2016/10/07 19:58:55 by jmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static char		*create_var_env(char *name, char *value)
{
	char *new_var;

	new_var = ft_strnew(ft_strlen(name) + ft_strlen(value) + 1);
	ft_strcpy(new_var, name);
	ft_strcat(new_var, "=");
	ft_strcat(new_var, value);
	return (new_var);
}

static void		cmd_setenv2(char **e, char *new_var, int mode)
{
	int		i;
	char	**tmp;

	i = ft_size_tab(e);
	if (i == -1)
		i = 1;
	tmp = e;
	e = ft_add_tab(e, i++);
	e[i - 2] = new_var;
	if (mode == ENV_TMP)
		g_envtmp = e;
	else
		g_env = e;
	if (tmp)
		ft_freetab(&tmp);
}

int				cmd_setenv(char *name, const char *value, int ov, int mode)
{
	char	*new_var;
	int		i;
	char	**e;

	e = (mode == ENV_TMP) ? g_envtmp : g_env;
	new_var = create_var_env(name, (char*)value);
	i = ft_getenvline(name, e);
	if (i != -1 && e[i] != NULL)
	{
		if (ov)
		{
			free(e[i]);
			e[i] = new_var;
		}
		return (1);
	}
	cmd_setenv2(e, new_var, mode);
	return (1);
}

int				cmd_unsetenv(char **tab, char **e)
{
	int		i;
	int		n;
	char	*tmp;

	n = 0;
	while (tab[n])
	{
		i = ft_getenvline(tab[n], e);
		tmp = e[i];
		while (e[i])
		{
			e[i] = e[i + 1];
			i++;
		}
		free(tmp);
		n++;
	}
	return (1);
}
