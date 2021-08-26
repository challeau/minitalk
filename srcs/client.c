#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

static void	error(char *err_str)
{
	printf("[CLIENT] encountered an error!\n\tIssue: ");
	printf("%s.\n", err_str);
	perror("perror says: ");
	exit(EXIT_FAILURE);
}

int	main(__attribute__((unused))int ac, __attribute__((unused))char **av)
{
	pid_t	pid;

	if (ac != 2)
		error("wrong  number of arguments");
	pid = atoi(av[1]);
	if (kill(pid, 0) == -1)
		error("wrong pid or permissions");
	kill(pid, SIGUSR1);
	return (0);
}
