/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmunoz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/07 18:20:46 by jmunoz            #+#    #+#             */
/*   Updated: 2016/10/10 18:37:17 by jmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static void		ft_putstr_echo(char *s)
{
	int		i;
	int		size;
	char	*path;

	i = -1;
	if (s)
	{
		while (s[++i])
		{
			if (s[i] == '$')
			{
				size = ft_strlenc(&s[i + 1], ' ');
				path = ft_strncpy(ft_strnew(size), &s[i + 1], size);
				ft_putstr(ft_getenv(path, g_env));
				free(path);
				i += size + 1;
			}
			ft_putchar(s[i]);
		}
	}
}

int				ft_echo(char **tab)
{
	int		i;
	char	ret;

	ret = 0;
	i = 0;
	if (tab[1] && !ft_strcmp(tab[1], "-n"))
	{
		ret++;
		i++;
	}
	while (tab[++i])
	{
		ft_putstr_echo(tab[i]);
		if (tab[i + 1])
			ft_putchar(' ');
	}
	if (!ret)
		ft_putchar('\n');
	return (1);
}
