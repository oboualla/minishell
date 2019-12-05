/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   changer_directory.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 19:56:53 by oboualla          #+#    #+#             */
/*   Updated: 2019/12/05 10:37:44 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static int		is_dir(char *path)
{
	struct stat st;

	if (stat(path, &st) == -1)
	{
		error(path, "cd: not such or directory: ", ERR_AF);
		return (0);
	}
	if ((st.st_mode & S_IFMT) != S_IFDIR)
	{
		error(path, "cd: not a directory: ", ERR_AF);
		return (0);
	}
	if (access(path, X_OK | F_OK) == -1)
	{
		define_error(path, DIRECTORY_ERR);
		return (0);
	}
	return (1);
}

static char		*change_oldpwd(void)
{
	char	*tmp;
	char	*oldpwd;
	t_env	*ptr;

	oldpwd = NULL;
	if ((ptr = get_ptr(g_mat->lst[1], "OLDPWD")))
	{
		oldpwd = ptr->path;
		if (!(ptr->path = ft_strnew(100)))
			return (NULL);
		getcwd(ptr->path, 100);
		tmp = ptr->path;
		ptr->path = ft_strjoin("=", tmp);
		ft_strdel(&tmp);
		tmp = ptr->path;
	}
	if ((ptr = get_ptr(g_mat->lst[0], "OLDPWD")))
	{
		ft_strdel(&ptr->path);
		ptr->path = ft_strdup(tmp);
	}
	return (oldpwd);
}

void			changer_directory(char **av, int ac)
{
	t_env	*ptr;
	char	*oldpwd;

	oldpwd = change_oldpwd();
	if (ac == 3)
		error("cd: to many argument", NULL, ERR_AF);
	else if (!av[1])
	{
		if (!(ptr = get_ptr(g_mat->lst[1], "HOME")))
			return ;
		chdir(ptr->path + 1);
	}
	else
	{
		if (!ft_strcmp(av[1], "-") && oldpwd)
		{
			free(av[1]);
			av[1] = ft_strdup(oldpwd + 1);
		}
		if (is_dir(av[1]))
			chdir(av[1]);
	}
	ft_strdel(&oldpwd);
}
