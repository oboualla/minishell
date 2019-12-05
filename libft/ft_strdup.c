/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 17:22:45 by oboualla          #+#    #+#             */
/*   Updated: 2019/11/20 05:53:58 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include "libft.h"

char	*ft_strdup(const char *str)
{
	char		*st;
	int			i;

	i = 0;
	if (!str)
		return (NULL);
	if (!(st = ft_memalloc(sizeof(char) * ft_strlen(str) + 1)))
		return (NULL);
	while (str[i])
	{
		st[i] = str[i];
		i++;
	}
	return (st);
}
