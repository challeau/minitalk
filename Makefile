SERVER			=	server
CLIENT			=	client

SRC_PATH		= 	./srcs
SRC_NAME		=	server.c	\
				client.c	\
				utils.c

OBJ_PATH = objs
OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(CC) $(CFLAGS) -c $< $(CPPFLAGS) -o $@

CC		=	clang
CFLAGS		=	-Wall -Werror -Wextra -g

CPPFLAGS	=	-I inc/libft/

LDFLAGS		=	inc/libft/libft.a

all: $(NAME)

$(NAME): $(SERVER) $(CLIENT)

$(SERVER): objs/server.o objs/utils.o
	@make -C inc/libft  2> /dev/null || true
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $(SERVER) $^ $(LDFLAGS)
	@echo "Server compilation \033[1;32mOK\033[m"

$(CLIENT): objs/client.o  objs/utils.o
	@make -C inc/libft  2> /dev/null || true
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $(CLIENT) $^ $(LDFLAGS)
	@echo "Client compilation \033[1;32mOK\033[m"

clean:
	@make -C inc/libft clean
	@rm -f $(OBJ)
	@rmdir $(OBJ_PATH)

fclean: clean
	@make -C inc/libft fclean
	@rm -f $(SERVER) $(CLIENT)

re: fclean all

.PHONY: all, clean, fclean, re
