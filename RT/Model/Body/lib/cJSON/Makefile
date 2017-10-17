NAME	= cJSON.a
SRC		= cJSON.c

OBJ		= $(SRC:.c=.o)
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

all: $(NAME)

%.o:%.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

clean:
	@rm -fv $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all
