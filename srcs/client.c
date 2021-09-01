/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: challeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 23:13:10 by challeau          #+#    #+#             */
/*   Updated: 2021/08/31 23:13:10 by challeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

static bool	send_null_byte(pid_t pid)
{
	static uint8_t	i = 0;

	if (i++ < 8)
	{
		if (kill(pid, SIGUSR1) < 0)
			cerror("could not contact server.\n", NULL);
		return (false);
	}
	return (true);
}

static bool	send_bit(char *str, int pid, bool panic)
{
	static char	*message = 0;
	static int	bit = -1;

	if (str)
		message = ft_strdup(str);
	if (panic == true || !message)
		ft_panic(message);
	if (message && message[++bit / 8])
	{
		if (message[bit / 8] & (0x80 >> bit % 8))
		{
			if (kill(pid, SIGUSR2) == -1)
				cerror("could not contact server.\n", message);
		}
		else if (kill(pid, SIGUSR1) == -1)
			cerror("could not contact server.\n", message);
		return (false);
	}
	if (send_null_byte(pid) == false)
		return (false);
	free(message);
	return (true);
}

static void	signal_handler(int sig, siginfo_t *info,
			__attribute__((unused))void *context)
{
	static bool	done = false;

	if (sig == SIGUSR1 && done == false)
		done = send_bit(NULL, info->si_pid, false);
	if (sig == SIGUSR1 && done == true)
	{
		if (send_null_byte(info->si_pid) == true)
		{
			ft_putstr_fd("[CLIENT] server has successfully received your \
message. :)\n", 1);
			exit(EXIT_SUCCESS);
		}
	}
	if (sig == SIGUSR2)
		send_bit(NULL, 0, true);
}

int	main(int ac, char **av)
{
	pid_t				server_pid;
	struct sigaction	sig;

	if (ac == 3 && ft_str_isnum(av[1]) == true
		&& ft_str_isprint(av[1]) == true)
	{
		server_pid = ft_atoi(av[1]);
		if (kill(server_pid, 0) == -1 || server_pid == 0)
			cerror("wrong pid or permissions.\n", NULL);
		sig.sa_sigaction = &signal_handler;
		sig.sa_mask = (sigset_t){};
		sig.sa_flags = SA_SIGINFO | SA_NODEFER;
		sigaction(SIGUSR1, &sig, NULL);
		sigaction(SIGUSR2, &sig, NULL);
		signal(SIGINT, kill_handler);
		signal(SIGQUIT, kill_handler);
		send_bit(av[2], server_pid, false);
		while (420)
			sleep(69);
	}
	cerror("incorrect arguments.\n\tUsage: ./client <server pid> \
<string to print>.\n", NULL);
	return (0);
}
