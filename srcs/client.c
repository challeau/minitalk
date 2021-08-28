#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include "../inc/libft/libft.h"

static void	error(char *err_str)
{
	printf("[CLIENT] encountered an error!\n\tIssue: ");
	printf("%s.\n", err_str);
	perror("perror says");
	exit(EXIT_FAILURE);
}

/* static void s_str(char *str) */
/* { */
/* 	int	i; */
/* 	char	tmp; */

/* 	while (*str) */
/* 	{ */
/* 		i = 7; */
/* 		tmp = *str; */
/* 		while (i >= 0) */
/* 		{ */
/* 			if (((tmp >> i) & 0x01) == 0) */
/* 				printf("0"); */
/* 			else */
/* 				printf("1"); */
/* 			i--; */
/* 		} */
/* 		printf("\n"); */
/* 		str++; */
/* 	} */
/* } */

static void	send_string(char *str, pid_t pid)
{
	int	i;
	char	tmp;

	while (*str)
	{
		tmp = *str;
		i = 7;
		while (i >= 0)
		{
			if (((tmp >> i) & 0x01) == 0)
			{
				int ret = kill(pid, SIGUSR1);
				if (ret < 0)
					error("couldn't send signal");
				//			printf("SIGUSR1 sent\n");
			}
			else
			{
				int ret = kill(pid, SIGUSR2);
				if (ret < 0)
					error("couldn't send signal");
				//			printf("SIGUSR2 sent\n");
			}
			i--;
			usleep(100);
		}
		str++;
	}
	for (int i = 0 ; i <= 8 ; i++)
		if (kill(pid, SIGUSR1) < 0)
			error("couldn't send signal");
}

/* static void lol(int sig) */
/* { */
/* 	printf("she's done\n"); */
/* 	if (sig == SIGTERM) */
/* 		exit(0); */
/* } */

int	main(int ac, char **av)
{
	pid_t	server_pid;

	if (ac != 3)
		error("wrong  number of arguments");
	server_pid = ft_atoi(av[1]);
	if (kill(server_pid, 0) == -1)
		error("wrong pid or permissions");
	send_string(av[2], server_pid);
	/* signal(SIGUSR1, lol); */
	/* signal(SIGTERM, lol); */
	while (420)
		sleep(69);
	return (0);
}
