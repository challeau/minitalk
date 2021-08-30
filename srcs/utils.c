#include "../inc/minitalk.h"

void	kill_handler(__attribute__((unused))int sig)
{
	ft_putstr_fd("\n[CLIENT] this program is busy and cannot be ", 1);
	ft_putstr_fd("terminated prematurely.\n", 1);
}