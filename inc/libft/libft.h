/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: challeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 22:39:50 by challeau          #+#    #+#             */
/*   Updated: 2021/05/22 22:39:50 by challeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdbool.h>
# include <stdlib.h>
# include <stdint.h>
# include <fcntl.h>
# include <unistd.h>

/*
** MEMORY
*/
char	*ft_calloc(size_t size);
void	ft_memdel(char *ptr);
void	ft_memdel_strptr(char **array);
char	*ft_realloc(char *str, size_t new_size);
char	*ft_strdup(const char *src);

/*
** STRING TO NUM
*/
float	ft_atof(const char*str);
int		ft_atoi(const char *str);

/*
** CHAR OR STRING TYPE
*/
bool	ft_char_isalnum(int c);
bool	ft_char_isalpha(int c);
bool	ft_char_isascii(int c);
bool	ft_char_isdigit(int c);
bool	ft_str_isnum(const char *str);

/*
** STR MANIPULATION
*/
char	*ft_add_char(char *src, char to_add);
void	ft_bzero(char *str);
uint8_t	ft_char_rep_count(char c, const char *str);
void	ft_putstr_fd(int fd, char *str);
char	**ft_split(const char *src, char sep);
size_t	ft_strcat(const char *src, char *dst);
int		ft_strchr(const char *str, char to_find);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *str);
size_t	ft_strnlen(const char *str, size_t n);

/*
** OTHERS
*/
int		get_next_line(int fd, char **line);

#endif
