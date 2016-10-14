/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmunoz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 14:56:30 by jmunoz            #+#    #+#             */
/*   Updated: 2016/10/14 15:10:30 by jmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/uio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <dirent.h>
# include "../Libs/libft/Includes/libft.h"

# define ERCDNOTFOUND 1
# define ERPATH 2
# define ERCDMULT 3
# define ERUNSETARG 4
# define ERUNSETOPT 5
# define ERENVDIR 6
# define ERCDACCESS 7
# define ERCDNOTDIR 8
# define EREXEC 9
# define EREXIT 10
# define ABSOLUTE 0
# define RELATIVE 1
# define ENV_TMP 0
# define ENV 1

pid_t	g_pid;
char	**g_env;
char	**g_envtmp;

int		ft_getenvline(char *str, char **e);
char	**ft_getenvtab(char *str, char **e);
char	*ft_getenv(char *str, char **e);
void	freetab(char ***tab);

int		launch_bin(char **tab, char **e, char mode);

int		ft_err(char c, char *str);
int		write_err(char *str);

int		cmd_cd(char **tab);
int		cmd_setenv(char *name, const char *value, int overwrite, int mode);
int		cmd_unsetenv(char **tab, char **e);
int		cmd_env(char **tab);

int		builtins(char **tab);
int		cmd_exit(char **tab, int *i);

void	print_env(char **e);

void	set_signals(int mode);
void	signal_handler(int signo);

int		ft_echo(char **tab);

#endif
