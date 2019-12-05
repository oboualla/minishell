/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 21:55:01 by oboualla          #+#    #+#             */
/*   Updated: 2019/09/18 18:45:08 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	key_del(char *line)
{
	int i;

	i = 0;
	while (line[i] != '\0')
		i++;
	if (i == 0)
		return (0);
	ft_putstr("\b \b");
	line[i - 1] = '\0';
	return (1);
}

int	get_cmd(char **line, char **path)
{
	char buff[2];
	char *ptr;

	buff[1] = '\0';
	if (!line || !(*line = ft_strnew(0)))
		return (-1);
	while ((buff[0] = ft_getchr()) != '\n')
	{
		if (buff[0] == '\t' && (*line)[0] != '\0')
			auto_completion(line, path);
		else if (buff[0] != 127 && buff[0] != 27 && buff[0] != '\t')
		{
			ft_putstr(buff);
			ptr = *line;
			*line = ft_strjoin(ptr, buff);
			free(ptr);
		}
		else if (buff[0] == 127)
			key_del(*line);
	}
	ft_putchar('\n');
	return (1);
}
