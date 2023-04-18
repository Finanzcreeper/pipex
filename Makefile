CC = cc
CFLAGS = -Wall -Werror -Wextra -g3 -fsanitize
MAKEFLAGS = --no-print-directory
NAME = pipex
SRC = pipex.c pipex_functions.c pipex_extraerror.c
OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $^ $(CFLAGS) libft.a -o $(NAME)
clean :
	- rm *.o

fclean : clean
	- rm $(NAME)

re : fclean all
	
