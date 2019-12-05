/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 21:22:39 by oboualla          #+#    #+#             */
/*   Updated: 2019/09/17 21:03:18 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *str, int size)
{
	char	*ret;

	if (!str)
		return (NULL);
	if (!(ret = (char*)ft_memalloc(sizeof(char) * (size + 1))))
		return (NULL);
	ft_strncpy(ret, str, size);
	return (ret);
}
