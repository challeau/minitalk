/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inc/minitalk.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: challeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 23:52:24 by challeau          #+#    #+#             */
/*   Updated: 2021/08/31 23:52:24 by challeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
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

#endif