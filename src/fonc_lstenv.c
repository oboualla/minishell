/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonc_lstenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 10:10:29 by oboualla          #+#    #+#             */
/*   Updated: 2019/09/18 18:44:32 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

t_env		*get_ptr(t_env *lst, char *find)
{
	while (lst && (ft_strcmp(lst->var, find)))
		lst = lst->next;
	return (lst);
}

char		**my_path(t_env *lst)
{
	char	**path;
	t_env	*ptr;

	if (!(ptr = get_ptr(lst, "PATH")))
		return (NULL);
	if (!(path = ft_strsplit(ptr->path + 1, ':')))
		return (NULL);
	return (path);
}

void		freedouble(char **path)
{
	int i;

	i = 0;
	if (!path)
		return ;
	while (path[i])
		free(path[i++]);
	free(path);
}

size_t		ft_lstlen(t_env *lst)
{
	size_t size;

	size = 0;
	while (lst)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

char		**switch_lstenv(t_env *lst)
{
	char	**env;
	size_t	lstsize;
	int		i;

	i = 0;
	if (!lst)
		return (NULL);
	lstsize = ft_lstlen(lst);
	if (!(env = (char**)ft_memalloc(sizeof(char*) * (lstsize + 1))))
		return (NULL);
	while (lst)
	{
		env[i++] = ft_strjoin(lst->var, lst->path);
		lst = lst->next;
	}
	env[i] = NULL;
	return (env);
}
