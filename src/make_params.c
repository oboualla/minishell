/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_params.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 23:06:05 by oboualla          #+#    #+#             */
/*   Updated: 2019/09/18 18:45:31 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static size_t	size_param(const char *cmd)
{
	size_t	parm;
	int		i;

	i = 0;
	parm = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] != ' ')
		{
			parm++;
			if (cmd[i++] == '"')
				while (cmd[i] != '\0' && cmd[i] != '"')
					i++;
			else
				while (cmd[i] != '\0' && cmd[i] != ' ')
					i++;
		}
		i++;
	}
	return (parm);
}

static char		*ft_cpy_to(const char *param, char to, int *index)
{
	char	*ret;
	int		size;

	size = 0;
	while (param[size] != '\0' && param[size] != to)
		size++;
	if (!(ret = ft_strcdup(param, to)))
		return (NULL);
	if (to == '"')
		size += 2;
	*index += size;
	return (ret);
}

static int		pointer_params(const char *params, char **elem, char c, int *i)
{
	if (c == '"')
	{
		if (!(*elem = ft_cpy_to(params + 1, c, i)))
			return (-1);
	}
	else
	{
		if (!(*elem = ft_cpy_to(params, ' ', i)))
			return (-1);
	}
	return (1);
}

char			**make_params(const char *params)
{
	char	**argv;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!params)
		return (NULL);
	if (!(argv = (char**)ft_memalloc(sizeof(char*) * (size_param(params) + 1))))
		return (NULL);
	while (params[i] != '\0')
	{
		if (params[i] != ' ')
		{
			if (pointer_params(params + i, &argv[j], params[i], &i) == -1)
				return (NULL);
			j++;
		}
		else
			i++;
	}
	argv[j] = NULL;
	return (argv);
}
