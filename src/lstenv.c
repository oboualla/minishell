/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 20:50:45 by oboualla          #+#    #+#             */
/*   Updated: 2019/12/05 10:40:58 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	ft_delelem(t_env *ptr)
{
	if (ptr->var)
		ft_strdel(&ptr->var);
	if (ptr->path)
		ft_strdel(&ptr->path);
}

t_env	*delthis(t_env **lst, t_env **del)
{
	t_env *ptr;

	if (!*lst)
		return (NULL);
	ft_delelem(*del);
	if ((ptr = *lst) == *del)
	{
		*lst = (*lst)->next;
		free(ptr);
		return (*lst);
	}
	while (ptr->next != *del)
		ptr = ptr->next;
	ptr->next = (*del)->next;
	free(*del);
	*del = ptr;
	return (*lst);
}

t_env	*newenv(char *var, char *path)
{
	t_env *new;

	if (!(new = (t_env*)ft_memalloc(sizeof(t_env))))
		return (NULL);
	new->var = ft_strcdup(var, '=');
	if (!path)
		new->path = ft_strdup("=");
	else if (ft_strchr(path, '='))
		new->path = ft_strdup(path);
	else
		new->path = ft_strjoin("=", path);
	new->next = NULL;
	return (new);
}

t_env	*lstenv(char **env, t_env **alst)
{
	t_env	*ptr;
	t_env	*new;
	int		i;

	i = 0;
	if (!*alst && env)
	{
		if (!(*alst = newenv(env[i], ft_strchr(env[i], '='))))
			return (NULL);
		ptr = *alst;
		while (env[++i])
		{
			if (!(new = newenv(env[i], ft_strchr(env[i], '='))))
				return (NULL);
			ptr->next = new;
			ptr = new;
		}
	}
	return (*alst);
}
