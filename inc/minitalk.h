# ifndef MINITALK_H
# define MINITALK_H
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include "libft/libft.h"

/* UTILS */
void	kill_handler(__attribute__((unused))int sig);
void	reset(char **str, uint8_t *bit, uint8_t *byte);
void	print_pid(pid_t pid);

# endif