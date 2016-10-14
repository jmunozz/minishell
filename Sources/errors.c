/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmunoz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 17:44:59 by jmunoz            #+#    #+#             */
/*   Updated: 2016/10/10 17:52:45 by jmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static int		ft_err3(char c, char *str)
{
	if (c == ERCDACCESS)
	{
		ft_putstr_fd("cd: permission denied: ", 2);
		ft_putendl_fd(str, 2);
	}
	if (c == ERCDNOTDIR)
	{
		ft_putstr_fd("cd: not a directory: ", 2);
		ft_putendl_fd(str, 2);
	}
	if (c == EREXEC)
	{
		ft_putstr_fd("zsh: permission denied: ", 2);
		ft_putendl_fd(str, 2);
		exit(-1);
	}
	if (c == EREXIT)
		ft_putendl_fd("exit: too many arguments", 2); 
	return (0);
}

static int		ft_err2(char c, char *str)
{
	if (c == ERUNSETOPT)
	{
		ft_putstr_fd("env: illegal option -- ", 2);
		ft_putendl_fd(str, 2);
	}
	if (c == ERUNSETOPT || c == ERUNSETARG)
	{
		ft_putendl_fd("usage: env [-iv] [-P utilpath] [-S string],", 2);
		ft_putendl_fd(
		"           [-u name] [name=value ...] [utility [argument ...]]", 2);
	}
	if (c == ERENVDIR)
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": No such file or directory", 2);
	}
	if (c == ERCDMULT)
	{
		ft_putstr_fd("cd: string not in pwd: ", 2);
		ft_putendl_fd(str, 2);
	}
	return (ft_err3(c, str));
}

int				ft_err(char c, char *str)
{
	char *t;

	if (c == ERCDNOTFOUND)
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		if ((t = ft_strrchr(str, '/')))
			ft_putendl_fd(t + 1, 2);
		else
			ft_putendl_fd(str, 2);
	}
	if (c == ERPATH)
	{
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": cmd not found", 2);
	}
	if (c == ERUNSETARG)
	{
		ft_putstr_fd("env: option requires an argument -- ", 2);
		ft_putendl_fd(str, 2);
	}
	return (ft_err2(c, str));
}

int				write_err(char *str)
{
	ft_putendl_fd(str, 2);
	return (0);
}
