#include "../inc/minitalk.h"

static void	clean_exit(pid_t pid)
{
	if (pid > 0)
		kill(pid, SIGUSR2);
	ft_putstr_fd("\n[SERVER] bye !!\n", 1);
	exit(EXIT_SUCCESS);
}

static void	serror(char *err_str, pid_t pid)
{
	if (pid)
		kill(pid, SIGUSR2);
	ft_putstr_fd("[SERVER] encountered an error! Issue: ", 1);
	ft_putstr_fd(err_str, 1);
	ft_putstr_fd(".\n", 1);
	perror("\tperror says");
	exit(EXIT_FAILURE);
}

static void	signal_handler(int sig, siginfo_t *info,
			__attribute__((unused))void *context)
{
	static uint8_t		i = 0;
	static char		c = 0;
	static char		*str = NULL;
	static pid_t		client_pid = 0;

	if (str == NULL)
		str = ft_strdup("");
	if (sig == SIGINT)
	{
		if (str)
			ft_memdel(str);
		clean_exit(client_pid);
	}
	if (sig == SIGUSR1 || sig == SIGUSR2)
	{
		client_pid = info->si_pid;
		c = c << 1;
		if (sig == SIGUSR2)
			c |= 0x01;
		i++;
	}
	if (i == 8)
	{
		if (c == '\0')
		{
			ft_putstr_fd(str, 1);
			ft_putstr_fd("\n", 1);
			free(str);
			str = NULL;
		}
		else
			str = ft_add_char(str, c);
		i = 0;
		c = 0;
	}
	if (kill(info->si_pid, SIGUSR1) < 0)
		serror("couldn't contact client", info->si_pid);
}

static void print_pid(pid_t pid)
{
	ft_putstr_fd("[SERVER] pid: ", 1);
	ft_putnbr_fd(pid, 1);
	ft_putstr_fd("\n", 1);
}

int	main(void)
{
	struct sigaction	sig;

	print_pid(getpid());
	sig.sa_sigaction = &signal_handler;
	sig.sa_flags = SA_SIGINFO;
	sigemptyset(&sig.sa_mask);
	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);
	sigaction(SIGINT, &sig, NULL);
	while (420)
		sleep(69);
	return (0);
}

