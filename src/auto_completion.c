/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_completion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 21:15:57 by oboualla          #+#    #+#             */
/*   Updated: 2019/09/18 18:43:11 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static char		*get_lstfile(char *comp, char *path, char **str)
{
	DIR				*drp;
	struct dirent	*drt;
	char			*ptr;

	if ((drp = opendir(path)))
	{
		while ((drt = readdir(drp)))
			if (!(ft_strncmp(comp, drt->d_name, ft_strlen(comp))))
			{
				ptr = *str;
				*str = ft_strjoin(ptr, ":");
				free(ptr);
				ptr = *str;
				*str = ft_strjoin(ptr, drt->d_name);
				free(ptr);
			}
		closedir(drp);
	}
	return (*str);
}

static char		*get_path(char *cmd, int i)
{
	char	*path;
	int		j;

	if ((j = i) <= 0)
		return (NULL);
	while (j > 0 && cmd[j] != ' ')
		j--;
	if (j == 0 && cmd[i] != '/')
		return (NULL);
	else
	{
		if (cmd[j] == ' ' && cmd[i] != '/')
			return (ft_strdup("."));
		else if (j == 0)
			path = ft_strndup(&cmd[j], i - j + 1);
		else
			path = ft_strndup(&cmd[j + 1], i - j);
	}
	return (path);
}

static	void	complet_work(char **join, char *pa, char *comp, char **path)
{
	char	*ptr;
	int		i;

	i = -1;
	if (!(ptr = ft_strnew(0)))
		return ;
	if (!pa && path)
		while (path[++i])
			get_lstfile(comp, path[i], &ptr);
	else if (pa)
	{
		get_lstfile(comp, pa, &ptr);
		free(pa);
	}
	if (ptr[0] != '\0' && print_file(ptr, comp, join))
	{
		aff_prompt();
		ft_putstr(*join);
	}
	free(ptr);
}

void			auto_completion(char **join, char **path)
{
	char	*ptr;
	char	*comp;
	char	*pa;
	int		i;
	int		j;

	j = -1;
	i = 0;
	ptr = &(*join)[ft_skip_sep(*join, " ")];
	while (ptr[i] != '\0')
		i++;
	while (i > 0 && ptr[i - 1] != ' ' && ptr[i - 1] != '/')
		i--;
	if (ptr[i] == '\0')
		return ;
	if (!(comp = ft_strdup(&ptr[i])))
		return ;
	pa = get_path(*join, i - 1);
	complet_work(join, pa, comp, path);
	free(comp);
}
