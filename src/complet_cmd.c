/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complet_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 16:58:49 by oboualla          #+#    #+#             */
/*   Updated: 2019/12/05 10:49:42 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static char	*get_new_cmd(char **path)
{
	char	*tmp;
	char	*ptr2;
	char	*ncmd;

	if (!(ncmd = ft_strnew(0)))
		return (NULL);
	while (1)
	{
		ft_putstr("dquote> ");
		if (get_cmd(&tmp, path) == -1)
			return (NULL);
		ptr2 = ncmd;
		ncmd = ft_strjoin(ncmd, tmp);
		free(ptr2);
		ft_strdel(&tmp);
		if (ft_strchr(ncmd, 34))
			break ;
	}
	return (ncmd);
}

static int	calc_len(char *ptr, char *cmd)
{
	int len;

	len = 0;
	while (cmd[len] != '\0' && &cmd[len] != &*ptr)
		len++;
	return (len);
}

static int	complet_cmd(char *ptr, char **line, char **tmp, char **path)
{
	char	*ncmd;
	char	*tmp2;
	int		len;

	len = calc_len(ptr, *line);
	if (!ft_strchr(ptr + 1, 34))
	{
		if (!(ncmd = get_new_cmd(path)))
			return (-1);
		tmp2 = *line;
		if (!(*line = ft_strjoin(*line, ncmd)))
			return (-1);
		free(tmp2);
		free(ncmd);
		*tmp = ft_strchr(*line + len + 1, '"');
		len = 0;
	}
	else
		*tmp = ft_strchr(ptr + 1, 34);
	return (len);
}

void		modifier_cmd(char **cmd, char **path)
{
	char	*tmp;
	int		i;

	if (!*cmd)
		return ;
	i = -1;
	tmp = *cmd;
	*cmd = ft_strtrim(*cmd);
	ft_strdel(&tmp);
	if (!*cmd[0])
		ft_strdel(cmd);
	else
	{
		tmp = *cmd;
		while (tmp[++i])
			if (tmp[i] == 34)
				i = complet_cmd(tmp + i, cmd, &tmp, path);
	}
}
