/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_to_find.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 20:31:54 by oboualla          #+#    #+#             */
/*   Updated: 2019/09/17 16:45:12 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_count_to_find(char *str, char *to_find)
{
	int i;
	int j;
	int count;

	count = 0;
	i = 0;
	j = 0;
	while (str[i])
	{
		j = 0;
		while (str[i + j] == to_find[j] && to_find[j] && str[i + j])
			j++;
		if (to_find[j] == '\0')
			count++;
		i++;
	}
	return (count);
}
