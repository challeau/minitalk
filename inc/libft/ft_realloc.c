/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: challeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 13:30:47 by challeau          #+#    #+#             */
/*   Updated: 2021/02/06 13:30:47 by challeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_realloc(char *str, size_t new_size)
{
	size_t	curr_size;
	char	*new;

	curr_size = ft_strlen(str);
	new = ft_calloc(new_size);
	if (new_size <= curr_size)
		ft_strlcpy(new, str, new_size);
	else
		ft_strlcpy(new, str, curr_size);
	ft_memdel(str);
	return (new);
}
