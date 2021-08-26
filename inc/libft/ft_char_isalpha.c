/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_isalpha.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: challeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 13:30:47 by challeau          #+#    #+#             */
/*   Updated: 2021/02/06 13:30:47 by challeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_char_isalpha(int c)
{
	bool	res;

	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		res = true;
	else
		res = false;
	return (res);
}
