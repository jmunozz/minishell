/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmunoz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 14:55:29 by jmunoz            #+#    #+#             */
/*   Updated: 2016/10/14 15:10:47 by jmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"
#include <errno.h>

char	*find_bin(char *str, char **e)
{
	char			**path;
	DIR				*stream;
	struct dirent	*file;
	char			*ret;
	int				i;

	i = 0;
	ret = NULL;
	path = ft_getenvtab("PATH", e);
	while (path && path[i] != NULL && !ret)
	{
		if ((stream = opendir(path[i])))
		{
			while ((file = readdir(stream)) != NULL && !ret)
				if (!ft_strcmp(str, file->d_name))
				{
					ret = ft_strjoin(path[i], "/");
					ret = ft_strjoin_free(&ret, file->d_name);
				}
			closedir(stream);
		}
		i++;
	}
	ft_freetab(&path);
	return (ret);
}

int		launch_bin(char **tab, char **e, char mode)
{
	char	*path;
	//pid_t 	pid;

	if (tab[0][0] == '.' || tab[0][0] == '/')
		path = ft_strdup(tab[0]);
	else if (!(path = find_bin(tab[0], e)))
	{
		free(path);
		return (mode == 1 ? ft_err(ERENVDIR, tab[0]) : ft_err(ERPATH, tab[0]));
	}
	g_pid = fork();
	if (g_pid == 0)
	{
		set_signals(1);
		if (!mode && !ft_strcmp(ft_strrchr(path, '/'), "/minishell"))
			cmd_setenv("SHLVL",
			ft_itoa(ft_atoi(ft_getenv("SHLVL", e)) + 1), 1, ENV);
		if (execve(path, tab, e) == -1)
			ft_err(EREXEC, tab[0]);
	}
	else
		wait(NULL);
	free(path);
	return (0);
}
