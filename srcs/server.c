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

static void	signal_handler(int sig, siginfo_t *info,
			__attribute__((unused))void *context)
{
	static uint8_t		bit = 0;
	static uint8_t		byte = 0;
	static char		*str = NULL;
	static pid_t		client_pid = 0;

	if (sig == SIGINT)
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
	while (420)
		sleep(69);
	return (0);
}

