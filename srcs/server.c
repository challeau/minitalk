#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include "../inc/libft/libft.h"

/* printf("%c%c%c%c%c%c%c%c\n",  (c & 0x80 ? '1' : '0'), */
/*        (c & 0x40 ? '1' : '0'), */
/*        (c & 0x20 ? '1' : '0'), */
/*        (c & 0x10 ? '1' : '0'), */
/*        (c & 0x08 ? '1' : '0'), */
/*        (c & 0x04 ? '1' : '0'), */
/*        (c & 0x02 ? '1' : '0'), */
/*        (c & 0x01 ? '1' : '0') ); */

static void	signal_handler(int sig, siginfo_t *info,
			       __attribute__((unused))void *context)
{
	static uint8_t		i = 0;
	static char		c = 0;
	static char		*str = 0;
	static int		pid = 0;

//	printf("entering handler\n");
	str = ft_strdup("");
	if (info->si_pid)
		pid = info->si_pid;
	if (sig == SIGUSR1)
	{
//		printf("received SIGUSR1\n");
		c = c << 1;
		i++;
	}
	if (sig == SIGUSR2)
	{
//		printf("received SIGUSR2\n");
		c = c << 1;
		c |= 0x01;
		i++;
		/* printf("%c%c%c%c%c%c%c%c\n",  (c & 0x80 ? '1' : '0'), */
		/*        (c & 0x40 ? '1' : '0'), */
		/*        (c & 0x20 ? '1' : '0'), */
		/*        (c & 0x10 ? '1' : '0'), */
		/*        (c & 0x08 ? '1' : '0'), */
		/*        (c & 0x04 ? '1' : '0'), */
		/*        (c & 0x02 ? '1' : '0'), */
		/*        (c & 0x01 ? '1' : '0') ); */
	}
	if (i == 8)
	{
		str = ft_add_char(str, c);
		ft_putstr_fd(1, str);
		ft_putstr_fd(1, "\n");
		i = 0;
		c = 0;
	}
	/* if (kill(pid, SIGUSR1) == -1) */
	/* 	perror("yikes"); */
}

int	main(void)
{
	pid_t			pid;
	struct sigaction	sig;
	sigset_t		block_mask;

	pid = getpid();
	printf("[SERVER] pid: %d\n", pid);
	
	sig.sa_handler = NULL;
	sig.sa_sigaction = &signal_handler;
	sig.sa_flags = SA_SIGINFO;

	sigemptyset(&block_mask);
	sigaddset(&block_mask, SIGINT);
	sig.sa_mask = block_mask;

	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);
	while (420)
		sleep(69);
	return (0);
}