# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: challeau <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/07 18:08:08 by challeau          #+#    #+#              #
#    Updated: 2020/02/08 14:37:44 by challeau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	ft_add_char.c		\
		ft_atof.c		\
		ft_atoi.c		\
		ft_bzero.c		\
		ft_calloc.c		\
		ft_char_isalnum.c	\
		ft_char_isalpha.c	\
		ft_char_isascii.c	\
		ft_char_isdigit.c	\
		ft_char_rep_count.c	\
		ft_memdel.c		\
		ft_memdel_strptr.c	\
		ft_putstr_fd.c		\
		ft_realloc.c		\
		ft_split.c		\
		ft_str_isnum.c		\
		ft_strcat.c 		\
		ft_strchr.c		\
		ft_strcmp.c		\
		ft_strdup.c		\
		ft_strjoin.c		\
		ft_strlcpy.c		\
		ft_strlen.c		\
		ft_strnlen.c		\
		get_next_line.c

OBJS	=	${SRCS:.c=.o}

HEAD	=	./libft.h

NAME	=	libft.a

RM	=	rm -f

FLAGS	=	-Wall -Wextra -Werror

.c.o:
	clang ${FLAGS} -I ${HEAD} -c $< -o ${<:.c=.o}

$(NAME) : ${OBJS}
	ar -rcs libft.a ${OBJS}

all:	${NAME}

clean:
		${RM} ${OBJS}

fclean:	clean
	${RM} ${NAME}

re:		fclean all

.PHONY:all clean fclean re bonus%
