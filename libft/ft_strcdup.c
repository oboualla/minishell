/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strcdup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 21:02:33 by oboualla          #+#    #+#             */
/*   Updated: 2019/08/11 18:38:10 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcdup(const char *str, char c)
{
	char	*ret;
	size_t	size;
	int		i;

	i = -1;
	size = 0;
	while (str[size] != '\0' && str[size] != c)
		size++;
	if (!(ret = (char*)ft_memalloc(sizeof(char) * (size + 1))))
		return (NULL);
	while (++i < (int)size)
		ret[i] = str[i];
	ret[i] = '\0';
	return (ret);
}
