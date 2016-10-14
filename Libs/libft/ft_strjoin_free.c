/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmunoz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/07 16:44:57 by jmunoz            #+#    #+#             */
/*   Updated: 2016/10/07 16:49:45 by jmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char **s1, char const *s2)
{
	char	*s3;

	s3 = NULL;
	if (s1 && s2)
	{
		s3 = ft_strnew(ft_strlen(*s1) + ft_strlen(s2));
		if (!s3)
			return (NULL);
		s3 = ft_strcpy(s3, *s1);
		s3 = ft_strcat(s3, s2);
	}
	free(*s1);
	*s1 = NULL;
	return (s3);
}
