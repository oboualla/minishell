/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 01:53:02 by oboualla          #+#    #+#             */
/*   Updated: 2019/12/05 10:47:20 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int			i;
	char		*str;
	int			j;
	int			k;

	k = 0;
	j = 0;
	i = 0;
	if (s == NULL)
		return (NULL);
	if (!(str = (char *)ft_memalloc(sizeof(char) * ft_count_char(s) + 1)))
		return (NULL);
	j = ft_skip_lensep(s, " \n\t");
	i = ft_skip_sep(s, " \n\t");
	while (i <= j)
		str[k++] = s[i++];
	str[k] = '\0';
	return (str);
}
