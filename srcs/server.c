/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: challeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 22:00:36 by challeau          #+#    #+#             */
/*   Updated: 2021/08/31 22:00:36 by challeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

static void	clean_exit(pid_t pid, char *str)
{
	if (str)
		ft_memdel(str);
	if (pid > 0)
		kill(pid, SIGUSR2);
	ft_putstr_fd("\n[SERVER] bye !!\n", 1);
	exit(EXIT_SUCCESS);
}

static void	serror(char *str, char *err_str, pid_t pid)
{
	if (str)
		ft_memdel(str);
	if (pid)
		kill(pid, SIGUSR2);
	ft_putstr_fd("[SERVER] encountered an error! Issue: ", 1);
	ft_putstr_fd(err_str, 1);
	perror("\tperror says");
	exit(EXIT_FAILURE);
}

/*
** apends a byte to a string.
** if said byte is null, print the string.
*/
static char	*add_byte(char *str, char byte, pid_t pid)
{
	if (str == NULL)
	{
		str = ft_strdup("");
		if (!str)
			serror(str, "allocation error.\n", pid);
	}
	if (byte == '\0')
	{
		ft_putstr_fd(str, 1);
		ft_putstr_fd("\n", 1);
		free(str);
		return (NULL);
	}
	return (ft_add_char(str, byte));
}

/*
** signal handling function for SIGUSR1, SIGUSR2, SIGINT AND SIGKILL.
** if the program receives SIGINT, SIGKILL or SIGSTOP, then exit cleanly.
** if it receives SIGUSR1 or SIGUSR2, add a bit to the buffer byte (0 or 1 respectively).
** upon reception of 8 bits, the now full byte is added to str, and printed if
** byte is '\0'. 
 */
static void	signal_handler(int sig, siginfo_t *info,
			__attribute__((unused))void *context)
{
	static uint8_t		bit = 0;
	static uint8_t		byte = 0;
	static char			*str = NULL;
	static pid_t		client_pid = 0;

	if (sig == SIGINT || sig == SIGSTOP || sig == SIGQUIT)
		clean_exit(client_pid, str);
	if (sig == SIGUSR1 || sig == SIGUSR2)
	{
		if (client_pid > 0 && client_pid != info->si_pid)
			reset(&str, &bit, &byte);
		client_pid = info->si_pid;
		byte <<= 1;
		if (sig == SIGUSR2)
			byte |= 0x01;
		bit++;
	}
	if (bit == 8)
	{
		str = add_byte(str, byte, client_pid);
		reset(NULL, &bit, &byte);
	}
	if (kill(info->si_pid, SIGUSR1) < 0)
		serror(str, "couldn't contact client.\n", client_pid);
}

/*
** sets up sigaction() to handle reception of SIGUSR1, SIGUSR2, SIGKILL and SIGSTOP.
 */
int	main(void)
{
	struct sigaction	sig;

	print_pid(getpid());
	sig.sa_sigaction = &signal_handler;
	sig.sa_flags = SA_SIGINFO;
	sigemptyset(&sig.sa_mask);
	sigaddset(&sig.sa_mask, SIGKILL);
	sigaddset(&sig.sa_mask, SIGSTOP);
	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);
	sigaction(SIGINT, &sig, NULL);
	sigaction(SIGQUIT, &sig, NULL);
	while (420)
		sleep(69);
	return (0);
}
