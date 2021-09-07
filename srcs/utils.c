/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: challeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 18:46:44 by challeau          #+#    #+#             */
/*   Updated: 2021/08/31 18:46:44 by challeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

/*
** prevents user from interrupting th client while it is sending a message.
*/
void	kill_handler(__attribute__((unused))int sig)
{
	ft_putstr_fd("\n[CLIENT] this program is busy and cannot be \
terminated prematurely.\n", 1);
}

/*
** called if a string was printed or if a new client is sending a message before
** the old one could finish.
** resets the variables necessary for the server's signal_handler() to work.
*/
void	reset(char **str, uint8_t *bit, uint8_t *byte)
{
	if (str)
	{
		free(*str);
		*str = NULL;
	}
	*bit = 0;
	*byte = 0;
}

void	print_pid(pid_t pid)
{
	ft_putstr_fd("[SERVER] pid: ", 1);
	ft_putnbr_fd(pid, 1);
	ft_putstr_fd("\n", 1);
}

/*
** client error function.
*/
void	cerror(char *err_str, char *message)
{
	if (message)
	{
		free(message);
		message = NULL;
	}
	ft_putstr_fd("[CLIENT] encountered an error! Issue: ", 1);
	ft_putstr_fd(err_str, 1);
	perror("\tperror says");
	exit(EXIT_FAILURE);
}

/*
** takes care of cleaning up the allocated message string in client if an issue is
** encountered.
*/
void	ft_panic(char *str)
{
	if (str)
	{
		free(str);
		str = NULL;
	}
	cerror("server ran into an issue.\n", NULL);
}
