# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/14 16:47:08 by hshakula          #+#    #+#              #
#    Updated: 2017/10/14 17:29:35 by hshakula         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OBJ_PATH = ./obj/

NAME = libft.a
SRC =	ft_merge.c ft_split_str_to_int.c ft_sizeofnumber.c ft_atoi_base.c ft_countwords.c ft_getword.c ft_isnum.c ft_lstmap.c ft_realloc.c ft_islower.c ft_lstiter.c ft_lstaddend.c ft_lstadd.c ft_lstdel.c ft_lstdelone.c ft_lstnew.c ft_strsplit.c ft_putnbr_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putchar_fd.c ft_strtrim.c ft_strjoin.c ft_strsub.c ft_strmapi.c ft_strmap.c ft_striteri.c ft_strlcat.c ft_strrev.c ft_power.c ft_bzero.c ft_memset.c ft_strlen.c ft_strdup.c ft_strcpy.c ft_atoi.c ft_isdigit.c ft_isspace.c ft_strcat.c ft_strncat.c ft_strchr.c ft_strrchr.c ft_strstr.c ft_strnstr.c ft_strcmp.c ft_strncmp.c ft_isalpha.c ft_isalnum.c ft_isascii.c ft_isprint.c  ft_toupper.c ft_isupper.c ft_tolower.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c ft_memcmp.c ft_strncpy.c ft_memalloc.c ft_memdel.c ft_strnew.c ft_strdel.c ft_strclr.c ft_striter.c ft_strequ.c ft_strnequ.c ft_putchar.c ft_putstr.c ft_putendl.c ft_putnbr.c ft_itoa.c \
		vector_handle.c vector_handle_.c ft_strisdigit.c
OBJ_NAME = $(SRC:.c=.o)
FLAGS = -Wall -Werror -Wextra
CC = gcc

OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

$(OBJ_PATH)%.o: %.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(FLAGS) -o $@ -c $<

clean:
	@rm -fv $(OBJ)
	@rm -rf $(OBJ_PATH)

fclean: clean
	@rm -fv $(NAME)

re: fclean all

.PHONY: re fclean all clean zip