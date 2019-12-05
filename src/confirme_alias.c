/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   confirme_alias.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 17:48:29 by oboualla          #+#    #+#             */
/*   Updated: 2019/09/18 18:44:00 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static int	free_materiel(char *cmd, char *rmp, int ret)
{
	free(cmd);
	free(rmp);
	return (ret);
}

static int	confirme_cmd(char *cmd, char **path)
{
	char	test[1000];
	int		i;

	i = 0;
	ft_memset((void*)test, '\0', 1000);
	ft_strcpy(test, cmd);
	while (access(test, F_OK) == -1)
		if (path && path[i])
		{
			ft_memset((void*)test, '\0', 1000);
			ft_strcpy(test, path[i++]);
			ft_strcat(test, "/");
			ft_strcat(test, cmd);
		}
		else
			return (0);
	return (1);
}

static int	make_sure(char *cmd, char *rmp, char **path)
{
	if (!(confirme_cmd(cmd, path)))
	{
		error(cmd, "not existe command :", ERR_AF);
		return (free_materiel(cmd, rmp, -1));
	}
	if (confirme_cmd(rmp, path))
	{
		error(rmp, "is existe command :", ERR_AF);
		return (free_materiel(cmd, rmp, -1));
	}
	return (free_materiel(cmd, rmp, 1));
}

int			confirme_alias(char *argument, char **path)
{
	char	*cmd;
	char	*rmp;
	int		i;

	i = 0;
	while (argument[i] != '\0' && argument[i] != ' ' && argument[i] != '=')
		i++;
	if (argument[i] == '=' && argument[i + 1] == '\0')
		return (-1);
	else if (argument[i] == ' ' && !ft_strchr(argument, '='))
		return (-1);
	else if (argument[i] == '\0')
		return (-1);
	cmd = ft_strcdup(argument, argument[i]);
	rmp = ft_strdup(ft_strchr(argument, '=') + 1);
	if (!rmp || !cmd || rmp[0] == '\0')
		return (-1);
	return (make_sure(cmd, rmp, path));
}
