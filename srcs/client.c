#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include "../inc/libft/libft.h"

static void	cerror(char *err_str)
{
	ft_putstr_fd(1, "[CLIENT] encountered an error!\n\tIssue: ");
	ft_putstr_fd(1, err_str);
	ft_putstr_fd(1, ".\n");
	perror("perror says");
	exit(EXIT_FAILURE);
}

static int	send_null(int pid, char *str)
{
	static int	i = 0;

	if (i++ != 8)
	{
		if (kill(pid, SIGUSR1) == -1)
			cerror(str);
		return (0);
	}
	return (1);
}

static int	send_bit(char *str, pid_t pid)
{
	static pid_t	server;
	static char	*mess;
	static int	byte = 0;
	static int	bit = 7;
	int		sig;

	if (str)
	{
		mess = ft_strdup(str);
		server = pid;
	}
	if (mess[byte])
	{
		if (((mess[byte] >> bit) & 0x01) == 0)
			sig = SIGUSR1;
		else
			sig = SIGUSR2;
		if (kill(server, sig) < 0)
			cerror("couldn't contact server");
		bit--;
		if (bit < 0)
		{
			byte++;
			bit = 7;
		}
		return (0);
	}
	if (!send_null(server, mess))
		return (0);
	ft_memdel(mess);
	return (1);	
}

static void	signal_handler(int sig, __attribute__((unused))siginfo_t *info,
			__attribute__((unused))void *context)
{
	int	check;

	check = 0;
	if (sig == SIGUSR1)
		check = send_bit(NULL, 0);
	else if (sig == SIGUSR2)
		cerror("server ran into an issue..");
	else if (sig == SIGTERM)
		exit(0);
	if (check)
	{
		printf("she's done\n");
		exit(EXIT_SUCCESS);
	}
}

int	main(int ac, char **av)
{
	pid_t	server_pid;
	struct sigaction	sig;
	sigset_t			block_mask;

	if (ac != 3)
		cerror("wrong  number of arguments");
	server_pid = ft_atoi(av[1]);
	if (kill(server_pid, 0) == -1)
		cerror("wrong pid or permissions");

	sigemptyset(&block_mask);
	sigaddset(&block_mask, SIGINT);
	sigaddset(&block_mask, SIGQUIT);
	sig.sa_sigaction = &signal_handler;
	sig.sa_flags = SA_SIGINFO;
	send_bit(av[2], server_pid);
	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);
	sigaction(SIGINT, &sig, NULL);
	while (420)
		sleep(69);
	return (0);
}
