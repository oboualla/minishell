/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modifier_argument.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 23:33:31 by oboualla          #+#    #+#             */
/*   Updated: 2019/12/05 10:38:08 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static int	get_origcmd(char **line)
{
	t_rmpcmd	*lst;
	char		*ptr;

	ptr = *line;
	lst = g_mat->rmpcmd;
	while (lst)
	{
		if (!ft_strccmp(ptr, lst->rem, ' ')
			|| !ft_strccmp(ptr, lst->rem, ';'))
		{
			if (!(*line = ft_remplacer_str(ptr, lst->rem, lst->origine)))
				return (0);
			free(ptr);
			if (!(ptr = ft_strchr(*line, ';')))
				break ;
			ptr++;
			lst = g_mat->rmpcmd;
		}
		else
			lst = lst->next;
	}
	return (1);
}

int			modifier_argument(char **line)
{
	char	*ptr;
	int		i;

	i = -1;
	if (!(get_origcmd(line)))
		return (0);
	ptr = *line;
	while (ptr[++i])
	{
		if (ptr[i] == '~' && (i == 0 || ptr[i - 1] == ' '))
			if (!(modifier_path(line)))
				return (0);
		if (ft_strchr(ptr, '$'))
			if (!(modifier_val(line)))
				return (0);
		ptr = *line;
	}
	return (1);
}
