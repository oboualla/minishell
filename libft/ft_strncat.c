/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 17:35:58 by oboualla          #+#    #+#             */
/*   Updated: 2019/11/20 05:57:25 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *str, const char *str2, size_t nb)
{
	size_t i;
	size_t j;

	j = 0;
	i = 0;
	if (!str || !str2)
		return (NULL);
	i = ft_strlen(str);
	while (j < nb && str2[j])
	{
		str[i] = str2[j];
		j++;
		i++;
	}
	str[i] = '\0';
	return (str);
}
