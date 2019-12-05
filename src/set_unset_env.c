/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_unset_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 16:18:54 by oboualla          #+#    #+#             */
/*   Updated: 2019/12/05 10:27:04 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static int	is_error(int ac, int mode)
{
	if ((mode & SETENV) && (ac == 4 || ac == 1))
	{
		if (ac == 1)
			error("setenv: ", "Too few arguments.", ERR_BF);
		else
			error("setenv: ", "Too many arguments.", ERR_BF);
		return (0);
	}
	else if ((mode & UNSETENV) && ac == 1)
	{
		error("unsetenv: ", "Too few arguments.", ERR_BF);
		return (0);
	}
	return (1);
}

t_env		*ft_setenv(t_env *ptr, char **av, int ac)
{
	if (!(is_error(ac, SETENV)))
		return (NULL);
	if (!ptr)
		return (NULL);
	while (ptr)
	{
		if (!ft_strcmp(ptr->var, av[1]))
		{
			ft_delelem(ptr);
			ptr->var = ft_strdup(av[1]);
			if (av[2])
				ptr->path = ft_strjoin("=", av[2]);
			else
				ptr->path = ft_strdup("=");
			return (ptr);
		}
		if (!ptr->next)
			break ;
		ptr = ptr->next;
	}
	if (ptr && !(ptr->next = newenv(av[1], av[2])))
		return (NULL);
	return (ptr->next);
}

t_env		*ft_unsetenv(t_env **alst, char **av, int ac)
{
	t_env	*ptr;
	int		i;

	ptr = *alst;
	if (!(is_error(ac, UNSETENV)))
		return (NULL);
	while (ptr)
	{
		i = 0;
		while (av[++i])
			if (!ft_strcmp(ptr->var, av[i]))
				if (!(delthis(&*alst, &ptr)))
					break ;
		ptr = ptr->next;
	}
	return (*alst);
}
