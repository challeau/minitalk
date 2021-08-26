/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: challeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 13:30:47 by challeau          #+#    #+#             */
/*   Updated: 2021/02/06 13:30:47 by challeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_add_char(char *src, char to_add)
{
	size_t	i;
	char	*new;

	i = 0;
	new = ft_calloc(ft_strlen(src) + 2);
	while (src[i])
	{
		new[i] = src[i];
		i++;
	}
	new[i] = to_add;
	new[i + 1] = '\0';
	ft_memdel(src);
	return (new);
}
