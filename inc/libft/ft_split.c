/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: challeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 13:30:47 by challeau          #+#    #+#             */
/*   Updated: 2021/02/06 13:30:47 by challeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static uint8_t	subdiv_count(const char *str, char sep)
{
	uint8_t	i;

	i = 0;
	while (*str)
	{
		while (*str && *str == sep)
			str++;
		if (*str == '\0')
			break ;
		i++;
		while (*str && *str != sep)
			str++;
	}
	return (i);
}

char	**ft_split(const char *str, char sep)
{
	size_t	i;
	size_t	j;
	size_t	next_sep;
	uint8_t	word_num;
	char	**new;

	i = 0;
	j = 0;
	word_num = subdiv_count(str, sep);
	new = (char **)malloc((word_num + 1) * sizeof(char *));
	if (!new)
		return (NULL);
	while (str[j])
	{
		while (str[j] && str[j] == sep)
			j++;
		next_sep = ft_strchr(str + j, sep);
		new[i] = ft_calloc(ft_strnlen(str + j, next_sep));
		ft_strlcpy(new[i++], str + j, next_sep);
		if (i == word_num)
			break ;
		j += next_sep;
	}
	new[i] = NULL;
	return (new);
}
