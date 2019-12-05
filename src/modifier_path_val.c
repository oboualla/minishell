/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modifier_path_val.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 15:50:52 by oboualla          #+#    #+#             */
/*   Updated: 2019/12/05 10:54:30 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static int	is_user(char *path)
{
	char	*user;
	char	*ptr;
	int		i;
	int		pt;

	pt = 0;
	i = -1;
	if (!(ptr = ft_strstr(path, "/Users/")))
		return (1);
	while (ptr[++i] != '\0' && pt < 2)
		if (ptr[i] == '/')
			pt++;
	pt = 1;
	if (!(user = ft_strndup(ptr, i)))
		return (-1);
	if (access(user, F_OK) == -1)
	{
		ft_putstr_fd("Unknown user :", 2);
		ft_putendl_fd(ft_strchr(user + 1, '/') + 1, 2);
		pt = 0;
	}
	free(user);
	return (pt);
}

int			modifier_path(char **path)
{
	t_env	*plst;
	char	*tmp;
	char	*ptr;

	tmp = *path;
	ptr = ft_strchr(tmp, '~');
	if (!(plst = get_ptr(g_mat->lst[1], "HOME")))
		return (1);
	*path = ft_remplacer_str(tmp, "~", plst->path + 1);
	if (ptr[1] != '\0' && ptr[1] != '/' && ptr[1] != ' ' && ft_isalnum(ptr[1]))
	{
		free(tmp);
		plst = get_ptr(g_mat->lst[1], "USER");
		tmp = *path;
		*path = ft_remplacer_str(tmp, plst->path + 1, "\0");
	}
	free(tmp);
	return (is_user(*path));
}

static char	*make_change(char *ptr)
{
	char	*change;
	int		i;

	i = 1;
	while (ptr[i] != '\0' && ft_isalnum(ptr[i]))
		i++;
	change = ft_strcdup(ptr, ptr[i]);
	return (change);
}

static int	what_wrong(char *change)
{
	if (change[1] == '\0')
		error(NULL, "Illegal variable name.", ERR_BF);
	else
		error(change + 1, ": Undefiend variable.", ERR_BF);
	free(change);
	return (0);
}

int			modifier_val(char **path)
{
	char	*change;
	char	*ptr;
	t_env	*ptr2;
	char	*tmp;

	tmp = *path;
	ptr = ft_strchr(tmp, '$');
	change = make_change(ptr);
	if ((ptr2 = get_ptr(g_mat->lst[0], change + 1)))
	{
		*path = ft_remplacer_str(tmp, change, ptr2->path + 1);
		free(tmp);
	}
	else
		return (what_wrong(change));
	free(change);
	if (ft_strchr(*path, '$'))
		modifier_val(path);
	return (1);
}
