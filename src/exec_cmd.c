/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 14:25:11 by oboualla          #+#    #+#             */
/*   Updated: 2019/12/05 10:43:03 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static int		check_err(char *cmd)
{
	if (access(cmd, F_OK) == -1)
	{
		error(cmd, "mini_shell: no such file or directory: ", ERR_AF);
		return (0);
	}
	else if (access(cmd, X_OK) == -1)
	{
		error(cmd, "mini_shell: permission denied: ", ERR_AF);
		return (0);
	}
	return (1);
}

static char		*new_test(char *cmd, char *path, char *orcmd)
{
	ft_strcpy(cmd, path);
	ft_strcat(cmd, "/");
	ft_strcat(cmd, orcmd);
	return (cmd);
}

void			exec_cmd(char **av, char **path, char **env)
{
	char	cmd[1000];
	int		i;

	i = 0;
	bzero((void*)cmd, 1000);
	if (ft_strchr(av[0], '/') || !path)
	{
		if (ft_strstr(av[0], "./"))
			if (!(check_err(av[0])))
				exit(0);
		ft_strcpy(cmd, av[0]);
	}
	else
		new_test(cmd, path[i++], av[0]);
	while ((execve(cmd, av, env)) == -1)
	{
		if (path && path[i])
			new_test(cmd, path[i++], av[0]);
		else
		{
			define_error(av[0], CMD_NOT_FOUND);
			break ;
		}
	}
	exit(0);
}
