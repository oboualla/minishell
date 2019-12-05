/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 16:28:00 by oboualla          #+#    #+#             */
/*   Updated: 2019/09/18 18:49:04 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static int	get_filelen(char **tab, int *howmany)
{
	struct winsize	ws;
	int				flen;
	int				i;
	int				howm;

	howm = 0;
	flen = 0;
	i = -1;
	ioctl(0, TIOCGWINSZ, &ws);
	while (tab[++i])
		if ((int)ft_strlen(tab[i]) > flen)
			flen = ft_strlen(tab[i]);
	i = flen + 1;
	while ((i += flen + 1) < ws.ws_col)
		howm++;
	if (!(howm))
		howm = 1;
	*howmany = howm;
	return (flen);
}

static int	putcomplet_cmd(char **complet, char *cmd, char **join)
{
	char	*ptr;
	int		i;

	i = 1;
	while (complet[0][i] && cmd[i] && complet[0][i] == cmd[i])
		i++;
	ft_putstr(&complet[0][i]);
	ptr = *join;
	*join = ft_strjoin(ptr, &complet[0][i]);
	free(ptr);
	free(complet[0]);
	free(complet);
	return (0);
}

static int	print_probabilities(char **tab, int flen, int howmany[2])
{
	int src;
	int i;

	i = 0;
	src = 0;
	ft_putchar('\n');
	while (tab[i])
	{
		ft_putstr(tab[i]);
		if ((src = ft_strlen(tab[i])) <= flen)
			while (++src <= (flen + 1))
				ft_putchar(' ');
		free(tab[i++]);
		if (i == howmany[0] && (howmany[0] += howmany[1]))
			ft_putchar('\n');
	}
	free(tab);
	ft_putchar('\n');
	return (1);
}

static int	calc_probabilities(char *str)
{
	int	nbr_prob;

	nbr_prob = ft_count_to_find(str, ":");
	if (nbr_prob > 50)
	{
		ft_putchar('\n');
		ft_putstr("mini_shell: do you wish to see all ");
		ft_putnbr(nbr_prob);
		ft_putstr(" possibilities ? y/n");
		if (ft_getchr() == 'y')
			return (1);
		ft_putchar('\n');
		return (0);
	}
	return (1);
}

int			print_file(char *str, char *comp, char **join)
{
	char	**tab;
	int		flen;
	int		howmany[2];

	if (!(tab = ft_strsplit(str, ':')))
		return (-1);
	if (!(tab[1]))
		return (putcomplet_cmd(tab, comp, join));
	flen = get_filelen(tab, &howmany[0]);
	howmany[1] = howmany[0];
	if (calc_probabilities(str) == 1)
		print_probabilities(tab, flen, howmany);
	return (1);
}
