/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 20:57:44 by oboualla          #+#    #+#             */
/*   Updated: 2019/09/18 18:45:40 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static int	check_flag(char *flg)
{
	int flag;
	int i;

	i = 0;
	flag = 0;
	while (flg[++i] != '\0')
	{
		if (flg[i] == 'n')
			flag = 1;
		else
			return (0);
	}
	return (flag);
}

void		me_echo(char **av)
{
	int flag;
	int i;

	i = 0;
	flag = 0;
	while (av[++i] && av[i][0] == '-')
		if (!(flag = check_flag(av[i])))
			break ;
	while (av[i])
	{
		ft_putstr(av[i]);
		if (av[++i])
			ft_putchar(' ');
	}
	if (flag == 0)
		ft_putchar('\n');
}
