#include "../inc/minitalk.h"

static void	cerror(char *err_str)
{
	ft_putstr_fd("[CLIENT] encountered an error! Issue: ", 1);
	ft_putstr_fd(err_str, 1);
	ft_putstr_fd(".\n", 1);
	perror("\tperror says");
	exit(EXIT_FAILURE);
}

static bool	send_bit(char *str, pid_t pid)
{
	static pid_t	server;
	static char	*mess;
	static int	byte = 0;
	static int8_t	bit = 0;
	char x[8] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
	
	if (str)
	{
		mess = ft_strdup(str);
		server = pid;
	}
	if (mess[byte])
	{
		if ((mess[byte] & x[bit]) == 0)
		{
			if (kill(server, SIGUSR1) < 0)
				cerror("couldn't contact server");
		}
		else
		{
			if (kill(server, SIGUSR2) < 0)
				cerror("couldn't contact server");

		}
		bit++;
		if (bit == 8)
		{
			byte++;
			bit = 0;
		}
		return (false);
	}
	if (bit < 8)
	{
		if (kill(server, SIGUSR1) < 0)
			cerror("couldn't contact server");
		bit++;
		return (false);
	}
	ft_memdel(mess);
	return (true);
}

static void	signal_handler(int sig, __attribute__((unused))siginfo_t *info,
			__attribute__((unused))void *context)
{
	bool	done;

	done = 0;
	if (sig == SIGUSR1)
		done = send_bit(NULL, 0);
	if (sig == SIGUSR2)
		cerror("server ran into an issue..");
	if (done)
	{
		ft_putstr_fd("[CLIENT] string was received successfully. job is done :)\n", 1);
		exit(EXIT_SUCCESS);
	}
}

int	main(int ac, char **av)
{
	pid_t	server_pid;
	struct sigaction	sig;

	if (ac != 3)
		cerror("wrong  number of arguments");
	server_pid = ft_atoi(av[1]);
	if (kill(server_pid, 0) == -1 || server_pid == 0)
		cerror("wrong pid or permissions");
	sig.sa_sigaction = &signal_handler;
	sig.sa_mask = (sigset_t){};
	sig.sa_flags = SA_SIGINFO | SA_NODEFER;
	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);
	signal(SIGINT, kill_handler);
	signal(SIGTERM, kill_handler);
	signal(SIGQUIT, kill_handler);
	send_bit(av[2], server_pid);
	while (420)
		sleep(69);
	return (0);
}