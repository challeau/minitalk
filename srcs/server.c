#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include "../inc/libft/libft.h"

static void	clean_exit(void)
{
	printf("[SERVER] exiting...\n");
	exit(EXIT_SUCCESS);
}

static void	signal_handler(int sig)
{
	static int		i;
	struct sigaction	siga;

	if (sig == SIGUSR1)
	{
		printf("[SERVER] received signals from %d client.s\n", i);
		i++;
	}
	if (sig == SIGINT)
		clean_exit();
	siga.sa_handler = &signal_handler;
	siga.sa_flags = SA_NODEFER;
	sigaction(SIGUSR1, &siga, NULL);
	sigaction(SIGINT, &siga, NULL);
	pause();
}

int	main(void)
{
	pid_t			pid;
	struct sigaction	sig;

	pid = getpid();
	printf("[SERVER] pid: %d\n", pid);
	sig.sa_handler = &signal_handler;
	sig.sa_flags = SA_NODEFER;
	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGINT, &sig, NULL);
	pause();
	return (0);
}
