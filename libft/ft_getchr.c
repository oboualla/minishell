/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 16:45:20 by oboualla          #+#    #+#             */
/*   Updated: 2019/09/17 21:05:10 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <termios.h>

char	ft_getchr(void)
{
	struct termios	trm;
	struct termios	bckp;
	char			buff[2];

	if (tcgetattr(0, &trm) == -1 || tcgetattr(0, &bckp) == -1)
		return (0);
	trm.c_lflag &= ~(ICANON);
	trm.c_lflag &= ~(ECHO);
	if (tcsetattr(0, 0, &trm) == -1)
		return (0);
	buff[1] = '\0';
	if (read(0, buff, 1) == -1)
		return (0);
	if (tcsetattr(0, 0, &bckp) == -1)
		return (0);
	return (buff[0]);
}
