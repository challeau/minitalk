#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include "../inc/libft/libft.h"

static void	clean_exit(int sig)
{
	ft_putstr_fd(1, "\n[SERVER] bye !!\n");
	if (sig == SIGINT)
		exit(EXIT_SUCCESS);
}

static void	serror(char *err_str)
{
	ft_putstr_fd(1, "[SERVER] encountered an error!\n\tIssue: ");
	ft_putstr_fd(1, err_str);
	ft_putstr_fd(1, ".\n");
	perror("perror says");
	exit(EXIT_FAILURE);
}

static void	signal_handler(int sig, siginfo_t *info,
			__attribute__((unused))void *context)
{
	static uint8_t		i = 0;
	static char		c = 0;
	static char		*str = NULL;

	if (str == NULL)
		str = ft_strdup("");
	if (sig == SIGUSR1 || sig == SIGUSR2)
	{
		c = c << 1;
		if (sig == SIGUSR2)
			c |= 0x01;
		i++;
	}
	if (i == 8)
	{
		if (c == '\0')
		{
			ft_putstr_fd(1, str);
			ft_memdel(str);
			str = ft_strdup("");
		}
		else
			str = ft_add_char(str, c);
		i = 0;
		c = 0;
	}
	if (kill(info->si_pid, SIGUSR1) < 0)
		serror("couldn't contact client");
}

int	main(void)
{
	pid_t			pid;
	struct sigaction	sig;
	sigset_t			block_mask;

	pid = getpid();
	ft_putstr_fd(1, "[SERVER] pid: ");
	ft_putstr_fd(1, ft_itoa(pid));
	ft_putstr_fd(1, "\n");

	sigemptyset(&block_mask);
	sigaddset(&block_mask, SIGINT);
	sigaddset(&block_mask, SIGQUIT);
	sig.sa_sigaction = &signal_handler;
	sig.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);
	signal(SIGINT, clean_exit);
	while (420)
		sleep(69);
	return (0);
}

