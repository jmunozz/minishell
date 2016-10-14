/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmunoz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 18:24:41 by jmunoz            #+#    #+#             */
/*   Updated: 2016/10/03 11:05:33 by jmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/libft.h"

static int		ft_strlenc2(char *str, char c, char d)
{
	int i;

	i = 0;
	if (!str || !str[i])
		return (-1);
	while (str[i])
	{
		if (str[i] == c || str[i] == d)
			return (i);
		i++;
	}
	return (i);
}

static char		**add_tab(char **tab, int size_tab)
{
	char	**new_tab;

	if (!(new_tab = (char**)malloc(sizeof(char*) * (size_tab + 1))))
		return (0);
	new_tab[size_tab] = NULL;
	if (size_tab == 1)
		return (new_tab);
	size_tab -= 2;
	while (size_tab >= 0)
	{
		new_tab[size_tab] = ft_strdup(tab[size_tab]);
		free(tab[size_tab]);
		size_tab--;
	}
	return (new_tab);
}

char			**ft_strsplit2(char const *s, char c, char d)
{
	char	**tab;
	char	**tabdup;
	int		size;
	int		size_tab;

	if (!(tab = (char**)malloc(sizeof(char*))))
		return (NULL);
	*tab = NULL;
	size_tab = 0;
	while (*s)
	{
		while (!(size = ft_strlenc2((char*)s, c, d)))
			s++;
		if (size == -1)
			return (tab);
		tabdup = tab;
		tab = add_tab(tab, ++size_tab);
		free(tabdup);
		tab[size_tab - 1] = ft_strncpy(ft_strnew(size), s, size);
		s += size;
	}
	return (tab);
}
