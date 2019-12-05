/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 20:57:44 by oboualla          #+#    #+#             */
/*   Updated: 2019/12/05 10:54:34 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static t_env		*my_lstenv(t_env *lst, t_env **alst)
{
	t_env *ptr;
	t_env *tmp;

	ptr = NULL;
	while (lst)
	{
		if (!ft_strcmp(lst->var, "OLDPWD") ||
			!ft_strcmp(lst->var, "USER") || !ft_strcmp(lst->var, "HOME"))
		{
			tmp = ptr;
			ptr = newenv(lst->var, lst->path);
			if (!*alst)
				*alst = ptr;
			if (tmp)
				tmp->next = ptr;
		}
		lst = lst->next;
	}
	return (*alst);
}

static t_mat		*initializer_mat(char **env)
{
	if (!(g_mat = (t_mat*)ft_memalloc(sizeof(t_mat))))
		return (NULL);
	g_mat->line = NULL;
	g_mat->lst[0] = NULL;
	g_mat->lst[1] = NULL;
	if (!(lstenv(env, &g_mat->lst[0])))
		return (NULL);
	if (!(my_lstenv(g_mat->lst[0], &g_mat->lst[1])))
		return (NULL);
	g_mat->rmpcmd = NULL;
	g_mat->sepcmd = NULL;
	return (g_mat);
}

static int			get_lstsep(t_sepcmd *sep)
{
	int ac;

	while (sep)
	{
		ac = 0;
		while (sep->av[ac])
			ac++;
		if (!(ft_strcmp("cd", sep->av[0])))
			changer_directory(sep->av, ac);
		else if (!(mode_execmd(sep->av, ac)))
			return (0);
		sep = sep->next;
	}
	return (1);
}

int					main(int ac, char **av, char **environ)
{
	(void)ac;
	(void)av;
	initializer_mat(environ);
	while (1337)
	{
		signal(SIGINT, sig1);
		aff_prompt();
		if ((g_mat->sepcmd = read_cmd(&g_mat->line)))
		{
			if (!(get_lstsep(g_mat->sepcmd)))
			{
				free_lstmateriel(3);
				free(g_mat);
				exit(0);
			}
			free_lstmateriel(1);
		}
	}
	return (0);
}
