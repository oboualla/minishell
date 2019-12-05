/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lstmateriel.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 21:35:44 by oboualla          #+#    #+#             */
/*   Updated: 2019/09/18 18:44:58 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	free_lstenv(t_env *lst)
{
	if (lst)
	{
		if (lst->next)
			free_lstenv(lst->next);
		free(lst->var);
		free(lst->path);
		free(lst);
	}
}

void	free_lstrmcmd(t_rmpcmd *lst)
{
	if (lst)
	{
		if (lst->next)
			free_lstrmcmd(lst->next);
		free(lst->origine);
		free(lst->rem);
		free(lst);
	}
}

void	free_lstsepcmd(t_sepcmd *sep)
{
	if (sep)
	{
		if (sep->next)
			free_lstsepcmd(sep->next);
		freedouble(sep->av);
		ft_memdel((void**)&sep);
	}
	g_mat->sepcmd = NULL;
}

void	free_lstmateriel(int flag)
{
	if ((flag & 2))
	{
		free_lstenv(g_mat->lst[0]);
		free_lstenv(g_mat->lst[1]);
		free_lstrmcmd(g_mat->rmpcmd);
	}
	if ((flag & 1))
		free_lstsepcmd(g_mat->sepcmd);
}
