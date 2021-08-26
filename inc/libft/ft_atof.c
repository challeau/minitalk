/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: challeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 13:30:47 by challeau          #+#    #+#             */
/*   Updated: 2021/02/06 13:30:47 by challeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_sign(const char *str)
{
	int	sign;

	sign = 1;
	while (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	return (sign);
}

float	ft_atof(const char *str)
{
	int		sign;
	float	res;
	float	dec;
	float	deg;

	sign = get_sign(str);
	res = 0.0;
	dec = 0.0;
	deg = 1.0;
	while (*str == '-' || *str == '+')
		str++;
	while (ft_char_isdigit(*str) && *str != '.')
	{
		res = res * 10 + *str - 48;
		str++;
	}
	if (*str == '.')
		str++;
	while (ft_char_isdigit(*str))
	{
		dec = dec + (*str - 48) / (10 * deg);
		deg = deg * 10;
		str++;
	}
	return (sign * (res + dec));
}
