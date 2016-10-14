/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmunoz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/01 14:24:03 by jmunoz            #+#    #+#             */
/*   Updated: 2016/10/10 17:23:07 by jmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static void		refresh_pwd(char *pwd)
{
	cmd_setenv("OLDPWD", ft_getenv("PWD", g_env), 1, ENV);
	cmd_setenv("PWD", pwd, 1, ENV);
}

static int		check_cd(char *pwd)
{
	struct stat	buf;
	char		*tmp;
	int			err;

	err = 0;
	if (ft_strchr((pwd + 1), '/'))
	{
		tmp = ft_strdup(pwd);
		tmp = ft_path_back(tmp, '/');
		if (check_cd(tmp) == 0)
		{
			free(tmp);
			return (0);
		}
		free(tmp);
	}
	lstat(pwd, &buf);
	if (access(pwd, F_OK) == -1)
		err = ERCDNOTFOUND;
	else if (!(buf.st_mode & S_IFDIR))
		err = ERCDNOTDIR;
	else if (access(pwd, R_OK) == -1)
		err = ERCDACCESS;
	return ((!err) ? 1 : ft_err(err, pwd));
}

static char		*build_pwd(char *str, char *pwd)
{
	int	i;
	int	size;

	size = 0;
	i = (*str == '~' || *str == '-') ? 1 : 0;
	while ((size = ft_strlenc(&str[i], '/')) != -1)
	{
		if (!size || (!ft_strncmp(&str[i], ".", size) && size == 1))
			i++;
		else if (!ft_strncmp(&str[i], "..", size) && size == 2)
		{
			pwd = ft_path_back(pwd, '/');
			if (!*pwd)
				*pwd = '/';
			i += size;
		}
		else
		{
			pwd = ft_strcat(pwd, "/");
			pwd = ft_strncat(pwd, &str[i], size);
			i += size;
		}
	}
	return (pwd);
}

int				cmd_cd(char **tab)
{
	int		size;
	char	*pwd;

	pwd = ft_strnew(200);
	if ((size = ft_size_tab(tab)) > 3)
		return (ft_err(ERCDMULT, tab[1]));
	else if (size == 2)
		pwd = ft_strcpy(pwd, ft_getenv("HOME", g_env));
	else
	{
		if (tab[1][0] == '~')
			pwd = ft_strcpy(pwd, ft_getenv("HOME", g_env));
		else if (tab[1][0] == '-')
			pwd = ft_strcpy(pwd, ft_getenv("OLDPWD", g_env));
		else if (tab[1][0] != '/')
			pwd = ft_strcpy(pwd, ft_getenv("PWD", g_env));
		if (!ft_strlen((pwd = build_pwd(tab[1], pwd))))
			pwd[0] = '/';
	}
	if (check_cd(pwd) == 0)
		return (1);
	if (chdir(pwd) != -1)
		refresh_pwd(pwd);
	free(pwd);
	return (1);
}
