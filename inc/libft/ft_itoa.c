/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: challeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 23:00:44 by challeau          #+#    #+#             */
/*   Updated: 2020/04/27 23:01:16 by challeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int num)
{
	int		i;
	int		len;
	long	tmp;
	char	*dst;

	tmp = num;
	i = 0;
	len = ft_intlen(tmp);
	dst = (char *)malloc(len + 1);
	if (!dst)
		return (NULL);
	if (tmp < 0)
		tmp *= -1;
	while (i < len)
	{
		dst[i++] = (tmp % 10) + 48;
		tmp /= 10;
	}
	if (num < 0)
		dst[len - 1] = '-';
	dst[len] = '\0';
	ft_strrev(dst);
	return (dst);
}
