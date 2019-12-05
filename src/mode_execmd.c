/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode_execmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 19:35:38 by oboualla          #+#    #+#             */
/*   Updated: 2019/09/18 18:47:48 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static int	shell_cmd(char **av, int ac, char **path)
{
	if (!ft_strcmp(av[0], "alias"))
	{
		remplace_cmd(av, path, &g_mat->rmpcmd);
		return (0);
	}
	else if (!ft_strcmp(av[0], "setenv"))
	{
		ft_setenv(g_mat->lst[0], av, ac);
		return (0);
	}
	else if (!ft_strcmp(av[0], "unsetenv"))
	{
		ft_unsetenv(&g_mat->lst[0], av, ac);
		return (0);
	}
	else if (!ft_strcmp(av[0], "echo"))
	{
		me_echo(av);
		return (0);
	}
	return (1);
}

int			mode_execmd(char **av, int ac)
{
	char	**path;
	char	**env;
	pid_t	pid;

	env = NULL;
	if (!ft_strcmp(av[0], "exit"))
		return (0);
	path = my_path(g_mat->lst[0]);
	if (!(shell_cmd(av, ac, path)))
	{
		freedouble(path);
		return (1);
	}
	else if ((pid = fork()) != -1)
	{
		env = switch_lstenv(g_mat->lst[0]);
		if (pid == 0)
			exec_cmd(av, path, env);
		signal(SIGINT, sig2);
		wait(NULL);
	}
	freedouble(env);
	freedouble(path);
	return (1);
}
