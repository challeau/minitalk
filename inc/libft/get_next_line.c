/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: challeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 13:30:47 by challeau          #+#    #+#             */
/*   Updated: 2021/02/06 13:30:47 by challeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_sep_rest(char *line, char **rest)
{
	int		ret;
	size_t	nl;

	if (ft_strchr(line, '\n') >= 0)
		ret = 1;
	else
		ret = 0;
	nl = ft_strchr(line, '\n');
	ft_memdel(*rest);
	if (*line != '\0')
	{
		*rest = ft_strdup(line + nl + 1);
		line[nl] = '\0';
	}
	else
		*rest = ft_strdup("");
	return (ret);
}

int	get_next_line(int fd, char **line)
{
	int			ret;
	char		*buff;
	static char	*rest;

	if (!line || fd < 0)
		return (-1);
	ret = 1;
	buff = ft_calloc(255);
	if (!rest)
		rest = ft_calloc(255);
	*line = ft_strdup(rest);
	while (ft_strchr(*line, '\n') < 0 && ret > 0)
	{
		ret = read(fd, buff, 255);
		*line = ft_strjoin(*line, buff);
		buff = ft_calloc(255);
	}
	ft_memdel(buff);
	if (ret < 0)
		return (-1);
	ret = ft_sep_rest(*line, &rest);
	if (ret == 0)
		ft_memdel(rest);
	return (ret);
}
