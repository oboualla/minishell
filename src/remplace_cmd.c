/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remplace_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 22:44:00 by oboualla          #+#    #+#             */
/*   Updated: 2019/09/18 18:49:39 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static t_rmpcmd	*new_rmpcmd(char *cmdrmp)
{
	t_rmpcmd *new;

	if (!(new = (t_rmpcmd*)ft_memalloc(sizeof(t_rmpcmd))))
		return (NULL);
	new->origine = ft_strcdup(cmdrmp, '=');
	new->rem = ft_strdup(ft_strchr(cmdrmp, '=') + 1);
	new->next = NULL;
	return (new);
}

static t_rmpcmd	*afflst_rempcmd(t_rmpcmd *lst)
{
	if (lst)
	{
		while (lst)
		{
			ft_putstr(lst->rem);
			ft_putchar('=');
			ft_putendl(lst->origine);
			lst = lst->next;
		}
	}
	return (NULL);
}

static t_rmpcmd	*add_rmpcmd(char **av, char **path)
{
	t_rmpcmd	*tmp;
	t_rmpcmd	*new;
	int			i;

	i = -1;
	new = NULL;
	while (av[++i])
	{
		if (confirme_alias(av[i], path) == 1)
		{
			tmp = new_rmpcmd(av[i]);
			if (!new)
				new = tmp;
			else
			{
				new->next = tmp;
				new = new->next;
			}
		}
	}
	return (new);
}

t_rmpcmd		*remplace_cmd(char **av, char **path, t_rmpcmd **alst)
{
	t_rmpcmd	*new;
	t_rmpcmd	*ptr;
	int			i;

	ptr = NULL;
	new = NULL;
	i = 0;
	if (!av[1])
		return (afflst_rempcmd(*alst));
	if ((ptr = *alst))
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = add_rmpcmd(av, path);
	}
	else
	{
		ptr = add_rmpcmd(av, path);
		if (!*alst)
			*alst = ptr;
	}
	return (ptr);
}
