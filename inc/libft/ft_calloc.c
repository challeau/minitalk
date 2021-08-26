/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: challeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 14:33:12 by challeau          #+#    #+#             */
/*   Updated: 2021/02/08 14:33:12 by challeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_calloc(size_t new_size)
{
	size_t	i;
	char	*new;

	i = 0;
	new = (char *)malloc(sizeof(char) + (new_size + 1));
	if (new == NULL)
		return (NULL);
	while (i <= new_size)
	{
		new[i] = '\0';
		i++;
	}
	return (new);
}
