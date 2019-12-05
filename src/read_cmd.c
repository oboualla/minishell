/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 13:53:13 by oboualla          #+#    #+#             */
/*   Updated: 2019/12/05 10:54:29 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static void	add_argv(t_sepcmd **alst, char *cmd)
{
	t_sepcmd *new;
	t_sepcmd *ptr;

	if (!(new = (t_sepcmd*)ft_memalloc(sizeof(t_sepcmd))))
		return ;
	if (!(new->av = make_params(cmd)))
		return ;
	new->next = NULL;
	if (!*alst)
		*alst = new;
	else
	{
		ptr = *alst;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
}

static void	modifier_tab(char **tab, char **path)
{
	int i;

	i = -1;
	while (tab[++i])
	{
		modifier_cmd(&tab[i], path);
		if (tab[i])
		{
			if ((modifier_argument(&tab[i])))
			{
				add_argv(&g_mat->sepcmd, tab[i]);
				ft_strdel(&tab[i]);
			}
			else
				ft_strdel(&tab[i]);	
		}
	}
	free(tab);
}

t_sepcmd	*read_cmd(char **line)
{
	t_env		*ptr;
	char		**path;
	char		**tab;

	path = NULL;
	if ((ptr = get_ptr(g_mat->lst[0], "PATH")))
		path = ft_strsplit(ptr->path + 1, ':');
	if (get_cmd(line, path) == -1)
	{
		freedouble(path);
		return (NULL);
	}
	modifier_cmd(line, path);
	if (!(tab = ft_strsplit(*line, ';')))
	{
		freedouble(path);
		return (NULL);
	}
	ft_strdel(line);
	modifier_tab(tab, path);
	freedouble(path);
	return (g_mat->sepcmd);
}
