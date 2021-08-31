#include "../inc/minitalk.h"

static void	cerror(char *err_str)
{
	ft_putstr_fd("[CLIENT] encountered an error! Issue: ", 1);
	ft_putstr_fd(err_str, 1);
	perror("\tperror says");
	exit(EXIT_FAILURE);
}

static bool	send_null_byte(pid_t pid)
{
	static uint8_t i = 0;

	if (i < 8)
	{
		if (kill(pid, SIGUSR1) < 0)
			cerror("could not contact server.\n");
		i++;
		return (false);
	}
	return (true);
}

/* static bool	send_bit(char *str, pid_t pid) */
/* { */
/* 	static uint8_t	bit = 0; */
/* 	static int	byte = 0; */
/* 	static char	*message = NULL; */

/* 	if (str) */
/* 		message = ft_strdup(str); */
/* 	while(message[byte]) */
/* 	{ */
/* 		if (((message[byte] >> bit) & 0x01) == 0) */
/* 		{ */
/* 			if (kill(pid, SIGUSR1) < 0) */
/* 				cerror("could not contact server.\n"); */
/* 		} */
/* 		else if (kill(pid, SIGUSR2) < 0) */
/* 			cerror("could not contact server.\n"); */
/* 		bit++; */
/* 		if (bit == 8) */
/* 		{ */
/* 			byte++; */
/* 			bit = 8; */
/* 		} */
/* 	} */
/* 	ft_memdel(message); */
/* 	return (true); */
/* } */

int	send_bit(char *str, int pid)
{
	static char	*message = 0;
	static int	bit = -1;
	const int	masks[8] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};

	if (str)
		message = ft_strdup(str);
	if (!message)
		cerror("f");
	if (message[++bit / 8])
	{
		if (message[bit / 8] & masks[bit % 8])
		{
			if (kill(pid, SIGUSR2) == -1)
				cerror("f");
		}
		else if (kill(pid, SIGUSR1) == -1)
			cerror("f");
		return (0);
	}
	if (!send_null_byte(pid))
		return (0);
	free(message);
	return (1);
}

static void	signal_handler(int sig, __attribute__((unused))siginfo_t *info,
			__attribute__((unused))void *context)
{
	static bool	done = false;

	if (sig == SIGUSR1)
		done = send_bit(NULL, info->si_pid);
	if (sig == SIGUSR2)
		cerror("server ran into an issue.\n");
	if (sig == SIGQUIT)
		exit(0);
	if (done == true)
	{
		ft_putstr_fd("[CLIENT] server has successfully received your \
message. :)\n", 1);
		exit(EXIT_SUCCESS);
	}
}

int	main(int ac, char **av)
{
	pid_t			server_pid;
	struct sigaction	sig;

	if (ac == 3 && ft_str_isnum(av[1]) == true
	    && ft_str_isprint(av[1]) == true)
	{
		server_pid = ft_atoi(av[1]);
		if (kill(server_pid, 0) == -1 || server_pid == 0)
			cerror("wrong pid or permissions.\n");
		sig.sa_sigaction = &signal_handler;
		sig.sa_mask = (sigset_t){};
		sig.sa_flags = SA_SIGINFO | SA_NODEFER;
		sigaction(SIGUSR1, &sig, NULL);
		sigaction(SIGUSR2, &sig, NULL);
		send_bit(av[2], server_pid);
		while (420)
			sleep(69);
	}
	cerror("incorrect arguments.\n\tUsage: ./client <server pid> \
<string to print>.\n");
	return (0);
}
