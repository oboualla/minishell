/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objet.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 21:44:27 by oboualla          #+#    #+#             */
/*   Updated: 2019/12/05 10:21:14 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	error(char *path, char *message, int mode)
{
	if (mode & ERR_BF)
	{
		ft_putstr_fd(path, 2);
		ft_putendl_fd(message, 2);
	}
	if (mode & ERR_AF)
	{
		ft_putstr_fd(message, 2);
		if (path)
			ft_putendl_fd(path, 2);
	}
}

void	define_error(char *err, int errtype)
{
	if (errtype & CMD_NOT_FOUND)
		error(err, "mini_shell: command not found: ", ERR_AF);
	else if (errtype & DIRECTORY_ERR)
	{
		if (access(err, F_OK) == -1)
			error(err, "cd: no such file or directory: ", ERR_AF);
		else if (access(err, X_OK) == -1)
			error(err, "cd: permission denied: ", ERR_AF);
	}
}

void	sig1(int sig)
{
	(void)sig;
	ft_putchar('\n');
	ft_strdel(&g_mat->line);
	aff_prompt();
}

void	sig2(int sig)
{
	(void)sig;
	ft_strdel(&g_mat->line);
	ft_putchar('\n');
}

void	aff_prompt(void)
{
	t_env	*ptr;
	char	*buff;

	ptr = get_ptr(g_mat->lst[1], "USER");
	ft_putstr("\033[01;32m");
	if (ptr)
		ft_putstr(ptr->path + 1);
	ft_putstr("[\033[0;36m");
	buff = getcwd(NULL, 0);
	if (buff)
	{
		ft_putstr(buff);
		free(buff);
	}
	ft_putendl("\033[1;32m]");
	ft_putstr("$> ");
	ft_putstr("\033[0m");
}
