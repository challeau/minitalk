#include "../inc/minitalk.h"

void	kill_handler(__attribute__((unused))int sig)
{
	ft_putstr_fd("\n[CLIENT] this program is busy and cannot be ", 1);
	ft_putstr_fd("terminated prematurely.\n", 1);
}

void	reset(char **str, uint8_t *bit, uint8_t *byte)
{
	if (str)
	{
		free(*str);
		*str = NULL;
	}
	*bit = 0;
	*byte = 0;
}

void	print_pid(pid_t pid)
{
	ft_putstr_fd("[SERVER] pid: ", 1);
	ft_putnbr_fd(pid, 1);
	ft_putstr_fd("\n", 1);
}
